#include "SparkEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"

SparkEffect::SparkEffect()
{
}

SparkEffect::~SparkEffect()
{
}


void SparkEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);

	GlobalContents::TextureFileLoad("SparkEffect_1x1_16x16.bmp", "Resources\\Effect\\SkillEffect");

	MainRenderer->SetTexture("SparkEffect_1x1_16x16.bmp");
	MainRenderer->SetRenderScaleToTexture();

	Scale = ResourcesManager::GetInst().FindTexture("SparkEffect_1x1_16x16.bmp")->GetScale();
}

void SparkEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	Dir = _Dir;
	SetPos(_Pos + _Dir * _MaterScale.Half().Max2D() + float4{ 0.0f , -_MaterScale.Half().Y });
}


void SparkEffect::Update(float _Delta)
{
	float EffectSpeed = SPARKEFFECTDISTANCE / SPARKEFFECTTIME;
	
	CurrentEffectDistance += EffectSpeed * _Delta;

	AddPos(Dir * EffectSpeed * _Delta);

	if (CurrentEffectDistance > SPARKEFFECTDISTANCE)
	{
		Death();
	}
}
