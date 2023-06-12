#include "ExhaleEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"


ExhaleEffect::ExhaleEffect()
{
}

ExhaleEffect::~ExhaleEffect()
{
}


void ExhaleEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);

	GlobalContents::TextureFileLoad("Left_ExhaleEffect_1x1_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect");
	GlobalContents::TextureFileLoad("Right_ExhaleEffect_1x1_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect");

	MainRenderer->SetTexture("Left_ExhaleEffect_1x1_16x16.bmp");

	Scale = float4{ 48.0f , 48.0f };
	MainRenderer->SetRenderScale(Scale);
}


void ExhaleEffect::init(const float4& _MasterPos, const float4& _MasterScale, const float4& _EffectDir)
{
	EffectDir = _EffectDir;

	if (_EffectDir.X > 0.0f)
	{
		MainRenderer->SetTexture("Right_ExhaleEffect_1x1_16x16.bmp");
	}
	else
	{
		MainRenderer->SetTexture("Left_ExhaleEffect_1x1_16x16.bmp");
	}

	SetPos(_MasterPos + float4{ 0.0f , -_MasterScale.Half().Y } + _EffectDir * (24.0f + Scale.Half().X));
}


void ExhaleEffect::Update(float _Delta)
{
	if (GetLiveTime() < EXHALEEFFECTFORWARDTIME)
	{
		AddPos(EffectDir * EXHALEEFFECTSPEED * _Delta);
	}

	if (GetLiveTime() > EXHALEEFFECTTIME)
	{
		Death();
	}
}
