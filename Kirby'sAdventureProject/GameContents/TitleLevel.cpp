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
	LevelBackGround->init("TitleScreen.bmp", "Resources\\KirbyTest\\", float4{ 0 , 0 }, float4{ 256 , 240 });
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