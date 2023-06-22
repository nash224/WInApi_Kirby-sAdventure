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
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelBackGround->init("VegetableValley.bmp", "VegetableValleyPixel.bmp", "Resources\\Map");


	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("VegetableValley.bmp");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오는데 실패했습니다.");
		return;
	}

	float4 BackScale = Texture->GetScale();
	SetLevelBackgroundScale(BackScale);;




	// 플레이어 생성
	LevelPlayer = GameEngineLevel::CreateActor<Kirby>(UpdateOrder::Player);
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	// 레벨 Over가능
	LevelPlayer->OverOn();



	// HubMap DoorActor
	VegetableValley_Stage1_PlayDoor = GameEngineLevel::CreateActor<DoorObject>(UpdateOrder::BackGroundEffect);
	if (nullptr == VegetableValley_Stage1_PlayDoor)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}
	VegetableValley_Stage1_PlayDoor->init(StageOneLocation);


	// HubMap BillboardActor
	VegetableValley_Billboard = GameEngineLevel::CreateActor<BillboardsObject>(UpdateOrder::BackGroundEffect);
	if (nullptr == VegetableValley_Billboard)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	VegetableValley_Billboard->StageOneBillBoardinit(StageOneBillBoardLocation);
	VegetableValley_Billboard->StageBossBillBoardinit(StageBossBillBoardLocation);




	LevelUIManager = GameEngineLevel::CreateActor<HubUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("생성한 UI 가 Null 입니다.");
		return;
	}





	//GameEngineWindow::MainWindow.CursorOff();
}

void VegetableValleyHub::Update(float _Delta)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("레벨에 플레이어를 지정해주지 않았습니다.");
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


	// 첫번째 스테이지에 들어가면
	if (true == IsPlayerEnter && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f )
	{
		if (nullptr == VegetableValley_Stage1_PlayDoor)
		{
			MsgBoxAssert("오브젝트가 Null 입니다.");
			return;
		}

		// 문열고
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
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI를 불러오지 못했습니다.");
		return;
	}


	LevelPlayer->SetGroundTexture("VegetableValleyPixel.bmp");


	// 카메라 위치 지정
	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
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
	밝기 4단계
	fade out & fade in : TotalFrameInter 0.16f, OneFrameInter 0.04f

	맵 오픈
	1. fade in : TotalFrameInter 0.04f, OneFrameInter 0.04f
	2. Open Door : TotalFrameInter 0.16f, OneFrameInter 0.04f
	3. Hellow NewWorld  0.1f, 0.3f, 0.1f, 0.2f, 0.2f , After WabbleInter 0.04f
	4. CameraMove And Open New Stage
	5. CameraOrigin Positon
	6. Dumbling 15.9 16.1 16.4 16.8 17.07 17.45 17.52 Idle
	7. ChangeForm ClearDoor & BombEffect

*/