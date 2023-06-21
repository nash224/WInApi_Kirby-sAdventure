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
	VegetableValley_Stage1_PlayDoor->init(OneStageLocation);


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
	if (true == NextLevelTriggerOn && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f )
	{
		if (nullptr == VegetableValley_Stage1_PlayDoor)
		{
			MsgBoxAssert("오브젝트가 Null 입니다.");
			return;
		}

		// 문열고
		VegetableValley_Stage1_PlayDoor->IsDoorOpen = true;


		GameEngineRenderer* DoorRenderer = VegetableValley_Stage1_PlayDoor->MainRenderer;

		if (nullptr == DoorRenderer)
		{
			MsgBoxAssert("오브젝트의 렌더러가 Null 입니다.")
		}

		// 문여는 동작이 끝나면 페이드 아웃
		if (true == DoorRenderer->IsAnimationEnd() && false == IsPlayerEnter)
		{
			GlobalContents::FadeOut(this);

			IsPlayerEnter = true;
		}

		if (true == IsPlayerEnter)
		{
			FadeTime += _Delta;
		}

		// 페이드 아웃이 다 끝나면 다음 레벨로
		if (FadeTime > FADEOUT_ENDTIME)
		{
			VegetableValleyEntertheDoorNumber = 1;
			NextLevelTriggerOn = false;
			IsPlayerEnter = false;
			FadeTime = 0.0f;

			GameEngineCore::ChangeLevel("VegetableValley11");
		}

		return;
	}


	if (true == NextLevelTriggerOn && KirbyPos.X > 695.0f && KirbyPos.X < 750.0f)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValley13");
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
}

void VegetableValleyHub::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture("VegetableValleyPixel.bmp");

	if (1 == VegetableValleyEntertheDoorNumber)
	{
		LevelPlayer->SetPos(OneStageLocation);
	}

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