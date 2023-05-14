#include "PauseLevel.h"
#include "BackGround.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include <Windows.h>

PauseLevel::PauseLevel() 
{
}

PauseLevel::~PauseLevel() 
{
}

void PauseLevel::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("PauseScreens.bmp", float4{ 2 , 2 }, float4{ 256 , 240 });
}

void PauseLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("VegetableValley11");
	}
}