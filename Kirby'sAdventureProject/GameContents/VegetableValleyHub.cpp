#include "VegetableValleyHub.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>


#include "Kirby.h"
#include "DoorObject.h"
#include "BillboardsObject.h"
#include "FadeObject.h"
#include "BackGround.h"
#include "HubUI.h"



VegetableValleyHub::VegetableValleyHub()
{
}

VegetableValleyHub::~VegetableValleyHub()
{

}


void VegetableValleyHub::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelBackGround->init("VegetableValley.bmp", "VegetableValleyPixel.bmp", "Resources\\Map");


	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("VegetableValley.bmp");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����µ� �����߽��ϴ�.");
		return;
	}

	float4 BackScale = Texture->GetScale();
	SetLevelBackgroundScale(BackScale);;




	// �÷��̾� ����
	LevelPlayer = GameEngineLevel::CreateActor<Kirby>(UpdateOrder::Player);
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	// ���� Over����
	LevelPlayer->OverOn();



	// HubMap DoorActor
	VegetableValley_Stage1_PlayDoor = GameEngineLevel::CreateActor<DoorObject>(UpdateOrder::BackGroundEffect);
	if (nullptr == VegetableValley_Stage1_PlayDoor)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}
	VegetableValley_Stage1_PlayDoor->init(StageOneLocation);


	// HubMap BillboardActor
	VegetableValley_Billboard = GameEngineLevel::CreateActor<BillboardsObject>(UpdateOrder::BackGroundEffect);
	if (nullptr == VegetableValley_Billboard)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	VegetableValley_Billboard->StageOneBillBoardinit(StageOneBillBoardLocation);
	VegetableValley_Billboard->StageBossBillBoardinit(StageBossBillBoardLocation);




	LevelUIManager = GameEngineLevel::CreateActor<HubUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("������ UI �� Null �Դϴ�.");
		return;
	}





	//GameEngineWindow::MainWindow.CursorOff();
}

void VegetableValleyHub::Update(float _Delta)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("������ �÷��̾ ���������� �ʾҽ��ϴ�.");
		return;
	}

	float4 KirbyPos = LevelPlayer->GetPos();


	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
		return;
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		VegetableValleyEntertheDoorNumber = 1;
		GameEngineCore::ChangeLevel("VegetableValley11");
		return;
	}


	// ù��° ���������� ����
	if (true == IsPlayerEnter && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f )
	{
		if (nullptr == VegetableValley_Stage1_PlayDoor)
		{
			MsgBoxAssert("������Ʈ�� Null �Դϴ�.");
			return;
		}

		// ������
		VegetableValley_Stage1_PlayDoor->IsDoorOpen = true;



		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 1;
			NextLevelTriggerOn = false;
			IsPlayerEnter = false;

			GameEngineCore::ChangeLevel("VegetableValley11");
		}

		return;
	}


	if (true == NextLevelTriggerOn && KirbyPos.X > 695.0f && KirbyPos.X < 750.0f && KirbyPos.Y > 910.0f)
	{
		VegetableValleyEntertheDoorNumber = 2;
		NextLevelTriggerOn = false;
		IsPlayerEnter = false;
		GameEngineCore::ChangeLevel("VegetableValley13");
		return;
	}


	if (true == IsPlayerEnter)
	{
		IsPlayerEnter = false;
	}

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}


	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}
}








void VegetableValleyHub::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI�� �ҷ����� ���߽��ϴ�.");
		return;
	}


	LevelPlayer->SetGroundTexture("VegetableValleyPixel.bmp");


	// ī�޶� ��ġ ����
	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
		return;
	}


	switch (VegetableValleyEntertheDoorNumber)
	{
	case -1:
		LevelPlayer->SetPos(StageOneLocation);
		break;
	case 1:
		LevelPlayer->SetPos(StageOneLocation);
		break;
	case 2:
		LevelPlayer->SetPos(StageTwoLocation);
		break;
	default:
		break;
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 KirbyPos = LevelPlayer->GetPos();
	float4 HUB_UIScale = LevelUIManager->UIScale;

	float4 CameraPos = float4{ KirbyPos.X - WinScale.Half().Half().X , KirbyPos.Y - (WinScale - HUB_UIScale).Y * 0.8f};

	MainCameraPtr->SetPos(CameraPos);



	GlobalContents::FadeIn(this);
}

void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) { }



/*
	��� 4�ܰ�
	fade out & fade in : TotalFrameInter 0.16f, OneFrameInter 0.04f

	�� ����
	1. fade in : TotalFrameInter 0.04f, OneFrameInter 0.04f
	2. Open Door : TotalFrameInter 0.16f, OneFrameInter 0.04f
	3. Hellow NewWorld  0.1f, 0.3f, 0.1f, 0.2f, 0.2f , After WabbleInter 0.04f
	4. CameraMove And Open New Stage
	5. CameraOrigin Positon
	6. Dumbling 15.9 16.1 16.4 16.8 17.07 17.45 17.52 Idle
	7. ChangeForm ClearDoor & BombEffect

*/