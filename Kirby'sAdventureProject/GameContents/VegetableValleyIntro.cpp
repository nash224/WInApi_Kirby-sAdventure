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
	LevelBackGround->init("CutsceneBackgrounds.bmp", "Resources\\Map", float4{ 4 , 21 }, float4{ 256 , 240 });

	//LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void VegetableValleyIntro::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}


	if (true == GameEngineInput::IsDown('A'))
	{
		GameEngineCore::ChangeLevel("VegetableValley11");
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
	//if (nullptr == LevelPlayer)
	//{
	//	MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	//}
}

void VegetableValleyIntro::LevelEnd(GameEngineLevel* _NextLevel) { }