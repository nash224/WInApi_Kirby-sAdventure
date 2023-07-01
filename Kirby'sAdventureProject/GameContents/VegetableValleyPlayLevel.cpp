#include "VegetableValleyPlayLevel.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "GameEffect.h"
#include "UIManager.h"
#include "BackGround.h"
#include "Kirby.h"
#include <vector>


bool VegetableValleyPlayLevel::PrevLevelTriggerOn = false;
bool VegetableValleyPlayLevel::NextLevelTriggerOn = false;
bool VegetableValleyPlayLevel::IsStageEnd = false;
bool VegetableValleyPlayLevel::IsPlayerEnter = false;
bool VegetableValleyPlayLevel::IsPlayerMiss = false;
bool VegetableValleyPlayLevel::IsFadeDone = false;
bool VegetableValleyPlayLevel::IsChangeLevel = false;;
bool VegetableValleyPlayLevel::ChangeClearDoor = false;

GameEngineSoundPlayer VegetableValleyPlayLevel::BGM_Player;
bool VegetableValleyPlayLevel::IsBGM_On = false;
float VegetableValleyPlayLevel::BGMSoundVolume = 0.0f;

int VegetableValleyPlayLevel::Camera_ShakeCount = 0;
float VegetableValleyPlayLevel::Camera_ShakeMagnitude = 3.0f;


float VegetableValleyPlayLevel::UpdateTime = 0.0f;
bool VegetableValleyPlayLevel::Level_DebugRenderIsOn = false;




VegetableValleyPlayLevel::VegetableValleyPlayLevel() 
{
}

VegetableValleyPlayLevel::~VegetableValleyPlayLevel() 
{
}




void VegetableValleyPlayLevel::RePlayBGM()
{
	BGM_Player = GameEngineSound::SoundPlay(LevelBgmFileName);
	IsBGM_On = true;
}


void VegetableValleyPlayLevel::SetPlayerPosAndCameraPos(const float4& _PlayerPos, const float4& _CameraPos)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("ī�޶� NUll �Դϴ�.");
		return;
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);


	LevelPlayer->SetPos(_PlayerPos);
	MainCameraPtr->SetPos(_CameraPos);
}




void VegetableValleyPlayLevel::CheckRespawnEnemy()
{
	for (size_t i = 0; i < LevelEnemy.size(); i++)
	{
		Enemy* Enemy = LevelEnemy[i];
		Enemy->RespawnTrigger();
	}
}



void VegetableValleyPlayLevel::CreateAndSetupBackgroundEffectRenderer(
	const std::string& _AnimationName,
	const std::string& _FileName,
	int _StartFrame, int _EndFrame,
	float4 _Pos, float _Ratio,
	float _Inter/* = 0.1f*/, bool _Loop/* = true*/)
{
	GameEngineRenderer* Render = LevelEffect->CreateRenderer(RenderOrder::BackGroundEffect);
	Render->CreateAnimation(_AnimationName, _FileName, _StartFrame, _EndFrame, _Inter, _Loop);
	Render->SetRenderPos(_Pos);
	Render->SetScaleRatio(_Ratio);
	Render->ChangeAnimation(_AnimationName);
}



void VegetableValleyPlayLevel::CameraFocus(float _Delta)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GameEngineCamera* CameraPtr = GetMainCamera();
	if (nullptr == CameraPtr)
	{
		MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 CameraPos = CameraPtr->GetPos();

	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 CurrentUIScale = LevelUIManager->UIScale;



	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("���ȭ���� �ҷ����� ���߽��ϴ�.");
		return;
	}

	LevelBackGround->BackGroundScale;



	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 PlayerMovePos = LevelPlayer->KirbyMovePos;
	float4 PlayerPos = LevelPlayer->GetPos();



	CameraFrontCheckPos = CameraPos;
	CameraBackCheckPos = float4{ CameraPos.X + WinScale.X , CameraPos.Y + WinScale.Y - CurrentUIScale.Y };

	float4 CameraMovePos = PlayerMovePos;

	// Ŀ�� ������ ������ ��, ȭ���� �߾��� �Ѿ�� ������
	if (PlayerPos.X < CameraFrontCheckPos.X + WinScale.Half().X && PlayerMovePos.X > 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// Ŀ�� ���� ������ ��, ȭ���� 1/4 ������ �Ѿ�� ������
	if (PlayerPos.X > CameraFrontCheckPos.X + WinScale.Half().Half().X && PlayerMovePos.X < 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// Ŀ�� ���� ������ ��, ȭ���� 1/4 ������ �Ѿ�� ������
	if (PlayerPos.Y > CameraFrontCheckPos.Y + (WinScale - CurrentUIScale).Half().Half().Y && PlayerMovePos.Y < 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}

	// Ŀ�� �Ʒ��� ������ ��, UIȭ���� �� ������ȭ���� 3/4 ������ �Ѿ�� ������
	if (PlayerPos.Y < CameraBackCheckPos.Y - (WinScale - CurrentUIScale).Half().Half().Y && PlayerMovePos.Y > 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}



	// ���� ���� ������ ���ϰ� ����
	if (CameraPos.X + PlayerMovePos.X < 0.0f || CameraBackCheckPos.X + PlayerMovePos.X > BackGroundScale.X)
	{
		CameraMovePos.X = 0.0f;
	}

	// ������ �Ʒ��� ������ ���ϰ� ����
	if (CameraPos.Y + PlayerMovePos.Y < 0.0f || CameraBackCheckPos.Y + PlayerMovePos.Y > BackGroundScale.Y)
	{
		CameraMovePos.Y = 0.0f;
	}


	// ��������
	if (Camera_ShakeCount >= 1)
	{
		Camera_ShakeTime += _Delta;

		if (Camera_ShakeTime > Camera_ShakeCycle)
		{
			Camera_ShakeTime = 0.0f;


			++Camera_ShakeNumber;

			float4 ShakeAddPos = float4::ZERO;

			switch (Camera_ShakeNumber)
			{
			case 1:
				ShakeAddPos = float4{ -Camera_ShakeMagnitude , -Camera_ShakeMagnitude };
				break;
			case 2:
				ShakeAddPos = float4{ Camera_ShakeMagnitude * 2.0f , Camera_ShakeMagnitude * 2.0f };
				break;
			case 3:
				ShakeAddPos = float4{ -Camera_ShakeMagnitude * 2.0f , 0.0f };
				break;
			case 4:
				ShakeAddPos = float4{ Camera_ShakeMagnitude * 2.0f , -Camera_ShakeMagnitude * 2.0f };
				break;
			case 5:
				ShakeAddPos = float4{ -Camera_ShakeMagnitude , Camera_ShakeMagnitude };
				break;
			default:
				break;
			}

			if (5 == Camera_ShakeNumber)
			{
				Camera_ShakeNumber = 0;
				--Camera_ShakeCount;
			}

			if (0 == Camera_ShakeCount)
			{
				Camera_ShakeMagnitude = 3.0f;
			}

			CameraMovePos += ShakeAddPos;
		}
	}



	CameraPtr->AddPos(CameraMovePos);
}