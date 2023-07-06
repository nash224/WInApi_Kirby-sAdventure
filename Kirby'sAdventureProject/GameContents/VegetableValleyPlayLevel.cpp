#include "VegetableValleyPlayLevel.h"
#include "ContentsEnum.h"



#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "BackGround.h"
#include "GameEffect.h"
#include "UIManager.h"
#include "Kirby.h"
#include "Enemy.h"



bool VegetableValleyPlayLevel::PrevLevelTriggerOn = false;
bool VegetableValleyPlayLevel::NextLevelTriggerOn = false;
bool VegetableValleyPlayLevel::IsStageEnd = false;
bool VegetableValleyPlayLevel::IsPlayerEnter = false;
bool VegetableValleyPlayLevel::IsPlayerMiss = false;
bool VegetableValleyPlayLevel::IsFadeDone = false;
bool VegetableValleyPlayLevel::IsChangeLevel = false;;
bool VegetableValleyPlayLevel::ChangeClearDoor = false;


float VegetableValleyPlayLevel::SoundVol = 0.0f;
GameEngineSoundPlayer VegetableValleyPlayLevel::BGM_Player;
bool VegetableValleyPlayLevel::IsBGM_On = false;
std::string VegetableValleyPlayLevel::BGMFileName = "";


int VegetableValleyPlayLevel::Camera_ShakeCount = 0;
float VegetableValleyPlayLevel::Camera_ShakeMagnitude = 3.0f;


bool VegetableValleyPlayLevel::Level_MenuOpenValue = false;
bool VegetableValleyPlayLevel::Level_SwitchBitMapRenderValue = false;
bool VegetableValleyPlayLevel::Level_DebugRenderValue = false;
int VegetableValleyPlayLevel::Level_DebugRenderXPos = 0;
float VegetableValleyPlayLevel::UpdateTime = 0.0f;


VegetableValleyPlayLevel::VegetableValleyPlayLevel() 
{
}

VegetableValleyPlayLevel::~VegetableValleyPlayLevel() 
{
}


// ��� ������ ��� �Լ�
void VegetableValleyPlayLevel::CreateAndSetupBackgroundEffectRenderer(
	const std::string& _AnimationName,
	const std::string& _FileName,
	int _StartFrame, int _EndFrame,
	float4 _Pos, float _Ratio,
	float _Inter/* = 0.1f*/, bool _Loop/* = true*/)
{
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	GameEngineRenderer* Render = LevelEffect->CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == Render)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	Render->CreateAnimation(_AnimationName, _FileName, _StartFrame, _EndFrame, _Inter, _Loop);
	Render->SetRenderPos(_Pos);
	Render->SetScaleRatio(_Ratio);
	Render->ChangeAnimation(_AnimationName);
}



// ������ �ʱ� ���� �� ī�޶� ��ġ
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



// �� ������ �Լ�
void VegetableValleyPlayLevel::CheckRespawnEnemy()
{
	for (int i = 0; i < LevelEnemy.size(); i++)
	{
		Enemy* Enemy = LevelEnemy[i];
		Enemy->RespawnTrigger();
	}
}


// ��� ���
void VegetableValleyPlayLevel::RePlayBGM()
{
	BGM_Player = GameEngineSound::SoundPlay(LevelBgmFileName);
	BGMFileName = LevelBgmFileName;
	IsBGM_On = true;
}




// ī�޶� ����
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



	// ī�޶� �� ������ ���� �������� ��
	if (0 == Camera_ShakeCount)
	{
		float4 BoundaryCameraPos = float4::ZERO;

		if (CameraFrontCheckPos.X < 0.0f)
		{
			CameraPtr->SetPos(float4{ 0.0f , CameraPos.Y });
		}
		if (CameraFrontCheckPos.Y < 0.0f)
		{
			CameraPtr->SetPos(float4{ CameraPos.X , 0.0f });
		}

		if (CameraBackCheckPos.X > BackGroundScale.X)
		{
			CameraPtr->SetPos(float4{ BackGroundScale.X - WinScale.X , CameraPos.Y });
		}
		if (CameraPos.Y + WinScale.Y > BackGroundScale.Y + CurrentUIScale.Y)
		{
			CameraPtr->SetPos(float4{ CameraPos.X  , BackGroundScale.Y - WinScale.Y + CurrentUIScale.Y });
		}
	}
}








// ���� ����
void VegetableValleyPlayLevel::LevelDebugShortcut(float _Delta)
{
	// ����� ������ ��ȯŰ
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		if (false == Level_DebugRenderValue && false == Level_SwitchBitMapRenderValue)
		{
			Level_MenuOpenValue = !Level_MenuOpenValue;
		}

		if (false == Level_MenuOpenValue)
		{
			Level_DebugRenderValue = false;
			Level_SwitchBitMapRenderValue = false;
		}
	}

	if (true == Level_MenuOpenValue)
	{
		// ����� ������ ��ȯŰ
		if (true == GameEngineInput::IsDown(VK_F2))
		{
			Level_DebugRenderValue = !Level_DebugRenderValue;
			Level_SwitchBitMapRenderValue = false;
		}


		// ��Ʈ��
		if (true == GameEngineInput::IsDown(VK_F3))
		{
			Level_SwitchBitMapRenderValue = !Level_SwitchBitMapRenderValue;
			Level_DebugRenderValue = false;
		}

		// �浹
		if (true == GameEngineInput::IsDown(VK_F4))
		{
			CollisionDebugRenderSwitch();
		}


		SwitchRenders();
	}



	if (false == Level_DebugRenderValue)
	{
		return;
	}



	// ����
	if ("" != NextLevelName)
	{
		if (true == GameEngineInput::IsDown(VK_F6))
		{
			NextLevelTriggerOn = false;
			GameEngineCore::ChangeLevel(NextLevelName);
		}
	}


	if (float4::ZERO != KirbyShortCutPos)
	{
		if (true == GameEngineInput::IsDown(VK_F7))
		{
			GameEngineCamera* MainCameraPtr = GetMainCamera();
			if (nullptr == MainCameraPtr)
			{
				MsgBoxAssert("ī�޶� NUll �Դϴ�.");
				return;
			}

			float4 WinScale = GameEngineWindow::MainWindow.GetScale();

			LevelPlayer->SetPos(KirbyShortCutPos);
			MainCameraPtr->SetPos(float4{ BackGroundScale.X - WinScale.X , 0.0f });
		}
	}




	// ī�޶� Shake
	if (true == GameEngineInput::IsDown(VK_F8))
	{
		++Camera_ShakeCount;
	}


	// Volume ����
	SoundVolPressKeyTime += _Delta;

	if (SoundVolPressKeyTime > SoundVol_KeyDownCycle)
	{
		if (true == GameEngineInput::IsPress(VK_OEM_6))
		{
			if (SoundVol < MAX_VOLUME_AMOUNT)
			{
				SoundVol += SoundVol_OneTime_AmountOfChange;

				if (SoundVol > 20.0f)
				{
					SoundVol = 1.0f;
				}
			}

			GameEngineSound::SetGlobalVolume(SoundVol);
			BGM_Player.SetVolume(1.0f);

			SoundVolPressKeyTime = 0.0f;
		}
		else if (true == GameEngineInput::IsPress(VK_OEM_4))
		{
			if (SoundVol > 0.0f)
			{
				SoundVol -= SoundVol_OneTime_AmountOfChange;

				if (SoundVol < 0.0f)
				{
					SoundVol = 0.0f;
				}
			}

			GameEngineSound::SetGlobalVolume(SoundVol);
			BGM_Player.SetVolume(1.0f);

			SoundVolPressKeyTime = 0.0f;
		}
	}

}


// ����� ������
void VegetableValleyPlayLevel::DebugRender(float _Delta)
{
	if (false == Level_MenuOpenValue)
	{
		return;
	}

	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	int TextRenderNum = 0;

	if (false == Level_DebugRenderValue && false == Level_SwitchBitMapRenderValue)
	{
		OpenMenuRender(dc, TextRenderNum);
		return;
	}
	else if (true == Level_DebugRenderValue)
	{
		DevModeRender(dc, TextRenderNum, _Delta);
		return;
	}
	else if (true == Level_SwitchBitMapRenderValue)
	{
		ColAndBitMapRender(dc, TextRenderNum);
		return;
	}
}



// ���� �޴�
void VegetableValleyPlayLevel::OpenMenuRender(HDC _HDC, int& _RenderNumber)
{
	if (nullptr == _HDC)
	{
		MsgBoxAssert("�ڵ��� �ҷ����� ���߽��ϴ�.");
		return;
	}


	{
		std::string Text = "";
		Text += "F1 : �ڷΰ���";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "F2 : ������ ���";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "F3 : ��Ʈ�� ��ȯ";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "F4 : �浹 ���� ��ȯ";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}


// ������ ���
void VegetableValleyPlayLevel::DevModeRender(HDC _HDC, int& _RenderNumber, float _Delta)
{

	{
		std::string Text = " F2 : �ڷ� ����";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = " F3 : ��Ʈ�� ��ȯ";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "F4 : �浹 ���� ��ȯ";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}



	if ("" != NextLevelName)
	{
		std::string Text = "";
		Text += "F6 : ���� ������ �̵�";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}



	if (float4::ZERO != KirbyShortCutPos)
	{
		std::string Text = "";
		Text += "F7 : ����";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}



	{
		std::string Text = "";
		Text += "F8 : ���� ��û";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	++_RenderNumber;


	{
		std::string Text = "";
		Text += "������ : ";

		UpdateTime += _Delta;
		if (UpdateTime >= 1.0f)
		{
			UpdateTime = 0.0f;

			FPSText = 1.0f / _Delta;
		}
		Text += std::to_string(static_cast<int>(FPSText));
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}



	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 CameraPos = MainCameraPtr->GetPos();



	{
		std::string Text = "";
		Text += "ī�޶� X Pos : ";

		Text += std::to_string(CameraPos.iX());
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "ī�޶� Y Pos : ";

		Text += std::to_string(CameraPos.iY());
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "���� ���� : ";

		Text += std::to_string(SoundVol);
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

}

// ��Ʈ�� ����� ������
void VegetableValleyPlayLevel::ColAndBitMapRender(HDC _HDC, int& _RenderNumber)
{
	{
		std::string Text = " F2 : ������ ���";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "F3 : �ڷΰ���";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "F4 : �浹 ���� ��ȯ";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}


