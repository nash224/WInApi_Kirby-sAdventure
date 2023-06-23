#include "VegetableValley11.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>


// contents
#include "WaddleDee.h"
#include "BrontoBurt.h"
#include "WaddleDoo.h"
#include "HotHead.h"
#include "Sparky.h"
#include "SwordKnight.h"

#include <vector>


void VegetableValley11::EnemySummon()
{
	LevelEnemy.reserve(9);

	// 몹1
	WaddleDee* WaddleDee1 = GameEngineLevel::CreateActor<WaddleDee>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	WaddleDee1->init("VegetableValley1_1Pixel.bmp", NormalState::Walk, float4{ 892.0f, 336.0f });
	LevelEnemy.push_back(WaddleDee1);


	// 파워몹 1
	WaddleDoo* WaddleDoo1 = GameEngineLevel::CreateActor<WaddleDoo>(UpdateOrder::Monster);
	if (nullptr == WaddleDoo1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	WaddleDoo1->init("VegetableValley1_1Pixel.bmp", WaddleDooState::Walk, float4{ 1200.0f , 386.0f });
	LevelEnemy.push_back(WaddleDoo1);


	// 공중몹 1-2
	BrontoBurt* BrontoBurt2 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt2)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BrontoBurt2->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1760.0f, 130.0f });
	LevelEnemy.push_back(BrontoBurt2);


	// 공중몹 1-2
	BrontoBurt* BrontoBurt3 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt3)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BrontoBurt3->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1860.0f, 130.0f });
	LevelEnemy.push_back(BrontoBurt3);



	// 공중몹 1-2
	BrontoBurt* BrontoBurt4 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt4)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BrontoBurt4->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1960.0f, 130.0f });
	LevelEnemy.push_back(BrontoBurt4);



	// 파워몹 2
	HotHead* HotHead1 = GameEngineLevel::CreateActor<HotHead>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	HotHead1->init("VegetableValley1_1Pixel.bmp", HotHeadState::Walk, float4{ 2700.0f, 386.0f });
	LevelEnemy.push_back(HotHead1);



	// 파워몹 3
	Sparky* Sparky1 = GameEngineLevel::CreateActor<Sparky>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	Sparky1->init("VegetableValley1_1Pixel.bmp", SparkyState::Idle, float4{ 2000.0f, 386.0f });
	LevelEnemy.push_back(Sparky1);




	// 파워몹 5
	SwordKnight* SwordKnightPtr = GameEngineLevel::CreateActor<SwordKnight>(UpdateOrder::Monster);
	if (nullptr == SwordKnightPtr)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	SwordKnightPtr->init("VegetableValley1_1Pixel.bmp", SwordKnightState::PendulumStride, float4{ 2420.0f, 143.0f });
	LevelEnemy.push_back(SwordKnightPtr);
}