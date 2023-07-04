#include "TitleLevel.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>


#include "GlobalContents.h"
#include "BackGround.h"
#include "KirbyBanner.h"




TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	// ���� �ʱ� ����
	GameEngineSound::SetGlobalVolume(0.5f);
	SoundVol = GameEngineSound::GetGlobalVolume();


	// ���
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("����� �������� ���߽��ϴ�.");
		return;
	}

	LevelBackGround->init("KirbyTitle.bmp", "Resources\\Map");

	float4 BackGroundScale = LevelBackGround->GetBackGroundScale();


	// ���
	KirbyBanner* BannerPtr = GameEngineLevel::CreateActor<KirbyBanner>(UpdateOrder::BackGroundEffect);
	if (nullptr == BannerPtr)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	BannerPtr->init(BackGroundScale.Half());



	// ���� �ε�
	GlobalContents::SoundFileLoad("02_Title_Screen.mp3", "Resources\\SoundResources\\SoundTrack");





	// �����
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	Level_DebugRenderXPos = WinScale.iX() - 200;
	ItUseDebugBitMap = false;
}





void TitleLevel::Update(float _DeltaTime)
{
	LevelDebugShortcut(_DeltaTime);


	if (true == GameEngineInput::IsDown('W') ||
		GameEngineInput::IsDown('S') || 
		GameEngineInput::IsDown('A') || 
		GameEngineInput::IsDown('D'))
	{
		GlobalContents::WhiteFadeOut(this);
	}
	
	
	if (true == IsFadeDone)
	{
		IsFadeDone = false;
		GameEngineCore::ChangeLevel("VegetableValleyIntro");
	}
}



void TitleLevel::Render(float _Delta)
{
	DebugRender(_Delta);
}



void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (false == IsBGM_On)
	{
		BGM_Player = GameEngineSound::SoundPlay("02_Title_Screen.mp3");
		IsBGM_On = true;
	}
}



void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}