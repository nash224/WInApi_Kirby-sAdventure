#include "AirExplosionBEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>




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
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	GlobalContents::SpriteFileLoad("BombEffectA_1x3_16x16.bmp", "Resources\\Effect\\SkillEffect", 3, 1);

	MainRenderer->CreateAnimation("Afterimage2", "BombEffectA_1x3_16x16.bmp", 1, 2, FrameChangeTime, false);
	MainRenderer->ChangeAnimation("Afterimage2");

}

void AirExplosionBEffect::init(const float4& _ExplosionPos)
{
	SetPos(_ExplosionPos);
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void AirExplosionBEffect::Update(float _Delta)
{
	if (MainRenderer->IsAnimationEnd())
	{
		Death();
		EffectPointerRelease();
	}
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void AirExplosionBEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}