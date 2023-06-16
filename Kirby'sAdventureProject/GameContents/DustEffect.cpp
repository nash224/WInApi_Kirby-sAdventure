#include "DustEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"

DustEffect::DustEffect()
{
}

DustEffect::~DustEffect()
{
}


void DustEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("Smoke_1x2_8x10.bmp", "Resources\\Effect\\KirbyBaseEffect", 2, 1);

	MainRenderer->CreateAnimation("DustEffectAnimation", "Smoke_1x2_8x10.bmp", 0, 1, DUSTEFFECTFRAMECHANGETIME, false);
	MainRenderer->ChangeAnimation("DustEffectAnimation");
}


void DustEffect::init(const float4& _MasterPos, const float4& _MasterScale, const float4& _Dir, int _ItersCount/* = 1*/)
{
	SetPos(_MasterPos + _Dir * (_MasterScale.Half().X + 12.0f));

	EffectDir = _Dir;

	// 방향 값에 따라 방향이 결정됨
	if (EffectDir.X > 0.0f)
	{
		EffectDir = float4{ 0.8f, -0.2f };
	}
	else
	{
		EffectDir = float4{ -0.8f, -0.2f };
	}
}


void DustEffect::Update(float _Delta)
{
	AddPos(EffectDir * DUSTEFFECTSPEED * _Delta);

	if (MainRenderer->IsAnimationEnd())
	{
		Death();
		MainRenderer = nullptr;
	}
}
