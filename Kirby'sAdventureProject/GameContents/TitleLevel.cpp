#include "TitleLevel.h"
#include "BackGround.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	GameEngineSound::SetGlobalVolume(0.25f);

	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("KirbyTitle.bmp", "Resources\\Map");

	if (nullptr == GameEngineSound::FindSound("02_Title_Screen.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\SoundResources\\SoundTrack");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("02_Title_Screen.mp3"));
	}
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		BGMPlayer.Stop();
	}



	if (true == GameEngineInput::IsDown('W') ||
		GameEngineInput::IsDown('S') || 
		GameEngineInput::IsDown('A') || 
		GameEngineInput::IsDown('D'))
	{
		GameEngineCore::ChangeLevel("VegetableValleyIntro");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineSound::SoundPlay("02_Title_Screen.mp3");
}


void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}