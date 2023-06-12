#include "FrameBreathEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"


FrameBreathEffect::FrameBreathEffect()
{
}

FrameBreathEffect::~FrameBreathEffect()
{
}


void FrameBreathEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);

	GlobalContents::SpriteFileLoad("Left_FireEffect_2x1_16x16.bmp", "Resources\\Effect\\SkillEffect", 2, 1);
	GlobalContents::SpriteFileLoad("Right_FireEffect_2x1_16x16.bmp", "Resources\\Effect\\SkillEffect", 2, 1);

	MainRenderer->CreateAnimation("Left_FireEffect", "Left_FireEffect_2x1_16x16.bmp", 0, 1, 0.1f, true);
	MainRenderer->CreateAnimation("Right_FireEffect", "Right_FireEffect_2x1_16x16.bmp", 0, 1, 0.1f, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 48.0f , 48.0f };
	SetCheckPoint(Scale);
}

void FrameBreathEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });

	if (EffectDir.X < 0.0f)
	{
		MainRenderer->ChangeAnimation("Left_FireEffect");
	}
	else if (EffectDir.X >= 0.0f)
	{
		MainRenderer->ChangeAnimation("Right_FireEffect");
	}


	// Dir ÀçÁ¤ÀÇ

}


void FrameBreathEffect::Update(float _Delta)
{
	if (true == IsPassGround)
	{
		GroundPassUpdate(_Delta);
	}
	else if (false == IsPassGround)
	{
		GroundNotPassUpdate(_Delta);
	}
}


void FrameBreathEffect::GroundPassUpdate(float _Delta)
{
	if (GetLiveTime() > FRAMEBREATHEFFECTDURATION)
	{
		Death();
	}

	float EffectSpeed = FRAMEBREATHEFFECTDISTANCE / FRAMEBREATHEFFECTDURATION;
	AddPos(EffectDir * EffectSpeed * _Delta);
}


void FrameBreathEffect::GroundNotPassUpdate(float _Delta)
{

}