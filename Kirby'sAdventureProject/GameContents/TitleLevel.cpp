#include "TitleLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('Y'))
	{
		GameEngineCore::ChangeLevel("VegetableValley11");
	}
}