#include "VegetableValley12.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


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
#include "FadeObject.h"
#include <vector>


VegetableValley12::VegetableValley12() 
{
}

VegetableValley12::~VegetableValley12() 
{
}

void VegetableValley12::Start()
{
	// ��� ����
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("���� ���ȭ�� ������ �����߽��ϴ�.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValley1_2.bmp", "VegetableValley1_2Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("��Ʈ�� ������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	BackGroundScale = Texture->GetScale();

	BitMapFileName = "VegetableValley1_2Pixel.bmp";




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

	Scarfy2Ptr->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2400.0f , 200.0f });
	LevelEnemy.push_back(Scarfy2Ptr);



	// ���߸� 2
	Scarfy* Scarfy3Ptr = GameEngineLevel::CreateActor<Scarfy>(UpdateOrder::Monster);
	if (nullptr == Scarfy3Ptr)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	Scarfy3Ptr->init("VegetableValley1_2Pixel.bmp", ScarfyState::Idle, float4{ 2600.0f , 200.0f });
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





	// UI����
	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI ������ �����߽��ϴ�.");
		return;
	}


	// ���� �ε�
	GlobalContents::SoundFileLoad("06_Underground_Level.mp3", "Resources\\SoundResources\\SoundTrack");
}




void VegetableValley12::Update(float _Delta)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ �ҷ����� ���߽��ϴ�.");
		return;
	}


	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValleyHub");
	}

	if (true == GameEngineInput::IsDown('6'))
	{
		GameEngineCamera* MainCameraPtr = GetMainCamera();
		if (nullptr == MainCameraPtr)
		{
			MsgBoxAssert("ī�޶� NUll �Դϴ�.");
			return;
		}

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();

		LevelPlayer->SetPos(float4{ 3457.0f , 383.0f });
		MainCameraPtr->SetPos(float4{ BackGroundScale.X - WinScale.X , 0.0f });
	}



	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValleyHub");

		return;
	}


	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
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
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	SetPlayerPosAndCameraPos(float4{ 83.0f, 384.0f }, float4::ZERO);



	// ���� ���
	GameEngineSound::SoundPlay("06_Underground_Level.mp3");



	// �������� ����
	IsStageEnd = true;

	GlobalContents::FadeIn(this);
}

void VegetableValley12::LevelEnd(GameEngineLevel* _NextLevel) 
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}
