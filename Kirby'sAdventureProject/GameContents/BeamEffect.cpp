#include "BeamEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameENgineCore/GameEngineLevel.h>

#include "GlobalContents.h"
#include "AirExplosionAEffect.h"
#include "AirExplosionBEffect.h"

BeamEffect::BeamEffect()
{
}

BeamEffect::~BeamEffect()
{
}


void BeamEffect::Start()
{
	Scale = float4{ (BeamEffectDISTANCE) * 2.0f , (BeamEffectDISTANCE) * 2.0f };
}

void BeamEffect::init(const float4& _Pos, const float4& _MaterScale)
{
	SetPos(_Pos + float4{ 0.0f , -_MaterScale.Half().Y });
}


void BeamEffect::Update(float _Delta)
{
	ImageFrameChangeTime += _Delta;

	if (GetLiveTime() > BeamEffectTIME)
	{
		Death();
	}
}
