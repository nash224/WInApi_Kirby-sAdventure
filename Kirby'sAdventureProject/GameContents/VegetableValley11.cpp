#include "VegetableValley11.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

// contents
#include "Kirby.h"
#include "BackGround.h"
#include "GameEffect.h"

VegetableValley11::VegetableValley11() 
{
}

VegetableValley11::~VegetableValley11() 
{

}

/* texture type
	CreateAnimation("HillProjectionEffect", "CloudAndWater12x3_8x8.bmp", 0, 2, 0.15f, true);
	CreateAnimation("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, 0.15f, true);
	CreateAnimation("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, 0.15f, true);

*/

void VegetableValley11::Start() 
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1_1.bmp","VegetableValley1_1Pixel.bmp", "Resources\\Map");

	LevelEffect = GameEngineLevel::CreateActor<GameEffect>();
	LevelEffect->LoadBackGroundEffect("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);


	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	LevelPlayer->SetGroundTexture("VegetableValley1_1Pixel.bmp");
}


void VegetableValley11::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValley12");
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}



	if (LevelPlayer->GetPos().iX() >= 3048.0f)
	{
		GameEngineCore::ChangeLevel("VegetableValley12");
	}
}

void VegetableValley11::Render() 
{

}

void VegetableValley11::Release() 
{

}

void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) { }