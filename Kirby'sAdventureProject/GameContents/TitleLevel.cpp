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
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("KirbyTitle.bmp", "Resources\\Map");
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('W') ||
		GameEngineInput::IsDown('S') || 
		GameEngineInput::IsDown('A') || 
		GameEngineInput::IsDown('D'))
	{
		GameEngineCore::ChangeLevel("VegetableValleyIntro");
	}
}