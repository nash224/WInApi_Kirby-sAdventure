#include "VegetableValley11.h"
#include "VegetableValley12.h"
#include "ContentsEnum.h"


// 11
#include "WaddleDee.h"
#include "BrontoBurt.h"
#include "WaddleDoo.h"
#include "HotHead.h"
#include "Sparky.h"
#include "SwordKnight.h"


// 12
#include "LaserBall.h"
#include "Scarfy.h"
#include "Togezo.h"
#include "BroomHatter.h"
#include "PoppyBrosJr.h"
#include "Kabu.h"




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



void VegetableValley12::EnemySummon()
{

	LevelEnemy.reserve(12);

	// �Ŀ��� 5
	SwordKnight* SwordKnight1 = GameEngineLevel::CreateActor<SwordKnight>(UpdateOrder::Monster);
	if (nullptr == SwordKnight1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	SwordKnight1->init("VegetableValley1_2Pixel.bmp", SwordKnightState::PendulumStride, float4{ 1634.0f, 335.0f });
	LevelEnemy.push_back(SwordKnight1);


	// �� 4-1
	PoppyBrosJr* PoppyBrosJr1 = GameEngineLevel::CreateActor<PoppyBrosJr>(UpdateOrder::Monster);
	if (nullptr == PoppyBrosJr1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	PoppyBrosJr1->init("VegetableValley1_2Pixel.bmp", NormalState::Idle, float4{ 480.0f , 335.0f });
	LevelEnemy.push_back(PoppyBrosJr1);



	// ��2
	BroomHatter* BroomHatter1 = GameEngineLevel::CreateActor<BroomHatter>(UpdateOrder::Monster);
	if (nullptr == BroomHatter1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	BroomHatter1->init("VegetableValley1_2Pixel.bmp", NormalState::Idle, float4{ 1170.0f , 381.0f });
	LevelEnemy.push_back(BroomHatter1);



	// ��3
	Kabu* Kabu1 = GameEngineLevel::CreateActor<Kabu>(UpdateOrder::Monster);
	if (nullptr == Kabu1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	Kabu1->init("VegetableValley1_2Pixel.bmp", NormalState::Idle, float4{ 700.0f , 381.0f });
	LevelEnemy.push_back(Kabu1);



	// ���߸� 1-1
	BrontoBurt* BrontoBurt1 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	BrontoBurt1->init("VegetableValley1_2Pixel.bmp", BrontoState::Idle, float4{ 960.0f , 288.0f });
	LevelEnemy.push_back(BrontoBurt1);



	// ���߸� 2
	Scarfy* Scarfy1 = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	if (nullptr == Scarfy1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	Scarfy1->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2500.0f , 140.0f });
	LevelEnemy.push_back(Scarfy1);


	// ���߸� 2
	Scarfy* Scarfy2Ptr = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	if (nullptr == Scarfy2Ptr)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	Scarfy2Ptr->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2420.0f , 200.0f });
	LevelEnemy.push_back(Scarfy2Ptr);



	// ���߸� 2
	Scarfy* Scarfy3Ptr = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	if (nullptr == Scarfy3Ptr)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	Scarfy3Ptr->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2580.0f , 200.0f });
	LevelEnemy.push_back(Scarfy3Ptr);



	// �Ŀ��� 4
	Togezo* Togezo1 = GameEngineLevel::CreateActor<Togezo>(UpdateOrder::Monster);
	if (nullptr == Togezo1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	Togezo1->init("VegetableValley1_2Pixel.bmp", TogezoState::Walk, float4{ 2260.0f , 286.0f });
	LevelEnemy.push_back(Togezo1);



	// �Ŀ��� 6
	LaserBall* LaserBall1 = GameEngineLevel::CreateActor<LaserBall>(UpdateOrder::Monster);
	if (nullptr == LaserBall1)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	LaserBall1->init("VegetableValley1_2Pixel.bmp", LaserBallState::Fly, float4{ 3100.0f , 200.0f });
	LevelEnemy.push_back(LaserBall1);

	// �Ŀ��� 6
	LaserBall* LaserBall2Ptr = GameEngineLevel::CreateActor<LaserBall>(UpdateOrder::Monster);
	if (nullptr == LaserBall2Ptr)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	LaserBall2Ptr->init("VegetableValley1_2Pixel.bmp", LaserBallState::Fly, float4{ 3200.0f , 200.0f });
	LevelEnemy.push_back(LaserBall2Ptr);






}