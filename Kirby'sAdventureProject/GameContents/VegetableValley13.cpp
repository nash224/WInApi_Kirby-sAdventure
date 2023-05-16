#include "VegetableValley13.h"
#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


VegetableValley13::VegetableValley13()
{
}

VegetableValley13::~VegetableValley13()
{
}

void VegetableValley13::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1.bmp", "Resources\\KirbyTest\\", float4{ 2 , 342 }, float4{ 1016 , 168 });

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void VegetableValley13::Update(float _Delta)
{
	float4 CameraHalfSize = GameEngineWindow::MainWindow.GetScale().GetHalf();

	if (true == GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D'))
	{
		if (LevelPlayer->GetPos().iX() > CameraHalfSize.iX() &&
			LevelPlayer->GetPos().iX() <
			LevelBackGround->GetScale().iX() - CameraHalfSize.iX())
		{
			GetMainCamera()->AddPos(float4::XValue(LevelPlayer->GetMovePos()));
		}
	}
	if (true == GameEngineInput::IsPress('W') || GameEngineInput::IsPress('S'))
	{
		if (LevelPlayer->GetPos().iY() > CameraHalfSize.iY() &&
			LevelPlayer->GetPos().iY() <
			LevelBackGround->GetScale().iY() - CameraHalfSize.iY())
		{
			GetMainCamera()->AddPos(float4::YValue(LevelPlayer->GetMovePos()));
		}
	}



	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (LevelPlayer->GetPos().iX() >= LevelBackGround->GetScale().iX())
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

void VegetableValley13::LevelStart(GameEngineLevel* _PrevLevel) { }

void VegetableValley13::LevelEnd(GameEngineLevel* _NextLevel) { }
