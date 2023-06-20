#include "VegetableValleyHub.h"

#include "Kirby.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>



VegetableValleyHub::VegetableValleyHub()
{
}

VegetableValleyHub::~VegetableValleyHub()
{

}


void VegetableValleyHub::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley.bmp", "VegetableValleyPixel.bmp", "Resources\\Map");
	float4 BackScale = ResourcesManager::GetInst().FindTexture("VegetableValley.bmp")->GetScale();
	SetLevelBackgroundScale(BackScale);;

	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	LevelPlayer->OverOn();


	//GameEngineWindow::MainWindow.CursorOff();
}

void VegetableValleyHub::Update(float _Delta)
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비가 Null 입니다.");
		return;
	}

	float4 KirbyPos = KirbyPtr->GetPos();


	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		VegetableValleyEntertheDoorNumber = 1;
		GameEngineCore::ChangeLevel("VegetableValley11");
	}

	if (true == NextLevelTriggerOn && KirbyPos.X > 260.0f && KirbyPos.X < 320.0f )
	{
		NextLevelTriggerOn = false;
		VegetableValleyEntertheDoorNumber = 1;
		GameEngineCore::ChangeLevel("VegetableValley11");
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