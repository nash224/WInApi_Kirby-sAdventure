#include "VegetableValleyHub.h"


#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>


#include "Kirby.h"
#include "DoorObject.h"
#include "BackGround.h"



VegetableValleyHub::VegetableValleyHub()
{
}

VegetableValleyHub::~VegetableValleyHub()
{

}


void VegetableValleyHub::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
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





	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelPlayer->OverOn();




	VegetableValley_Stage1_PlayDoor = GameEngineLevel::CreateActor<DoorObject>();
	if (nullptr == VegetableValley_Stage1_PlayDoor)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}
	VegetableValley_Stage1_PlayDoor->init(OneStageLocation);




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

	if (true == NextLevelTriggerOn && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f )
	{
		if (nullptr == VegetableValley_Stage1_PlayDoor)
		{
			MsgBoxAssert("오브젝트가 Null 입니다.");
			return;
		}

		VegetableValley_Stage1_PlayDoor->IsDoorOpen = true;


		GameEngineRenderer* DoorRenderer = VegetableValley_Stage1_PlayDoor->MainRenderer;

		if (nullptr == DoorRenderer)
		{
			MsgBoxAssert("오브젝트의 렌더러가 Null 입니다.")
		}

		if (true == DoorRenderer->IsAnimationEnd())
		{
			GameEngineCore::ChangeLevel("VegetableValley11");

			VegetableValleyEntertheDoorNumber = 1;
			NextLevelTriggerOn = false;
		}

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
}

void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) { }