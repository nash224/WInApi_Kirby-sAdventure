#include "CrossDeathEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"
#include "MoveStarEffect.h"


CrossDeathEffect::CrossDeathEffect()
{
}

CrossDeathEffect::~CrossDeathEffect()
{
}


void CrossDeathEffect::Start()
{

}


void CrossDeathEffect::init(const float4& _Pos, const float4& _MasterScale)
{
	SetPos(_Pos + float4{ 0.0f, -_MasterScale.Half().Y});
	EffectDuration = 0.0f;
	StarEffectCreateAngle = 0.0f;
}


void CrossDeathEffect::Update(float _Delta)
{
	EffectDuration += _Delta;
	if (EffectDuration > STAREFFECTENDTIME)
	{
		EffectDuration = 0.0f;

		for (size_t i = 0; i < STAREFFECTCREATECOUNT; i++)
		{
			StarEffectCreateAngle += 90.0f;
			EffectDir = float4::GetUnitVectorFromDeg(StarEffectCreateAngle);
			MoveStarEffect* MoveStarEffectPtr = GetLevel()->CreateActor<MoveStarEffect>(UpdateOrder::Ability);
			MoveStarEffectPtr->init(GetPos(), EffectDir);
		}

		StarEffectCreateAngle = 45.0f;
		++CreateStarNumber;
	}

	if (CreateStarNumber >= 2)
	{
		Death();
	}
}
