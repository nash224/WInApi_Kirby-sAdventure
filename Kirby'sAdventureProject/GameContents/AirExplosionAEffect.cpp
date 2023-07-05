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
		MsgBoxAssert("�������� ���� ������ ����..");
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



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

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



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void AirExplosionAEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}