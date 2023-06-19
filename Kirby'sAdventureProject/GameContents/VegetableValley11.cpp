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
#include "BrontoBurt.h"
#include "WaddleDoo.h"
#include "HotHead.h"
#include "Sparky.h"
#include "PlayUI.h"

#include <map>


VegetableValley11::VegetableValley11() 
{
}

VegetableValley11::~VegetableValley11() 
{

}


void VegetableValley11::Start() 
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	LevelBackGround->init("VegetableValley1_1.bmp","VegetableValley1_1Pixel.bmp", "Resources\\Map");

	BitMapFileName = "VegetableValley1_1Pixel.bmp";

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	BackGroundScale = Texture->GetScale();


	LevelEffect = GameEngineLevel::CreateActor<GameEffect>(UpdateOrder::BackGroundEffect);
	LevelEffect->LoadBackGroundEffect("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);



	GameEngineWindowTexture* MapTexture = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	if (nullptr == MapTexture)
	{
		MsgBoxAssert("비트맵 로드에 실패했습니다.");
		return;
	}

	float4 BackScale = MapTexture->GetScale();
	SetLevelBackgroundScale(BackScale);








	// 몹1
	WaddleDee* WaddleDee1 = GameEngineLevel::CreateActor<WaddleDee>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	WaddleDee1->init("VegetableValley1_1Pixel.bmp", NormalState::Walk ,  float4{ 892, 336 });
	LevelEnemy.insert(std::make_pair("WaddleDee1", WaddleDee1));


	// 파워몹 1
	WaddleDoo* WaddleDoo1 = GameEngineLevel::CreateActor<WaddleDoo>(UpdateOrder::Monster);
	if (nullptr == WaddleDoo1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	WaddleDoo1->init("VegetableValley1_1Pixel.bmp", WaddleDooState::Walk, float4{ 1200, 386 });
	LevelEnemy.insert(std::make_pair("WaddleDoo1", WaddleDoo1));


	// 공중몹 1-2
	BrontoBurt* BrontoBurt2 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt2)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BrontoBurt2->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1760, 130 });
	LevelEnemy.insert(std::make_pair("BrontoBurt2", BrontoBurt2));


	// 공중몹 1-2
	BrontoBurt* BrontoBurt3 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt3)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BrontoBurt3->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1860, 130 });
	LevelEnemy.insert(std::make_pair("BrontoBurt3", BrontoBurt3));



	// 공중몹 1-2
	BrontoBurt* BrontoBurt4 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt4)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BrontoBurt4->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1960, 130 });
	LevelEnemy.insert(std::make_pair("BrontoBurt4", BrontoBurt4));



	// 파워몹 2
	HotHead* HotHead1 = GameEngineLevel::CreateActor<HotHead>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	HotHead1->init("VegetableValley1_1Pixel.bmp", HotHeadState::Walk, float4{ 2700, 386 });
	LevelEnemy.insert(std::make_pair("HotHead1", HotHead1));



	// 파워몹 3
	Sparky* Sparky1 = GameEngineLevel::CreateActor<Sparky>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	Sparky1->init("VegetableValley1_1Pixel.bmp", SparkyState::Idle, float4{ 2000, 386 });
	LevelEnemy.insert(std::make_pair("Sparky1", Sparky1));










	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}

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

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValley12");
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}

	CheckRespawnEnemy();
}



void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(float4{ 200.0f, 200.0f });
}


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) { }

void VegetableValley11::Render(float _Delta)
{
	UpdateTime += _Delta;

	std::string Text = "";
	Text += "프레임 : ";
	if (UpdateTime >= 1.0f)
	{
		UpdateTime = 0.0f;

		FPSText = 1.0f / _Delta;
	}
	Text += std::to_string(static_cast<int>(FPSText));
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
}