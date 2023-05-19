#include "VegetableValleyIntro.h"

#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


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

	//LevelPlayer = GameEngineLevel::CreateActor<Player>();
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

void VegetableValleyIntro::Render()
{

}

void VegetableValleyIntro::Release()
{

}

void VegetableValleyIntro::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void VegetableValleyIntro::LevelEnd(GameEngineLevel* _NextLevel) { }