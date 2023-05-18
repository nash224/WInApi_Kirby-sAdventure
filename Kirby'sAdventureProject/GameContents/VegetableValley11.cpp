#include "VegetableValley11.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Player.h"
#include "BackGround.h"
#include "GameEffect.h"


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

	LevelEffect = GameEngineLevel::CreateActor<GameEffect>();
	LevelEffect->init("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	GameEngineRenderer* Render1 = LevelEffect->CreateRenderer(RenderOrder::BackGroundEffect);
	Render1->CreateAnimation("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, 0.15f, true);
	Render1->SetRenderPos({ 20 , 20 });
	Render1->SetScaleRatio(3.0f);
	Render1->ChangeAnimation("ForestProjectionEffect");

	GameEngineRenderer* Render2 = LevelEffect->CreateRenderer(RenderOrder::BackGroundEffect);
	Render2->CreateAnimation("HillProjectionEffect", "CloudAndWater12x3_8x8.bmp", 0, 2, 0.15f, true);
	Render2->SetRenderPos({ 40 , 20 });
	Render2->SetScaleRatio(3.0f);
	Render2->ChangeAnimation("HillProjectionEffect");



	//CreateAnimation("HillProjectionEffect", "CloudAndWater12x3_8x8.bmp", 0, 2, 0.15f, true);
	//CreateAnimation("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, 0.15f, true);
	//CreateAnimation("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, 0.15f, true);

	//LevelPlayer = GameEngineLevel::CreateActor<Player>();
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

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValley12");
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
	LevelPlayer = Player::GetMainPlayer();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) { }