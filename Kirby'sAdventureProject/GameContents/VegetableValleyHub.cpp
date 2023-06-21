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





	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelPlayer->OverOn();




	VegetableValley_Stage1_PlayDoor = GameEngineLevel::CreateActor<DoorObject>();
	if (nullptr == VegetableValley_Stage1_PlayDoor)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}
	VegetableValley_Stage1_PlayDoor->init(OneStageLocation);




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

	if (true == NextLevelTriggerOn && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f )
	{
		if (nullptr == VegetableValley_Stage1_PlayDoor)
		{
			MsgBoxAssert("������Ʈ�� Null �Դϴ�.");
			return;
		}

		VegetableValley_Stage1_PlayDoor->IsDoorOpen = true;


		GameEngineRenderer* DoorRenderer = VegetableValley_Stage1_PlayDoor->MainRenderer;

		if (nullptr == DoorRenderer)
		{
			MsgBoxAssert("������Ʈ�� �������� Null �Դϴ�.")
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
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	LevelPlayer->SetGroundTexture("VegetableValleyPixel.bmp");

	if (1 == VegetableValleyEntertheDoorNumber)
	{
		LevelPlayer->SetPos(OneStageLocation);
	}
}

void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) { }