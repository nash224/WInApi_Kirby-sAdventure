#include "SubScreens.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

// contents
#include "BackGround.h"
#include "Kirby.h"
#include "FadeObject.h"



SubScreens::SubScreens()
{
}

SubScreens::~SubScreens()
{

}


void SubScreens::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelBackGround->init("MuseumSubScreen.bmp" , "Resources\\Map");


	// Player가 LevelStart 할 때 터짐을 방지
	SetName("BonusGame");


	ItUseDebugBitMap = false;
}


void SubScreens::Update(float _Delta)
{
	if (false == FadeObject::IsFadeInDone)
	{
		return;
	}


	if (true == GameEngineInput::IsDown('W') ||
		true == GameEngineInput::IsDown('A') ||
		true == GameEngineInput::IsDown('S') ||
		true == GameEngineInput::IsDown('D') ||
		true == GameEngineInput::IsDown('X') ||
		true == GameEngineInput::IsDown('Z'))
	{
		GlobalContents::FadeOut(this);
	}

	if (true == IsFadeDone)
	{
		IsFadeDone = false;

		NextLevelTriggerOn = true;
	}

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValleyMuseum");
		return;
	}

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}
}




void SubScreens::Render(float _Delta)
{
	if (false == Level_DebugRenderValue)
	{
		return;
	}


	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

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


void SubScreens::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->Off();

	GlobalContents::FadeIn(this);
}


void SubScreens::LevelEnd(GameEngineLevel* _NextLevel)
{
	IsFadeDone = false;

	if (true == IsBGM_On)
	{
		BGM_Player.Stop();

		IsBGM_On = false;
	}
}

