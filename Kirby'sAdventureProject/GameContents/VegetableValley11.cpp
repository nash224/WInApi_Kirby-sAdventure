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
#include "BroomHatter.h"
#include "Kabu.h"
#include "PoppyBrosJr.h"
#include "BrontoBurt.h"
#include "Scarfy.h"
#include "WaddleDoo.h"
#include "HotHead.h"
#include "Sparky.h"
#include "Togezo.h"
#include "SwordKnight.h"
#include "LaserBall.h"
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
		MsgBoxAssert("ºñÆ®¸Ê ·Îµå¿¡ ½ÇÆÐÇß½À´Ï´Ù.");
		return;
	}

	float4 BackScale = MapTexture->GetScale();
	SetLevelBackgroundScale(BackScale);








	// ¸÷1
	WaddleDee* WaddleDee1 = GameEngineLevel::CreateActor<WaddleDee>(UpdateOrder::Monster);
	WaddleDee1->init("VegetableValley1_1Pixel.bmp", NormalState::Walk ,  float4{ 600, 384 });
	LevelEnemy.insert(std::make_pair("WaddleDee1", WaddleDee1));

	// ¸÷2
	BroomHatter* BroomHatter1 = GameEngineLevel::CreateActor<BroomHatter>(UpdateOrder::Monster);
	BroomHatter1->init("VegetableValley1_1Pixel.bmp", NormalState::Idle, float4{ 500, 384 });
	LevelEnemy.insert(std::make_pair("BroomHatter1", BroomHatter1));

	// ¸÷3
	Kabu* Kabu1 = GameEngineLevel::CreateActor<Kabu>(UpdateOrder::Monster);
	Kabu1->init("VegetableValley1_1Pixel.bmp", NormalState::Idle, float4{ 400, 384 });
	LevelEnemy.insert(std::make_pair("Kabu1", Kabu1));

	// ¸÷ 4-1
	PoppyBrosJr* PoppyBrosJr1 = GameEngineLevel::CreateActor<PoppyBrosJr>(UpdateOrder::Monster);
	PoppyBrosJr1->init("VegetableValley1_1Pixel.bmp", NormalState::Idle, float4{ 900, 384 });
	LevelEnemy.insert(std::make_pair("PoppyBrosJr1", PoppyBrosJr1));

	// °øÁß¸÷ 1-1
	BrontoBurt* BrontoBurt1 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	BrontoBurt1->init("VegetableValley1_1Pixel.bmp", BrontoState::Idle , float4{ 900, 384 });
	LevelEnemy.insert(std::make_pair("BrontoBurt1", BrontoBurt1));

	// °øÁß¸÷ 1-2
	BrontoBurt* BrontoBurt2 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	BrontoBurt2->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 600, 130 });
	LevelEnemy.insert(std::make_pair("BrontoBurt2", BrontoBurt2));

	// °øÁß¸÷ 2
	Scarfy* Scarfy1 = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	Scarfy1->init("VegetableValley1_1Pixel.bmp", ScarfyState::Idle, float4{ 550, 220 });
	LevelEnemy.insert(std::make_pair("Scarfy1", Scarfy1));

	// ÆÄ¿ö¸÷ 1
	WaddleDoo* WaddleDoo1 = GameEngineLevel::CreateActor<WaddleDoo>(UpdateOrder::Monster);
	WaddleDoo1->init("VegetableValley1_1Pixel.bmp", WaddleDooState::Walk, float4{ 1200, 384 });
	LevelEnemy.insert(std::make_pair("WaddleDoo1", WaddleDoo1));

	// ÆÄ¿ö¸÷ 2
	HotHead* HotHead1 = GameEngineLevel::CreateActor<HotHead>(UpdateOrder::Monster);
	HotHead1->init("VegetableValley1_1Pixel.bmp", HotHeadState::Walk, float4{ 1300, 384 });
	LevelEnemy.insert(std::make_pair("HotHead1", HotHead1));

	// ÆÄ¿ö¸÷ 3
	Sparky* Sparky1 = GameEngineLevel::CreateActor<Sparky>(UpdateOrder::Monster);
	Sparky1->init("VegetableValley1_1Pixel.bmp", SparkyState::Idle, float4{ 1400, 384 });
	LevelEnemy.insert(std::make_pair("Sparky1", Sparky1));

	// ÆÄ¿ö¸÷ 4
	Togezo* Togezo1 = GameEngineLevel::CreateActor<Togezo>(UpdateOrder::Monster);
	Togezo1->init("VegetableValley1_1Pixel.bmp", TogezoState::Walk, float4{ 1100, 384 });
	LevelEnemy.insert(std::make_pair("Togezo1", Togezo1));

	// ÆÄ¿ö¸÷ 5
	SwordKnight* SwordKnight1 = GameEngineLevel::CreateActor<SwordKnight>(UpdateOrder::Monster);
	SwordKnight1->init("VegetableValley1_1Pixel.bmp", SwordKnightState::PendulumStride, float4{ 1250, 384 });
	LevelEnemy.insert(std::make_pair("SwordKnight1", SwordKnight1));

	// ÆÄ¿ö¸÷ 6
	LaserBall* LaserBall1 = GameEngineLevel::CreateActor<LaserBall>(UpdateOrder::Monster);
	LaserBall1->init("VegetableValley1_1Pixel.bmp", LaserBallState::Fly, float4{ 1250, 200 });
	LevelEnemy.insert(std::make_pair("LaserBall1", LaserBall1));


	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI »ý¼º¿¡ ½ÇÆÐÇß½À´Ï´Ù.");
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
		MsgBoxAssert("ÇÃ·¹ÀÌ¾î¸¦ ¼¼ÆÃÇØÁÖÁö ¾Ê¾Ò½À´Ï´Ù.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(float4{ 200.0f, 200.0f });
}


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) { }

void VegetableValley11::Render(float _Delta)
{
	UpdateTime += _Delta;

	std::string Text = "";
	Text += "ÇÁ·¹ÀÓ : ";
	if (UpdateTime >= 1.0f)
	{
		UpdateTime = 0.0f;

		FPSText = 1.0f / _Delta;
	}
	Text += std::to_string(static_cast<int>(FPSText));
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
}