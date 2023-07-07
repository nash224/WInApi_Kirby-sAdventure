#include "SubScreens.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>


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
	// 배경 생성
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelBackGround->init("MuseumSubScreen.bmp" , "Resources\\Map");


	// Player가 LevelStart 할 때 터짐을 방지
	SetName("BonusGame");
}


void SubScreens::Update(float _Delta)
{
	if (false == FadeObject::IsFadeInDone)
	{
		return;
	}


	// 레벨 이동
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



// 디버그 렌더
void SubScreens::Render(float _Delta)
{
	if (false == Level_DebugRenderValue)
	{
		return;
	}


	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("백버퍼를 불러오지 못했습니다.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();
	if (nullptr == dc)
	{
		MsgBoxAssert("핸들을 불러오지 못했습니다.");
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

