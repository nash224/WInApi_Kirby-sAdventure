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

	// ��1
	WaddleDee* WaddleDee1 = GameEngineLevel::CreateActor<WaddleDee>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	WaddleDee1->init("VegetableValley1_1Pixel.bmp", NormalState::Walk, float4{ 892.0f, 336.0f });
	LevelEnemy.push_back(WaddleDee1);


	// �Ŀ��� 1
	WaddleDoo* WaddleDoo1 = GameEngineLevel::CreateActor<WaddleDoo>(UpdateOrder::Monster);
	if (nullptr == WaddleDoo1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	WaddleDoo1->init("VegetableValley1_1Pixel.bmp", WaddleDooState::Walk, float4{ 1200.0f , 386.0f });
	LevelEnemy.push_back(WaddleDoo1);


	// ���߸� 1-2
	BrontoBurt* BrontoBurt2 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt2)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	BrontoBurt2->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1760.0f, 130.0f });
	LevelEnemy.push_back(BrontoBurt2);


	// ���߸� 1-2
	BrontoBurt* BrontoBurt3 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt3)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	BrontoBurt3->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1860.0f, 130.0f });
	LevelEnemy.push_back(BrontoBurt3);



	// ���߸� 1-2
	BrontoBurt* BrontoBurt4 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt4)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	BrontoBurt4->init("VegetableValley1_1Pixel.bmp", BrontoState::WaveFlightFall, float4{ 1960.0f, 130.0f });
	LevelEnemy.push_back(BrontoBurt4);



	// �Ŀ��� 2
	HotHead* HotHead1 = GameEngineLevel::CreateActor<HotHead>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	HotHead1->init("VegetableValley1_1Pixel.bmp", HotHeadState::Walk, float4{ 2700.0f, 386.0f });
	LevelEnemy.push_back(HotHead1);



	// �Ŀ��� 3
	Sparky* Sparky1 = GameEngineLevel::CreateActor<Sparky>(UpdateOrder::Monster);
	if (nullptr == WaddleDee1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	Sparky1->init("VegetableValley1_1Pixel.bmp", SparkyState::Idle, float4{ 2000.0f, 386.0f });
	LevelEnemy.push_back(Sparky1);




	// �Ŀ��� 5
	SwordKnight* SwordKnightPtr = GameEngineLevel::CreateActor<SwordKnight>(UpdateOrder::Monster);
	if (nullptr == SwordKnightPtr)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	SwordKnightPtr->init("VegetableValley1_1Pixel.bmp", SwordKnightState::PendulumStride, float4{ 2420.0f, 143.0f });
	LevelEnemy.push_back(SwordKnightPtr);
}