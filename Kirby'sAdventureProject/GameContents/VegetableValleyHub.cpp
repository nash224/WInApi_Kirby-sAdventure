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

	BitMapFileName = "VegetableValleyPixel.bmp";


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

	// Actor is Level Over When Current Level Change the other Level
	LevelPlayer->OverOn();




	// Stage Position Relation
	Stage1.StageLocation = float4{ 288.0f , 865.0f };
	Stage2.StageLocation = float4{ 720.0f , 961.0f };

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



	VegetableValleyEntertheDoorNumber = -1;




	// Sound Load
	GlobalContents::SoundFileLoad("05_LEVEL1.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("Enemy_DeathSound.wav", "Resources\\SoundResources\\EffectVoice");
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
		}



		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 1;
			IsRequestDoorOpen = false;
			IsPlayerEnter = false;
			NextLevelTriggerOn = false;

			if (true == Stage1.IsStageClear)
			{
				Stage1.DoorPtr->IsDoorClear = true;
			}
			else if (false == Stage1.IsStageClear)
			{
				Stage1.DoorPtr->IsDoorIdle = true;
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
		}



		if (true == NextLevelTriggerOn)
		{
			VegetableValleyEntertheDoorNumber = 2;
			IsRequestDoorOpen = false;
			IsPlayerEnter = false;
			NextLevelTriggerOn = false;

			if (true == Stage2.IsStageClear)
			{
				Stage2.DoorPtr->IsDoorClear = true;
			}
			else if (false == Stage2.IsStageClear)
			{
				Stage2.DoorPtr->IsDoorIdle = true;
			}

			GameEngineCore::ChangeLevel("VegetableValley13");
		}

		return;
	}
}


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
		case 30:
			break;
		case 3:
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
		case 30:
			break;
		case 3:
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

		ObejctDisapearingEffectPtr->init(Stage1.StageLocation + float4{ 0.0f, -StageDoorSize.Half().Y});
	}

}




void VegetableValleyHub::Render(float _Delta)
{
	if (false == Level_DebugRenderIsOn)
	{
		return;
	}


	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return;
	}


	{
		UpdateTime += _Delta;


		std::string Text = "";
		Text += "프레임 : ";
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
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI를 불러오지 못했습니다.");
		return;
	}


	// Kirby Set Bitmap Resource
	LevelPlayer->SetGroundTexture(BitMapFileName);


	// Kirby come out Location
	switch (VegetableValleyEntertheDoorNumber)
	{
	case -1:
		AreYouJustInterSeen = true;
		LevelPlayer->SetPos(Stage1.StageLocation);
		break;
	case 1:
		AreYouJustInterSeen = false;
		LevelPlayer->SetPos(Stage1.StageLocation);
		BGM_Player = GameEngineSound::SoundPlay("05_LEVEL1.mp3", 255);
		IsBGM_On = true;
		break;
	case 2:
		LevelPlayer->SetPos(Stage2.StageLocation);
		break;
	default:
		break;
	}


	// Door State
	switch (VegetableValleyEntertheDoorNumber)
	{
	case 1:
		if (nullptr == Stage1.DoorPtr)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}
		if (false == Stage1.IsStageClear)
		{
			Stage1.DoorPtr->IsDoorIdle;
		}
		else if (true == Stage1.IsStageClear)
		{
			Stage1.DoorPtr->IsDoorClear;
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
			Stage2.DoorPtr->IsDoorIdle;
		}
		else if (true == Stage2.IsStageClear)
		{
			Stage2.DoorPtr->IsDoorClear;
		}
		break;
	case 3:
		break;
	default:
		break;
	}




	// 카메라 위치 지정
	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return;
	}


	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 KirbyPos = LevelPlayer->GetPos();
	float4 HUB_UIScale = LevelUIManager->UIScale;

	float4 CameraPos = float4{ KirbyPos.X - WinScale.Half().Half().X , KirbyPos.Y - (WinScale - HUB_UIScale).Y * 0.8f};

	MainCameraPtr->SetPos(CameraPos);


	// 레벨 이동관련
	IsStageEnd = false;


	if (-1 == VegetableValleyEntertheDoorNumber)
	{
		GlobalContents::WhiteFadeIn(this);
	}
	else if (-1 != VegetableValleyEntertheDoorNumber)
	{
		GlobalContents::FadeIn(this);
	}
}



void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) 
{
	if (true == IsBGM_On && false == AreYouJustInterSeen)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
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