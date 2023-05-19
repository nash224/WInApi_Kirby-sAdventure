#include "VegetableValleyHub.h"

#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourceManager.h>


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
	LevelBackGround->init("VegetableValley.bmp", "Resources\\Map", float4{ 0 , 0 }, float4{ 470 , 360 });

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
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

	GameEngineWindowTexture* Texture = ResourceManager::GetInst().FindTexture("VegetableValley.bmp");
	float4 Scale = Texture->GetScale();
	if (LevelPlayer->GetPos().iX() >= Scale.iX() - LevelPlayer->GetScale().iX())
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
	LevelPlayer = Player::GetMainPlayer();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}

void VegetableValleyHub::LevelEnd(GameEngineLevel* _NextLevel) { }