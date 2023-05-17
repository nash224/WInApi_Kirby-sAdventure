#include "VegetableValley12.h"
#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


VegetableValley12::VegetableValley12() 
{
}

VegetableValley12::~VegetableValley12() 
{
}

void VegetableValley12::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1.bmp", "Resources\\KirbyTest\\", float4{ 2 , 172 }, float4{ 1016 , 168 });

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void VegetableValley12::Update(float _Delta)
{




	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (LevelPlayer->GetPos().iX() >= LevelBackGround->GetScale().iX() - LevelPlayer->GetScale().iX())
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

void VegetableValley12::LevelStart(GameEngineLevel* _PrevLevel) { }

void VegetableValley12::LevelEnd(GameEngineLevel* _NextLevel) { }
