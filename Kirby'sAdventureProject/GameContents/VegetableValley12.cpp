#include "VegetableValley12.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "Kirby.h"
#include "PlayUI.h"
#include "BackGround.h"


VegetableValley12::VegetableValley12() 
{
}

VegetableValley12::~VegetableValley12() 
{
}

void VegetableValley12::Start()
{
	// 배경 생성
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("레벨 배경화면 생성에 실패했습니다.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValley1_2.bmp", "VegetableValley1_2Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("비트맵 파일을 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();

	BitMapFileName = "VegetableValley1_2Pixel.bmp";



	EnemySummon();

	// UI생성
	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}



	// 사운드 로드
	GlobalContents::SoundFileLoad("06_Underground_Level.mp3", "Resources\\SoundResources\\SoundTrack");
}




void VegetableValley12::Update(float _Delta)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 불러오지 못했습니다.");
		return;
	}


	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValleyHub");
	}

	if (true == GameEngineInput::IsDown('6'))
	{
		GameEngineCamera* MainCameraPtr = GetMainCamera();
		if (nullptr == MainCameraPtr)
		{
			MsgBoxAssert("카메라가 NUll 입니다.");
			return;
		}

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();

		LevelPlayer->SetPos(float4{ 3457.0f , 383.0f });
		MainCameraPtr->SetPos(float4{ BackGroundScale.X - WinScale.X , 0.0f });
	}



	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValleyHub");

		return;
	}


	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}



	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}


	CheckRespawnEnemy();
}


void VegetableValley12::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return;
	}


	{
		UpdateTime += _Delta;


		std::string Text = "";
		Text += "프레임 : ";
		if (UpdateTime >= 1.0f)
		{
			UpdateTime = 0.0f;

			FPSText = 1.0f / _Delta;
		}
		Text += std::to_string(FPSText);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
	}
}




void VegetableValley12::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	SetPlayerPosAndCameraPos(float4{ 83.0f, 384.0f }, float4::ZERO);



	// 사운드 재생
	GameEngineSound::SoundPlay("06_Underground_Level.mp3");



	// 스테이지 끝남
	IsStageEnd = true;

	GlobalContents::FadeIn(this);
}

void VegetableValley12::LevelEnd(GameEngineLevel* _NextLevel) 
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}

