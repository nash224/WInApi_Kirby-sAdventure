#include "VegetableValleyHub.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>


#include "Kirby.h"
#include "DoorObject.h"
#include "BillboardsObject.h"
#include "ObejctDisapearingEffect.h"
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
	VegetableValley_Stage1_PlayDoor = GameEngineLevel::CreateActor<DoorObject>(UpdateOrder::Other);
	if (nullptr == VegetableValley_Stage1_PlayDoor)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}
	VegetableValley_Stage1_PlayDoor->init(StageOneLocation);


	VegetableValley_Stage2_BossDoor = GameEngineLevel::CreateActor<DoorObject>(UpdateOrder::Other);
	if (nullptr == VegetableValley_Stage2_BossDoor)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}
	VegetableValley_Stage2_BossDoor->init(StageTwoLocation);



	// HubMap BillboardActor
	VegetableValley_Billboard = GameEngineLevel::CreateActor<BillboardsObject>(UpdateOrder::BackGroundEffect);
	if (nullptr == VegetableValley_Billboard)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	VegetableValley_Billboard->StageOneBillBoardinit(StageOneBillBoardLocation);
	VegetableValley_Billboard->StageBossBillBoardinit(StageBossBillBoardLocation);



	// UI Load
	LevelUIManager = GameEngineLevel::CreateActor<HubUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("������ UI �� Null �Դϴ�.");
		return;
	}



	VegetableValleyEntertheDoorNumber = -1;


	// Sound Load
	GlobalContents::SoundFileLoad("05_LEVEL1.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("Enemy_DeathSound.wav", "Resources\\SoundResources\\EffectVoice");


	//GameEngineWindow::MainWindow.CursorOff();
}

void VegetableValleyHub::Update(float _Delta)
{


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


	Kirby_StageClear();

	VegetableValleyStage_1_Func();
	VegetableValleyStage_2_Func();




	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}


	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}
}




void VegetableValleyHub::VegetableValleyStage_1_Func()
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("������ �÷��̾ ���������� �ʾҽ��ϴ�.");
		return;
	}

	float4 KirbyPos = LevelPlayer->GetPos();



	// ù��° ���������� ����
	if (true == IsPlayerEnter && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f)
	{
		if (nullptr == VegetableValley_Stage1_PlayDoor)
		{
			MsgBoxAssert("������Ʈ�� Null �Դϴ�.");
			return;
		}

		// ������
		if (false == IsRequestDoorOpen)
		{
			VegetableValley_Stage1_PlayDoor->IsDoorOpen = true;
			IsRequestDoorOpen = true;
		}



		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 1;
			IsRequestDoorOpen = false;
			IsPlayerEnter = false;
			NextLevelTriggerOn = false;

			if (true == IsStage1Clear)
			{
				VegetableValley_Stage1_PlayDoor->IsDoorClear = true;
			}
			else if (false == IsStage1Clear)
			{
				VegetableValley_Stage1_PlayDoor->IsDoorIdle = true;
			}

			GameEngineCore::ChangeLevel("VegetableValley11");
		}

		return;
	}



}


void VegetableValleyHub::VegetableValleyStage_2_Func()
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("������ �÷��̾ ���������� �ʾҽ��ϴ�.");
		return;
	}

	float4 KirbyPos = LevelPlayer->GetPos();



	// WhispyWood ���� ��������
	if (true == IsPlayerEnter && KirbyPos.X > 650.0f && KirbyPos.X < 790.0f && KirbyPos.Y > 910.0f)
	{
		if (nullptr == VegetableValley_Stage1_PlayDoor)
		{
			MsgBoxAssert("������Ʈ�� Null �Դϴ�.");
			return;
		}

		// ������
		if (false == IsRequestDoorOpen)
		{
			VegetableValley_Stage2_BossDoor->IsDoorOpen = true;
			IsRequestDoorOpen = true;
		}



		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 2;
			IsRequestDoorOpen = false;
			IsPlayerEnter = false;
			NextLevelTriggerOn = false;

			if (true == IsStage1Clear)
			{
				VegetableValley_Stage2_BossDoor->IsDoorClear = true;
			}
			else if (false == IsStage1Clear)
			{
				VegetableValley_Stage2_BossDoor->IsDoorIdle = true;
			}

			GameEngineCore::ChangeLevel("VegetableValley13");
		}

		return;
	}


	//if (true == NextLevelTriggerOn && KirbyPos.X > 650.0f && KirbyPos.X < 790.0f && KirbyPos.Y > 910.0f)
	//{
	//	VegetableValleyEntertheDoorNumber = 2;
	//	NextLevelTriggerOn = false;
	//	IsPlayerEnter = false;
	//	GameEngineCore::ChangeLevel("VegetableValley13");
	//	return;
	//}
}


void VegetableValleyHub::Kirby_StageClear()
{
	if (nullptr == VegetableValley_Stage1_PlayDoor)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	if (nullptr == VegetableValley_Stage2_BossDoor)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}



	if (true == Kirby::IsKirbyOpenDoorToLevel)
	{
		Kirby::IsKirbyOpenDoorToLevel = false;

		switch (VegetableValleyEntertheDoorNumber)
		{
		case 1:
			VegetableValley_Stage1_PlayDoor->IsDoorOpen = true;
			break;
		case 2:
			VegetableValley_Stage2_BossDoor->IsDoorOpen = true;
			break;
		case 30:
			break;
		case 3:
			break;
		default:
			break;
		}
	}


	if (true == Kirby::IsKirbyCloseDoorToLevel)
	{
		Kirby::IsKirbyCloseDoorToLevel = false;

		switch (VegetableValleyEntertheDoorNumber)
		{
		case 1:
			VegetableValley_Stage1_PlayDoor->IsDoorClose = true;
			break;
		case 2:
			VegetableValley_Stage2_BossDoor->IsDoorClose = true;
			break;
		case 30:
			break;
		case 3:
			break;
		default:
			break;
		}
	}

	if (true == ChangeClearDoor)
	{
		ChangeClearDoor = false;

		switch (VegetableValleyEntertheDoorNumber)
		{
		case 1:
			VegetableValley_Stage1_PlayDoor->IsDoorClear = true;
			IsStage1Clear = true;
			break;
		case 2:
			VegetableValley_Stage2_BossDoor->IsDoorClear = true;
			IsStage2Clear = true;
			break;
		default:
			break;
		}

		ObejctDisapearingEffect* ObejctDisapearingEffectPtr = CreateActor<ObejctDisapearingEffect>(UpdateOrder::UI);
		if (nullptr == ObejctDisapearingEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		ObejctDisapearingEffectPtr->init(StageOneLocation + float4{ 0.0f, -StageDoorSize.Half().Y});
	}

}




void VegetableValleyHub::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
		return;
	}


	{
		UpdateTime += _Delta;


		std::string Text = "";
		Text += "������ : ";
		if (UpdateTime >= 1.0f)
		{
			UpdateTime = 0.0f;

			FPSText = 1.0f / _Delta;
		}
		Text += std::to_string(FPSText);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
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
		BGM_Player = GameEngineSound::SoundPlay("05_LEVEL1.mp3", 255);
		IsBGM_On = true;
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


	// ���� �̵�����
	IsStageEnd = false;

	GlobalContents::FadeIn(this);
}

void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) 
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}



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