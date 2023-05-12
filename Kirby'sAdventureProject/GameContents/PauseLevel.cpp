#include "PauseLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include <Windows.h>

PauseLevel::PauseLevel() 
{
}

PauseLevel::~PauseLevel() 
{
}


void PauseLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}