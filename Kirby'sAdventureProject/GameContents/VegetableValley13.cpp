#include "VegetableValley13.h"
#include "Kirby.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourceManager.h>


VegetableValley13::VegetableValley13()
{
}

VegetableValley13::~VegetableValley13()
{
}

void VegetableValley13::Start()
{
	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1_3.bmp", "Resources\\Map");

}

void VegetableValley13::Update(float _Delta)
{
	float4 CameraHalfSize = GameEngineWindow::MainWindow.GetScale().GetHalf();

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}

	//GameEngineWindowTexture* Texture = ResourceManager::GetInst().FindTexture("VegetableValley1");
	//float4 Scale = Texture->GetScale();
	if (LevelPlayer->GetPos().iX() >= 3048.0f - LevelPlayer->GetScale().iX())
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}
}

void VegetableValley13::Render()
{

}

void VegetableValley13::Release()
{

}

void VegetableValley13::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}


void VegetableValley13::LevelEnd(GameEngineLevel* _NextLevel) { }
