#include "VegetableValleyIntro.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>


#include "GlobalContents.h"
#include "BackGround.h"


VegetableValleyIntro::VegetableValleyIntro()
{
}

VegetableValleyIntro::~VegetableValleyIntro()
{

}


void VegetableValleyIntro::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValleyIntro.bmp", "Resources\\Map");



	// 사운드 로드
	GlobalContents::SoundFileLoad("03_Plains_Level.mp3", "Resources\\SoundResources\\SoundTrack");
}

void VegetableValleyIntro::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}


	if (true == GameEngineInput::IsDown('A') ||
		true == GameEngineInput::IsDown('D') || 
		true == GameEngineInput::IsDown('S') || 
		true == GameEngineInput::IsDown('W'))
	{
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
}

void VegetableValleyIntro::LevelEnd(GameEngineLevel* _NextLevel) { }