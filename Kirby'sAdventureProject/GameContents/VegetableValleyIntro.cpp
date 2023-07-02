#include "VegetableValleyIntro.h"
#include "ContentsEnum.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>


#include "GlobalContents.h"
#include "VegetableValleyCutScene.h"
#include "FadeObject.h"
#include "BackGround.h"


VegetableValleyIntro::VegetableValleyIntro()
{
}

VegetableValleyIntro::~VegetableValleyIntro()
{

}


void VegetableValleyIntro::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	LevelBackGround->init("VegetableValleyIntro.bmp", "Resources\\Map");


	LevelScene = GameEngineLevel::CreateActor<VegetableValleyCutScene>(UpdateOrder::BackGroundEffect);
	if (nullptr == LevelScene)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	


	// 사운드 로드
	GlobalContents::SoundFileLoad("03_Plains_Level.mp3", "Resources\\SoundResources\\SoundTrack");
}

void VegetableValleyIntro::Update(float _Delta)
{
	if (false == FadeObject::IsFadeInDone)
	{
		return;
	}



	if (true == GameEngineInput::IsDown('A') ||
		true == GameEngineInput::IsDown('D') || 
		true == GameEngineInput::IsDown('S') || 
		true == GameEngineInput::IsDown('W'))
	{
		GlobalContents::WhiteFadeOut(this);
	}


	if (nullptr == LevelScene)
	{
		MsgBoxAssert("씬이 존재하지 않습니다.");
		return;
	}

	

	if (true == LevelScene->SceneEnd)
	{
		LevelScene->SceneEnd = false;

		GlobalContents::WhiteFadeOut(this); 
	}

	if (true == IsFadeDone)
	{
		IsFadeDone = false;

		GameEngineCore::ChangeLevel("VegetableValleyHub");
	}

}

void VegetableValleyIntro::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (false == IsBGM_On)
	{
		BGM_Player = GameEngineSound::SoundPlay("03_Plains_Level.mp3");

		IsBGM_On = true;
	}


	GlobalContents::WhiteFadeIn(this);
}

void VegetableValleyIntro::LevelEnd(GameEngineLevel* _NextLevel) { }