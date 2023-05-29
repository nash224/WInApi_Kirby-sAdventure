#include "VegetableValley11.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

// contents
#include "BackGround.h"
#include "GameEffect.h"
#include "Kirby.h"
#include "WaddleDee.h"
#include "PlayUIManager.h"

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

	// 몹1
	WaddleDee* WaddleDee1 = GameEngineLevel::CreateActor<WaddleDee>();
	WaddleDee1->init("VegetableValley1_1Pixel.bmp", float4{ 600, 400 });
	LevelEnemy.insert(std::make_pair("WaddleDee1", WaddleDee1));


	GameEngineLevel::CreateActor<PlayUIManager>();

	GameEngineWindowTexture* Tetxure = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	BackGroundScale = Tetxure->GetScale();
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

	float4 WinHalfScale = GameEngineWindow::MainWindow.GetScale().Half();

	Enemy* Waddle1 = LevelEnemy.find("WaddleDee1")->second;
	if (false == Waddle1->IsUpdate() && WinHalfScale.X >= LevelPlayer->GetPos().X - Waddle1->RespawnLocation.X)
	{
		LevelEnemy.find("WaddleDee1")->second->On();
	}
}


void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) { }