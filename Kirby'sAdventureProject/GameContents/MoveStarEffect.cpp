#include "MoveStarEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"


MoveStarEffect::MoveStarEffect()
{
}

MoveStarEffect::~MoveStarEffect()
{
}


// 로드 및 텍스처 세팅
void MoveStarEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::TextureFileLoad("StarEffect_1x1_24x24.bmp", "Resources\\Effect\\SkillEffect");

	MainRenderer->SetTexture("StarEffect_1x1_24x24.bmp");
}


// 방향 및 위치 지정
void MoveStarEffect::init(const float4& _Pos, const float4& _Dir)
{
	EffectDir = _Dir;
	EffectDir.Normalize();

	SetPos(_Pos);
}

void MoveStarEffect::SetSpeedAndDuration(float _Speed, float _Duration)
{
	StarEffectSpeed = _Speed;
	StarEffectMoveDuration = _Duration;
}


// 지정된 방향대로 움직이다 꺼짐
void MoveStarEffect::Update(float _Delta)
{
	AddPos(EffectDir * StarEffectSpeed * _Delta);

	if (GetLiveTime() > StarEffectMoveDuration)
	{
		Death();
		EffectPointerRelease();
	}
}


void MoveStarEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}