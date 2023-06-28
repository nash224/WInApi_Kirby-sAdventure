#include "KirbyDeathEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"


KirbyDeathEffect::KirbyDeathEffect()
{
}

KirbyDeathEffect::~KirbyDeathEffect()
{
}


// 로드 및 텍스처 세팅
void KirbyDeathEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("SpitStar_1x4_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 4, 1);

	MainRenderer->CreateAnimation("StarAnimation", "SpitStar_1x4_16x16.bmp", 0, 3, 0.1f, true);
	MainRenderer->ChangeAnimation("StarAnimation");
}


// 방향 및 위치 지정
void KirbyDeathEffect::init(const float4& _Pos, const float4& _Dir)
{
	EffectDir = _Dir;
	EffectDir.Normalize();

	SetPos(_Pos);

}

// 지정된 방향대로 움직이다 꺼짐
void KirbyDeathEffect::Update(float _Delta)
{
	Target_TotalDecelection_UnitVector += EffectDir * (Target_Distance / StarEffectMoveDuration) * 0.5f * _Delta;
	float4 MovePos = EffectDir * (Target_Distance / StarEffectMoveDuration) - Target_TotalDecelection_UnitVector;

	AddPos(MovePos * _Delta);

	if (GetLiveTime() > StarEffectMoveDuration)
	{
		Death();
		EffectPointerRelease();
	}
}


void KirbyDeathEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}