#include "VegetableValley11.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

// contents
#include "Player.h"
#include "BackGround.h"
#include "GameEffect.h"

VegetableValley11::VegetableValley11() 
{
}

VegetableValley11::~VegetableValley11() 
{

}

/* texture type
	CreateAnimation("HillProjectionEffect", "CloudAndWater12x3_8x8.bmp", 0, 2, 0.15f, true);
	CreateAnimation("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, 0.15f, true);
	CreateAnimation("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, 0.15f, true);

*/

void VegetableValley11::Start() 
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1.bmp", "Resources\\Map", float4{ 2 , 2 }, float4{ 1016 , 168 });

	LevelEffect = GameEngineLevel::CreateActor<GameEffect>();
	LevelEffect->init("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);




	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void VegetableValley11::Update(float _Delta)
{

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


//void VegetableValley11::CreateAndSetupBackgroundEffectRenderer(
//	const std::string& _AnimationName,
//	const std::string& _FileName,
//	int _StartFrame, int _EndFrame,
//	float4 _Pos, float _Ratio,
//	float _Inter/* = 0.1f*/, bool _Loop/* = true*/)
//{
//	GameEngineRenderer* Render = LevelEffect->CreateRenderer(RenderOrder::BackGroundEffect);
//	Render->CreateAnimation(_AnimationName, _FileName, _StartFrame, _EndFrame, _Inter, _Loop);
//	Render->SetRenderPos(_Pos);
//	Render->SetScaleRatio(_Ratio);
//	Render->ChangeAnimation(_AnimationName);
//}