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
/// <summary>
/// /
/// </summary>
/// ////

void VegetableValleyHub::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley.bmp", "VegetableValleyPixel.bmp", "Resources\\Map");

	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	LevelPlayer->SetGroundTexture("VegetableValleyPixel.bmp");
}

void VegetableValleyHub::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValley11");
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}

	if (LevelPlayer->GetPos().iX() >= 1440)
	{
		GameEngineCore::ChangeLevel("VegetableValley11");
	}
}

void VegetableValleyHub::Render()
{

}

void VegetableValleyHub::Release()
{

}

void VegetableValleyHub::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}

void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) { }