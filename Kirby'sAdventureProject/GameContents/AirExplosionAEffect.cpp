#include "AirExplosionAEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>



AirExplosionAEffect::AirExplosionAEffect()
{
}

AirExplosionAEffect::~AirExplosionAEffect()
{
}


void AirExplosionAEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("BombEffectA_1x3_16x16.bmp", "Resources\\Effect\\SkillEffect", 3, 1);

	MainRenderer->CreateAnimation("Afterimage2", "BombEffectA_1x3_16x16.bmp", 0, 0, 0.44f, false);
	MainRenderer->ChangeAnimation("Afterimage2");
}

void AirExplosionAEffect::init(const float4& _ExplosionPos)
{
	SetPos(_ExplosionPos);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void AirExplosionAEffect::Update(float _Delta)
{
	if (GetLiveTime() > FrameChangeTime)
	{
		if (nullptr != MainRenderer)
		{
			Death();
			EffectPointerRelease();
		}
	}
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void AirExplosionAEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}