#include "VegetableValleyIntro.h"

#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


VegetableValleyIntro::VegetableValleyIntro()
{
}

VegetableValleyIntro::~VegetableValleyIntro()
{

}


void VegetableValleyIntro::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("CutsceneBackgrounds.bmp", float4{ 4 , 21 }, float4{ 256 , 240 });

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void VegetableValleyIntro::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	float4 MovePos = float4::ZERO;
	MovePos = LevelPlayer->GetDir() * LevelPlayer->GetSpeed() * _Delta;

	if (LevelPlayer->GetPos().iX() > GameEngineWindow::MainWindow.GetScale().GetHalf().iX() &&
		LevelPlayer->GetPos().iX() <
		LevelBackGround->GetScale().iX() - GameEngineWindow::MainWindow.GetScale().GetHalf().iX())
	{
		GetMainCamera()->AddPos(float4::XValue(MovePos));
	}

	if (LevelPlayer->GetPos().iY() > GameEngineWindow::MainWindow.GetScale().GetHalf().iY() &&
		LevelPlayer->GetPos().iY() <
		LevelBackGround->GetScale().iY() - GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
	{
		GetMainCamera()->AddPos(float4::YValue(MovePos));
	}

	//if (LevelPlayer->GetPos().iY() <= GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
	//{
	//	GetMainCamera()->AddPos(float4::YValue(MovePos));
	//}

	if (LevelPlayer->GetPos().iX() >= LevelBackGround->GetScale().iX() - LevelPlayer->GetScale().iX())
	{
		GameEngineCore::ChangeLevel("VegetableValleyHub");
	}
}

void VegetableValleyIntro::Render()
{

}

void VegetableValleyIntro::Release()
{

}

void VegetableValleyIntro::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.GetHalf());
}

void VegetableValleyIntro::LevelEnd(GameEngineLevel* _NextLevel) { }