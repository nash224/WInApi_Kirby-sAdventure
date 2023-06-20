#include "VegetableValley12.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Kirby.h"
#include "PlayUI.h"
#include "SwordKnight.h"
#include "BrontoBurt.h"
#include "LaserBall.h"
#include "Scarfy.h"
#include "Togezo.h"
#include "BroomHatter.h"
#include "PoppyBrosJr.h"
#include "Kabu.h"
#include "BackGround.h"


VegetableValley12::VegetableValley12() 
{
}

VegetableValley12::~VegetableValley12() 
{
}

void VegetableValley12::Start()
{
	// 배경 생성
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("레벨 배경화면 생성에 실패했습니다.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValley1_2.bmp", "VegetableValley1_2Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("비트맵 파일을 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();

	BitMapFileName = "VegetableValley1_2Pixel.bmp";




	// 파워몹 5
	SwordKnight* SwordKnight1 = GameEngineLevel::CreateActor<SwordKnight>(UpdateOrder::Monster);
	if (nullptr == SwordKnight1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	SwordKnight1->init("VegetableValley1_2Pixel.bmp", SwordKnightState::PendulumStride, float4{ 1634.0f, 335.0f });
	LevelEnemy.insert(std::make_pair("SwordKnight1", SwordKnight1));


	// 몹 4-1
	PoppyBrosJr* PoppyBrosJr1 = GameEngineLevel::CreateActor<PoppyBrosJr>(UpdateOrder::Monster);
	if (nullptr == PoppyBrosJr1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	PoppyBrosJr1->init("VegetableValley1_2Pixel.bmp", NormalState::Idle, float4{ 480.0f , 335.0f });
	LevelEnemy.insert(std::make_pair("PoppyBrosJr1", PoppyBrosJr1));



	// 몹2
	BroomHatter* BroomHatter1 = GameEngineLevel::CreateActor<BroomHatter>(UpdateOrder::Monster);
	if (nullptr == BroomHatter1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BroomHatter1->init("VegetableValley1_2Pixel.bmp", NormalState::Idle, float4{ 1170.0f , 381.0f });
	LevelEnemy.insert(std::make_pair("BroomHatter1", BroomHatter1));



	// 몹3
	Kabu* Kabu1 = GameEngineLevel::CreateActor<Kabu>(UpdateOrder::Monster);
	if (nullptr == Kabu1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	Kabu1->init("VegetableValley1_2Pixel.bmp", NormalState::Idle, float4{ 700.0f , 381.0f });
	LevelEnemy.insert(std::make_pair("Kabu1", Kabu1));



	// 공중몹 1-1
	BrontoBurt* BrontoBurt1 = GameEngineLevel::CreateActor<BrontoBurt>(UpdateOrder::Monster);
	if (nullptr == BrontoBurt1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	BrontoBurt1->init("VegetableValley1_2Pixel.bmp", BrontoState::Idle, float4{ 960.0f , 288.0f });
	LevelEnemy.insert(std::make_pair("BrontoBurt1", BrontoBurt1));



	// 공중몹 2
	Scarfy* Scarfy1 = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	if (nullptr == Scarfy1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	Scarfy1->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2500.0f , 140.0f });
	LevelEnemy.insert(std::make_pair("Scarfy1", Scarfy1));


	// 공중몹 2
	Scarfy* Scarfy2Ptr = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	if (nullptr == Scarfy2Ptr)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	Scarfy2Ptr->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2400.0f , 200.0f });
	LevelEnemy.insert(std::make_pair("Scarfy2Ptr", Scarfy2Ptr));



	// 공중몹 2
	Scarfy* Scarfy3Ptr = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	if (nullptr == Scarfy3Ptr)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	Scarfy3Ptr->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2600.0f , 200.0f });
	LevelEnemy.insert(std::make_pair("Scarfy3Ptr", Scarfy3Ptr));



	// 파워몹 4
	Togezo* Togezo1 = GameEngineLevel::CreateActor<Togezo>(UpdateOrder::Monster);
	if (nullptr == Togezo1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	Togezo1->init("VegetableValley1_2Pixel.bmp", TogezoState::Walk, float4{ 2260.0f , 286.0f });
	LevelEnemy.insert(std::make_pair("Togezo1", Togezo1));



	// 파워몹 6
	LaserBall* LaserBall1 = GameEngineLevel::CreateActor<LaserBall>(UpdateOrder::Monster);
	if (nullptr == LaserBall1)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	LaserBall1->init("VegetableValley1_2Pixel.bmp", LaserBallState::Fly, float4{ 3100.0f , 200.0f });
	LevelEnemy.insert(std::make_pair("LaserBall1", LaserBall1));

	// 파워몹 6
	LaserBall* LaserBall2Ptr = GameEngineLevel::CreateActor<LaserBall>(UpdateOrder::Monster);
	if (nullptr == LaserBall2Ptr)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	LaserBall2Ptr->init("VegetableValley1_2Pixel.bmp", LaserBallState::Fly, float4{ 3200.0f , 200.0f });
	LevelEnemy.insert(std::make_pair("LaserBall2Ptr", LaserBall2Ptr));





	// UI생성
	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}
}




void VegetableValley12::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		IsStageEnd = true;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
	}

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		IsStageEnd = true;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
	}


	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}


	CheckRespawnEnemy();
}


void VegetableValley12::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(float4{ 200.0f, 200.0f });
}

void VegetableValley12::LevelEnd(GameEngineLevel* _NextLevel) { }
