#include "VegetableValley12.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

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
	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValley1_2.bmp", "VegetableValley1_2Pixel.bmp", "Resources\\Map");
	BackGroundScale = Texture->GetScale();

	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	LevelPlayer->SetGroundTexture("VegetableValley1_2Pixel.bmp");
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

	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}

	if (2.0f <= GetLiveTime())
	{
		Grunt* NewGrunt = CreateActor<Grunt>();
		ResetLiveTime();
	}


	if (LevelPlayer->GetPos().iX() >= 3048.0f)
	{
		GameEngineCore::ChangeLevel("VegetableValley13");
	}
}


void VegetableValley12::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}

void VegetableValley12::LevelEnd(GameEngineLevel* _NextLevel) { }
