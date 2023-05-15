#include "VegetableValleyHub.h"

#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


VegetableValleyHub::VegetableValleyHub()
{
}

VegetableValleyHub::~VegetableValleyHub()
{

}


void VegetableValleyHub::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley.bmp", float4{ 0 , 0 }, float4{ 470 , 360 });

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void VegetableValleyHub::Update(float _Delta)
{

	if (true == GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D'))
	{
		if (LevelPlayer->GetPos().iX() > GameEngineWindow::MainWindow.GetScale().GetHalf().iX() &&
			LevelPlayer->GetPos().iX() <
			LevelBackGround->GetScale().iX() - GameEngineWindow::MainWindow.GetScale().GetHalf().iX())
		{
			GetMainCamera()->AddPos(float4::XValue(LevelPlayer->GetMovePos()));
		}
	}
	if (true == GameEngineInput::IsPress('W') || GameEngineInput::IsPress('S'))
	{
		if (LevelPlayer->GetPos().iY() > GameEngineWindow::MainWindow.GetScale().GetHalf().iY() &&
			LevelPlayer->GetPos().iY() <
			LevelBackGround->GetScale().iY() - GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
		{
			GetMainCamera()->AddPos(float4::YValue(LevelPlayer->GetMovePos()));
		}
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (LevelPlayer->GetPos().iX() >= LevelBackGround->GetScale().iX() - LevelPlayer->GetScale().iX())
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
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.GetHalf());
}

void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) { }