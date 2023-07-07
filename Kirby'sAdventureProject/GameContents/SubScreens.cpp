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
	// ��� ����
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelBackGround->init("MuseumSubScreen.bmp" , "Resources\\Map");


	// Player�� LevelStart �� �� ������ ����
	SetName("BonusGame");
}


void SubScreens::Update(float _Delta)
{
	if (false == FadeObject::IsFadeInDone)
	{
		return;
	}


	// ���� �̵�
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



// ����� ����
void SubScreens::Render(float _Delta)
{
	if (false == Level_DebugRenderValue)
	{
		return;
	}


	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("����۸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();
	if (nullptr == dc)
	{
		MsgBoxAssert("�ڵ��� �ҷ����� ���߽��ϴ�.");
		return;
	}

	{
		UpdateTime += _Delta;


		std::string Text = "";
		Text += "������ : ";
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
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
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

