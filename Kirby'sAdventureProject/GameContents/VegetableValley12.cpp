#include "VegetableValley12.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourceManager.h>

#include "Kirby.h"
#include "Grunt.h"
#include "BackGround.h"

VegetableValley12::VegetableValley12() 
{
}

VegetableValley12::~VegetableValley12() 
{
}

void VegetableValley12::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1_2.bmp", "Resources\\Map");

	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
}

void VegetableValley12::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValley13");
	}

	if (2.0f <= GetLiveTime())
	{
		Grunt* NewGrunt = CreateActor<Grunt>();
		ResetLiveTime();
	}


	if (LevelPlayer->GetPos().iX() >= 3048.0f - LevelPlayer->GetScale().iX())
	{
		GameEngineCore::ChangeLevel("VegetableValley13");
	}
}

void VegetableValley12::Render()
{

}

void VegetableValley12::Release()
{

}

void VegetableValley12::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}

void VegetableValley12::LevelEnd(GameEngineLevel* _NextLevel) { }
