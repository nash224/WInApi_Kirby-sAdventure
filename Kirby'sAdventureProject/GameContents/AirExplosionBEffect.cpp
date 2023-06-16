#include "AirExplosionBEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"

AirExplosionBEffect::AirExplosionBEffect()
{
}

AirExplosionBEffect::~AirExplosionBEffect()
{
}


void AirExplosionBEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("BombEffectA_1x3_16x16.bmp", "Resources\\Effect\\SkillEffect", 3, 1);

	MainRenderer->CreateAnimation("Afterimage2", "BombEffectA_1x3_16x16.bmp", 1, 2, AIREXPLOSIONBEFFECTFRAMECHANGETIME, false);
	MainRenderer->ChangeAnimation("Afterimage2");

}

void AirExplosionBEffect::init(const float4& _ExplosionPos)
{
	SetPos(_ExplosionPos);
}


void AirExplosionBEffect::Update(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		Death();
		EffectPointerRelease();
	}
}
