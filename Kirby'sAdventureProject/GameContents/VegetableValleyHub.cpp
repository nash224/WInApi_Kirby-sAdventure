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
#include "Flag.h"
#include "ObejctDisapearingEffect.h"
#include "BackGround.h"
#include "FadeObject.h"
#include "HubUI.h"



VegetableValleyHub::VegetableValleyHub()
{
}

VegetableValleyHub::~VegetableValleyHub()
{

}


void VegetableValleyHub::Start()
{
	SetName("VegetableValleyHub");

	BitMapFileName = "VegetableValleyPixel.bmp";

	VegetableValleyEntertheDoorNumber = -1;


	ResourecsLoad();
}



// 리소스 로드
void VegetableValleyHub::ResourecsLoad()
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

	BackGroundScale = Texture->GetScale();



	// 플레이어 생성
	LevelPlayer = GameEngineLevel::CreateActor<Kirby>(UpdateOrder::Player);
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	// Actor is Level Over When Current Level Change the other Level
	LevelPlayer->OverOn();




	// Stage Position Relation 
	Stage1.StageLocation = float4{ 288.0f , 865.0f };
	Stage2.StageLocation = float4{ 720.0f , 961.0f };
	Museum.StageLocation = float4{ 720.0f , 528.0f };

	Stage1.BillBoardLocation = float4{ 288.0f , 813.0f };
	Stage2.BillBoardLocation = float4{ 720.0f , 909.0f };


	// HubMap DoorActor
	Stage1.DoorPtr = GameEngineLevel::CreateActor<DoorObject>(UpdateOrder::Other);
	if (nullptr == Stage1.DoorPtr)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}
	Stage1.DoorPtr->init(Stage1.StageLocation);


	Stage2.DoorPtr = GameEngineLevel::CreateActor<DoorObject>(UpdateOrder::Other);
	if (nullptr == Stage2.DoorPtr)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}
	Stage2.DoorPtr->init(Stage2.StageLocation);



	Museum.DoorPtr = GameEngineLevel::CreateActor<DoorObject>(UpdateOrder::Other);
	if (nullptr == Museum.DoorPtr)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}
	Museum.DoorPtr->init(Museum.StageLocation);
	Museum.DoorPtr->IsDoorStar = true;



	// HubMap BillboardActor
	VegetableValley_Billboard = GameEngineLevel::CreateActor<BillboardsObject>(UpdateOrder::BackGroundEffect);
	if (nullptr == VegetableValley_Billboard)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	VegetableValley_Billboard->StageOneBillBoardinit(Stage1.BillBoardLocation);
	VegetableValley_Billboard->StageBossBillBoardinit(Stage2.BillBoardLocation);


	// Create Flag Actor
	Stage1.FlagPtr = GameEngineLevel::CreateActor<Flag>(UpdateOrder::BackGroundEffect);
	if (nullptr == Stage1.FlagPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Stage1.FlagPtr->init(Stage1.StageLocation);


	Stage2.FlagPtr = GameEngineLevel::CreateActor<Flag>(UpdateOrder::BackGroundEffect);
	if (nullptr == Stage2.FlagPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Stage2.FlagPtr->init(Stage2.StageLocation);



	// UI Load
	LevelUIManager = GameEngineLevel::CreateActor<HubUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("생성한 UI 가 Null 입니다.");
		return;
	}



	// Sound Load
	GlobalContents::SoundFileLoad("05_LEVEL1.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("Enemy_DeathSound.wav", "Resources\\SoundResources\\EffectVoice");
}






void VegetableValleyHub::Update(float _Delta)
{
	if (false == FadeObject::IsFadeInDone)
	{
		return;
	}


	Kirby_StageClear();

	VegetableValleyStage_1_Func();
	VegetableValleyStage_2_Func();
	VegetableValleyMuseum_Func();


	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}


	LevelDebugShortcut(_Delta);

	CameraFocus(_Delta);
}


// 비트맵 전환 스위치
void VegetableValleyHub::SwitchRenders()
{
	if (nullptr == VegetableValley_Billboard)
	{
		MsgBoxAssert("빌보드를 불러오지 못했습니다.");
		return;
	}

	VegetableValley_Billboard->SwitchEffect();

	if (nullptr == Stage1.DoorPtr)
	{
		MsgBoxAssert("문 오브젝트를 불러오지 못했습니다.");
		return;
	}

	Stage1.DoorPtr->SwitchEffect();

	if (nullptr == Stage2.DoorPtr)
	{
		MsgBoxAssert("문 오브젝트를 불러오지 못했습니다.");
		return;
	}

	Stage2.DoorPtr->SwitchEffect();

	if (nullptr == Museum.DoorPtr)
	{
		MsgBoxAssert("문 오브젝트를 불러오지 못했습니다.");
		return;
	}

	Museum.DoorPtr->SwitchEffect();


	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	LevelBackGround->SwitchRender();
}



// 스테이지 클리어 로직
void VegetableValleyHub::Kirby_StageClear()
{
	if (nullptr == Stage1.DoorPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	if (nullptr == Stage2.DoorPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}



	// When Kirby Enter StageDoor, Kirby Open the Door
	if (true == Kirby::IsKirbyOpenDoorToLevel)
	{
		Kirby::IsKirbyOpenDoorToLevel = false;

		switch (VegetableValleyEntertheDoorNumber)
		{
		case 1:
			Stage1.DoorPtr->IsDoorOpen = true;
			break;
		case 2:
			Stage2.DoorPtr->IsDoorOpen = true;
			break;
		case 3:
			break;
		case 30:
			break;
		default:
			break;
		}
	}


	// When Kirby comes out StageDoor and Stage finished, Kirby close the Door
	if (true == Kirby::IsKirbyCloseDoorToLevel)
	{
		Kirby::IsKirbyCloseDoorToLevel = false;

		switch (VegetableValleyEntertheDoorNumber)
		{
		case 1:
			Stage1.DoorPtr->IsDoorClose = true;
			break;
		case 2:
			Stage2.DoorPtr->IsDoorClose = true;
			break;
		case 3:
			break;
		case 30:
			break;
		default:
			break;
		}
	}


	// If Kirby finished, Stage's Door Change ClearDoor
	if (true == ChangeClearDoor)
	{
		ChangeClearDoor = false;

		switch (VegetableValleyEntertheDoorNumber)
		{
		case 1:
			if (nullptr == Stage1.DoorPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}
			if (nullptr == Stage1.FlagPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			Stage1.DoorPtr->IsDoorClear = true;
			Stage1.IsStageClear = true;
			Stage1.FlagPtr->On();
			break;
		case 2:
			if (nullptr == Stage2.DoorPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}
			if (nullptr == Stage2.FlagPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			Stage2.DoorPtr->IsDoorClear = true;
			Stage2.IsStageClear = true;
			Stage2.FlagPtr->On();
			break;
		default:
			break;
		}


		ObejctDisapearingEffect* ObejctDisapearingEffectPtr = CreateActor<ObejctDisapearingEffect>(UpdateOrder::UI);
		if (nullptr == ObejctDisapearingEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		ObejctDisapearingEffectPtr->init(Stage1.StageLocation + float4{ 0.0f, -StageDoorSize.Half().Y });
	}

}


// 스테이지 1-1 레벨 Change
void VegetableValleyHub::VegetableValleyStage_1_Func()
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("레벨에 플레이어를 지정해주지 않았습니다.");
		return;
	}

	float4 KirbyPos = LevelPlayer->GetPos();



	// 첫번째 스테이지에 들어가면
	if (true == IsPlayerEnter && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f)
	{
		if (nullptr == Stage1.DoorPtr)
		{
			MsgBoxAssert("오브젝트가 Null 입니다.");
			return;
		}

		// 문열고
		if (false == IsRequestDoorOpen)
		{
			Stage1.DoorPtr->IsDoorOpen = true;
			IsRequestDoorOpen = true;

			GlobalContents::FadeOut(this);
		}

		if (true == IsFadeDone)
		{
			IsFadeDone = false;

			NextLevelTriggerOn = true;
		}



		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 1;
			IsRequestDoorOpen = false;
			IsPlayerEnter = false; 
			NextLevelTriggerOn = false;
			IsChangeLevel = true;

			GameEngineCore::ChangeLevel("VegetableValley11");
		}

		return;
	}

}



// 보스 스테이지 레벨 Change
void VegetableValleyHub::VegetableValleyStage_2_Func()
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("레벨에 플레이어를 지정해주지 않았습니다.");
		return;
	}

	float4 KirbyPos = LevelPlayer->GetPos();



	// WhispyWood 보스 스테이지
	if (true == IsPlayerEnter && KirbyPos.X > 650.0f && KirbyPos.X < 790.0f && KirbyPos.Y > 910.0f)
	{
		if (nullptr == Stage2.DoorPtr)
		{
			MsgBoxAssert("오브젝트가 Null 입니다.");
			return;
		}

		// 문열고
		if (false == IsRequestDoorOpen)
		{
			Stage2.DoorPtr->IsDoorOpen = true;
			IsRequestDoorOpen = true;

			GlobalContents::FadeOut(this);
		}

		if (true == IsFadeDone)
		{
			IsFadeDone = false;

			NextLevelTriggerOn = true;
		}



		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 2;
			AreYouJustEnterScene = false;
			IsRequestDoorOpen = false;
			NextLevelTriggerOn = false;
			IsPlayerEnter = false;
			IsChangeLevel = true;

			GameEngineCore::ChangeLevel("VegetableValley13");
		}

		return;
	}
}


// Museum Level Change
void VegetableValleyHub::VegetableValleyMuseum_Func()
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("레벨에 플레이어를 지정해주지 않았습니다.");
		return;
	}

	float4 KirbyPos = LevelPlayer->GetPos();



	// 박물관
	if (true == IsPlayerEnter && KirbyPos.X > 650.0f && KirbyPos.X < 790.0f && KirbyPos.Y < 585.0f)
	{
		if (nullptr == Museum.DoorPtr)
		{
			MsgBoxAssert("오브젝트가 Null 입니다.");
			return;
		}

		// 문열고
		if (false == IsRequestDoorOpen)
		{
			Museum.DoorPtr->IsDoorOpen = true;
			IsRequestDoorOpen = true;

			GlobalContents::FadeOut(this);
		}

		if (true == IsFadeDone)
		{
			IsFadeDone = false;

			NextLevelTriggerOn = true;
		}


		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 30;
			IsRequestDoorOpen = false;
			NextLevelTriggerOn = false;
			IsPlayerEnter = false;
			IsChangeLevel = true;

			GameEngineCore::ChangeLevel("SubScreens");
		}

		return;
	}
}




void VegetableValleyHub::Render(float _Delta)
{
	DebugRender(_Delta);
}







void VegetableValleyHub::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	// Kirby Set Bitmap Resource
	LevelPlayer->SetGroundTexture(BitMapFileName);


	LevelStartCameraPos();

	LevelStartDoorLogic();


	if (-1 == VegetableValleyEntertheDoorNumber)
	{
		GlobalContents::WhiteFadeIn(this);
	}
	else if (-1 != VegetableValleyEntertheDoorNumber)
	{
		GlobalContents::FadeIn(this);
	}
}



// 처음 카메라 위치
void VegetableValleyHub::LevelStartCameraPos()
{
	// 초기 카메라 위치 지정
	if (-1 == VegetableValleyEntertheDoorNumber)
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


		GameEngineCamera* MainCameraPtr = GetMainCamera();
		if (nullptr == MainCameraPtr)
		{
			MsgBoxAssert("카메라를 불러오지 못했습니다.");
			return;
		}

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		float4 KirbyPos = Stage1.StageLocation;
		float4 HUB_UIScale = LevelUIManager->UIScale;

		float4 CameraPos = float4{ KirbyPos.X - WinScale.Half().Half().X , KirbyPos.Y - (WinScale - HUB_UIScale).Y * 0.8f };

		MainCameraPtr->SetPos(CameraPos);
	}
}



// 레벨 입장 시 문 상태 
void VegetableValleyHub::LevelStartDoorLogic()
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	// Kirby come out last Stage
	switch (VegetableValleyEntertheDoorNumber)
	{
	case -1:
		LevelPlayer->SetPos(Stage1.StageLocation);
		break;
	case 1:
		LevelPlayer->SetPos(Stage1.StageLocation);

		BGM_Player = GameEngineSound::SoundPlay("05_LEVEL1.mp3", 255);
		BGMFileName = "05_LEVEL1.mp3";
		IsBGM_On = true;
		break;
	case 2:
		LevelPlayer->SetPos(Stage2.StageLocation);
		break;
	case 30:
		LevelPlayer->SetPos(Museum.StageLocation);

		if (false == IsBGM_On)
		{
			BGM_Player = GameEngineSound::SoundPlay("05_LEVEL1.mp3", 255);
			BGMFileName = "05_LEVEL1.mp3";
			IsBGM_On = true;
		}
		break;
	default:
		break;
	}


	// Door State
	switch (VegetableValleyEntertheDoorNumber)
	{
	case 1:
		if (false == Stage1.IsStageClear)
		{
			if (nullptr == Stage1.DoorPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			Stage1.DoorPtr->IsDoorIdle = true;
		}
		else if (true == Stage1.IsStageClear)
		{
			if (nullptr == Stage1.DoorPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			Stage1.DoorPtr->IsDoorClear = true;
		}
		break;
	case 2:
		if (nullptr == Stage2.DoorPtr)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}
		if (false == Stage2.IsStageClear)
		{
			Stage2.DoorPtr->IsDoorIdle = true;
		}
		else if (true == Stage2.IsStageClear)
		{
			Stage2.DoorPtr->IsDoorClear = true;
		}
		break;
	case 30:
		if (nullptr == Museum.DoorPtr)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		Museum.DoorPtr->IsDoorStar = true;
		break;
	default:
		break;
	}
}






void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) 
{
	IsRequestDoorOpen = false;
	IsPlayerEnter = false;
	NextLevelTriggerOn = false;
	IsFadeDone = false;


	if (true == IsBGM_On && false == AreYouJustEnterScene && 30 != VegetableValleyEntertheDoorNumber)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}

	if (true == AreYouJustEnterScene)
	{
		AreYouJustEnterScene = false;
	}
}



/*

	슈도코드

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