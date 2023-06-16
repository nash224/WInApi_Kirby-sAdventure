#include "MoveStarEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"


MoveStarEffect::MoveStarEffect()
{
}

MoveStarEffect::~MoveStarEffect()
{
}


void MoveStarEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);

	GlobalContents::TextureFileLoad("StarEffect_1x1_24x24.bmp", "Resources\\Effect\\SkillEffect");

	MainRenderer->SetTexture("StarEffect_1x1_24x24.bmp");
}


void MoveStarEffect::init(const float4& _Pos, const float4& _Dir)
{
	EffectDir = _Dir;
	EffectDir.Normalize();

	SetPos(_Pos);
}


void MoveStarEffect::Update(float _Delta)
{
	AddPos(EffectDir * STAREFFECTSPEED * _Delta);

	if (GetLiveTime() > STAREFFECTMOVETIME)
	{
		Death();
	}
}
