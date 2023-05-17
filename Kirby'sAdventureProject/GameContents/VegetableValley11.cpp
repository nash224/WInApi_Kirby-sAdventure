#include "VegetableValley11.h"
#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


VegetableValley11::VegetableValley11() 
{
}

VegetableValley11::~VegetableValley11() 
{

}


void VegetableValley11::Start() 
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1.bmp", "Resources\\KirbyTest\\", float4{ 2 , 2 }, float4{ 1016 , 168 });

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void VegetableValley11::Update(float _Delta)
{
	//if (true == GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D'))
	//{
	//	if (LevelPlayer->GetPos().iX() > GameEngineWindow::MainWindow.GetScale().GetHalf().iX() &&
	//		LevelPlayer->GetPos().iX() <
	//		LevelBackGround->GetScale().iX() - GameEngineWindow::MainWindow.GetScale().GetHalf().iX())
	//	{
	//		GetMainCamera()->AddPos(float4::XValue(LevelPlayer->GetMovePos()));
	//	}
	//}
	//if (true == GameEngineInput::IsPress('W') || GameEngineInput::IsPress('S'))
	//{
	//	if (LevelPlayer->GetPos().iY() > GameEngineWindow::MainWindow.GetScale().GetHalf().iY() &&
	//		LevelPlayer->GetPos().iY() <
	//		LevelBackGround->GetScale().iY() - GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
	//	{
	//		GetMainCamera()->AddPos(float4::YValue(LevelPlayer->GetMovePos()));
	//	}
	//}

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (LevelPlayer->GetPos().iX() >= LevelBackGround->GetScale().iX() - LevelPlayer->GetScale().iX())
	{
		GameEngineCore::ChangeLevel("VegetableValley12");
	}
}

void VegetableValley11::Render() 
{

}

void VegetableValley11::Release() 
{

}

void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.GetHalf());
} 

void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) { }