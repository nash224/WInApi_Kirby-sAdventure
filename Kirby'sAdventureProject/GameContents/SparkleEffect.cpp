#include "SparkleEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"

SparkleEffect::SparkleEffect()
{
}

SparkleEffect::~SparkleEffect()
{
}


void SparkleEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("ChangeModeEffect_1x3_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 3, 1);
	MainRenderer->CreateAnimation("ChangeModeEffect", "ChangeModeEffect_1x3_16x16.bmp", 0, 2, ChangeEffectFramesInter, false);

	MainRenderer->ChangeAnimation("ChangeModeEffect");
}

void SparkleEffect::init(const float4& _Pos)
{
	SetPos(_Pos);
}

void SparkleEffect::Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		EffectPointerRelease();
		return;
	}
}
