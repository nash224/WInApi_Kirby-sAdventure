#include "PlayLevel.h"
#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{

}



void PlayLevel::Start() 
{
	VegetableValley1 = GameEngineLevel::CreateActor<BackGround>();
	VegetableValley1->init("VegetableValley1.bmp", float4{ 2 , 2 }, float4{ 1016 , 168 });

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('U'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (LevelPlayer->GetPos().iX() == 0)
	{
		;
	}
	
}

void PlayLevel::Render() 
{

}

void PlayLevel::Release() 
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.GetHalf());
} 

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel) { }