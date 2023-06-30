#include "TitleLevel.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>


#include "GlobalContents.h"
#include "BackGround.h"
#include "FadeObject.h"
#include "KirbyBanner.h"




TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	GameEngineSound::SetGlobalVolume(0.25f);

	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("����� �������� ���߽��ϴ�.");
		return;
	}

	LevelBackGround->init("KirbyTitle.bmp", "Resources\\Map");

	float4 BackGroundScale = LevelBackGround->GetBackGroundScale();


	KirbyBanner* BannerPtr = GameEngineLevel::CreateActor<KirbyBanner>(UpdateOrder::BackGroundEffect);
	if (nullptr == BannerPtr)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	BannerPtr->init(BackGroundScale.Half());



	// ���� �ε�
	GlobalContents::SoundFileLoad("02_Title_Screen.mp3", "Resources\\SoundResources\\SoundTrack");
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('W') ||
		GameEngineInput::IsDown('S') || 
		GameEngineInput::IsDown('A') || 
		GameEngineInput::IsDown('D'))
	{
		GlobalContents::WhiteFadeOut(this);
	}
	
	
	if (true == FadeObject::IsFadeDone)
	{
		GameEngineCore::ChangeLevel("VegetableValleyIntro");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (false == IsBGMOn)
	{
		BGMPlayer = GameEngineSound::SoundPlay("02_Title_Screen.mp3");
		IsBGMOn = true;
	}

}


void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (true == IsBGMOn)
	{
		BGMPlayer.Stop();
		IsBGMOn = false;
	}
}