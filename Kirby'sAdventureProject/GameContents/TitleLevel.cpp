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
	// 사운드 초기 설정
	GameEngineSound::SetGlobalVolume(0.5f);
	SoundVol = GameEngineSound::GetGlobalVolume();


	// 배경
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("배경을 생성하지 못했습니다.");
		return;
	}

	LevelBackGround->init("KirbyTitle.bmp", "Resources\\Map");

	float4 BackGroundScale = LevelBackGround->GetBackGroundScale();


	// 배너
	KirbyBanner* BannerPtr = GameEngineLevel::CreateActor<KirbyBanner>(UpdateOrder::BackGroundEffect);
	if (nullptr == BannerPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	BannerPtr->init(BackGroundScale.Half());



	// 사운드 로드
	GlobalContents::SoundFileLoad("02_Title_Screen.mp3", "Resources\\SoundResources\\SoundTrack");





	// 디버그
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