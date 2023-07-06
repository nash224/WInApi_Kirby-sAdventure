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


// 배경 렌더러 양산 함수
void VegetableValleyPlayLevel::CreateAndSetupBackgroundEffectRenderer(
	const std::string& _AnimationName,
	const std::string& _FileName,
	int _StartFrame, int _EndFrame,
	float4 _Pos, float _Ratio,
	float _Inter/* = 0.1f*/, bool _Loop/* = true*/)
{
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	GameEngineRenderer* Render = LevelEffect->CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == Render)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	Render->CreateAnimation(_AnimationName, _FileName, _StartFrame, _EndFrame, _Inter, _Loop);
	Render->SetRenderPos(_Pos);
	Render->SetScaleRatio(_Ratio);
	Render->ChangeAnimation(_AnimationName);
}



// 리스폰 초기 방향 및 카메라 위치
void VegetableValleyPlayLevel::SetPlayerPosAndCameraPos(const float4& _PlayerPos, const float4& _CameraPos)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라가 NUll 입니다.");
		return;
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);


	LevelPlayer->SetPos(_PlayerPos);
	MainCameraPtr->SetPos(_CameraPos);
}



// 몹 리스폰 함수
void VegetableValleyPlayLevel::CheckRespawnEnemy()
{
	for (int i = 0; i < LevelEnemy.size(); i++)
	{
		Enemy* Enemy = LevelEnemy[i];
		Enemy->RespawnTrigger();
	}
}


// 브금 재생
void VegetableValleyPlayLevel::RePlayBGM()
{
	BGM_Player = GameEngineSound::SoundPlay(LevelBgmFileName);
	BGMFileName = LevelBgmFileName;
	IsBGM_On = true;
}




// 카메라 제어
void VegetableValleyPlayLevel::CameraFocus(float _Delta)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GameEngineCamera* CameraPtr = GetMainCamera();
	if (nullptr == CameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return;
	}

	float4 CameraPos = CameraPtr->GetPos();

	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI를 불러오지 못했습니다.");
		return;
	}

	float4 CurrentUIScale = LevelUIManager->UIScale;


	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 불러오지 못했습니다.");
		return;
	}

	float4 PlayerMovePos = LevelPlayer->KirbyMovePos;
	float4 PlayerPos = LevelPlayer->GetPos();



	CameraFrontCheckPos = CameraPos;
	CameraBackCheckPos = float4{ CameraPos.X + WinScale.X , CameraPos.Y + WinScale.Y - CurrentUIScale.Y };

	float4 CameraMovePos = PlayerMovePos;

	// 커비가 오른쪽 방향일 때, 화면의 중앙을 넘어가면 움직임
	if (PlayerPos.X < CameraFrontCheckPos.X + WinScale.Half().X && PlayerMovePos.X > 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// 커비가 왼쪽 방향일 때, 화면의 1/4 지점을 넘어가면 움직임
	if (PlayerPos.X > CameraFrontCheckPos.X + WinScale.Half().Half().X && PlayerMovePos.X < 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// 커비가 윗쪽 방향일 때, 화면의 1/4 지점을 넘어가면 움직임
	if (PlayerPos.Y > CameraFrontCheckPos.Y + (WinScale - CurrentUIScale).Half().Half().Y && PlayerMovePos.Y < 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}

	// 커비가 아랫쪽 방향일 때, UI화면을 뺀 윈도우화면의 3/4 지점을 넘어가면 움직임
	if (PlayerPos.Y < CameraBackCheckPos.Y - (WinScale - CurrentUIScale).Half().Half().Y && PlayerMovePos.Y > 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}



	// 왼쪽 위로 나가지 못하게 막음
	if (CameraPos.X + PlayerMovePos.X < 0.0f || CameraBackCheckPos.X + PlayerMovePos.X > BackGroundScale.X)
	{
		CameraMovePos.X = 0.0f;
	}

	// 오른쪽 아래로 나가지 못하게 막음
	if (CameraPos.Y + PlayerMovePos.Y < 0.0f || CameraBackCheckPos.Y + PlayerMovePos.Y > BackGroundScale.Y)
	{
		CameraMovePos.Y = 0.0f;
	}






	// 지진로직
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



	// 카메라가 맵 밖으로 절때 못나가게 함
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








// 레벨 숏컷
void VegetableValleyPlayLevel::LevelDebugShortcut(float _Delta)
{
	// 디버그 렌더링 전환키
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
		// 디버그 렌더링 전환키
		if (true == GameEngineInput::IsDown(VK_F2))
		{
			Level_DebugRenderValue = !Level_DebugRenderValue;
			Level_SwitchBitMapRenderValue = false;
		}


		// 비트맵
		if (true == GameEngineInput::IsDown(VK_F3))
		{
			Level_SwitchBitMapRenderValue = !Level_SwitchBitMapRenderValue;
			Level_DebugRenderValue = false;
		}

		// 충돌
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



	// 숏컷
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
				MsgBoxAssert("카메라가 NUll 입니다.");
				return;
			}

			float4 WinScale = GameEngineWindow::MainWindow.GetScale();

			LevelPlayer->SetPos(KirbyShortCutPos);
			MainCameraPtr->SetPos(float4{ BackGroundScale.X - WinScale.X , 0.0f });
		}
	}




	// 카메라 Shake
	if (true == GameEngineInput::IsDown(VK_F8))
	{
		++Camera_ShakeCount;
	}


	// Volume 조절
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


// 디버깅 렌더러
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



// 오픈 메뉴
void VegetableValleyPlayLevel::OpenMenuRender(HDC _HDC, int& _RenderNumber)
{
	if (nullptr == _HDC)
	{
		MsgBoxAssert("핸들을 불러오지 못했습니다.");
		return;
	}


	{
		std::string Text = "";
		Text += "F1 : 뒤로가기";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "F2 : 개발자 모드";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "F3 : 비트맵 전환";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "F4 : 충돌 렌더 전환";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}


// 개발지 모드
void VegetableValleyPlayLevel::DevModeRender(HDC _HDC, int& _RenderNumber, float _Delta)
{

	{
		std::string Text = " F2 : 뒤로 가기";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = " F3 : 비트맵 전환";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "F4 : 충돌 렌더 전환";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}



	if ("" != NextLevelName)
	{
		std::string Text = "";
		Text += "F6 : 다음 레벨로 이동";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}



	if (float4::ZERO != KirbyShortCutPos)
	{
		std::string Text = "";
		Text += "F7 : 숏컷";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}



	{
		std::string Text = "";
		Text += "F8 : 지진 요청";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	++_RenderNumber;


	{
		std::string Text = "";
		Text += "프레임 : ";

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
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return;
	}

	float4 CameraPos = MainCameraPtr->GetPos();



	{
		std::string Text = "";
		Text += "카메라 X Pos : ";

		Text += std::to_string(CameraPos.iX());
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "카메라 Y Pos : ";

		Text += std::to_string(CameraPos.iY());
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "사운드 볼륨 : ";

		Text += std::to_string(SoundVol);
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

}

// 비트맵 디버깅 렌더러
void VegetableValleyPlayLevel::ColAndBitMapRender(HDC _HDC, int& _RenderNumber)
{
	{
		std::string Text = " F2 : 개발자 모드";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "F3 : 뒤로가기";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "F4 : 충돌 렌더 전환";
		TextOutA(_HDC, Level_DebugRenderXPos, 2 + _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}


