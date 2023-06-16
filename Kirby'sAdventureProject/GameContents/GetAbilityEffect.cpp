#include "GetAbilityEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "GlobalContents.h"
#include "SparkleEffect.h"

GetAbilityEffect::GetAbilityEffect()
{
}

GetAbilityEffect::~GetAbilityEffect()
{
}


void GetAbilityEffect::Start()
{

}

void GetAbilityEffect::init(const float4& _Pos, const float4& _MasterScale)
{
	SetPos(_Pos + float4{ 0.0f, -_MasterScale.Half().Y});
}


void GetAbilityEffect::Update(float _Delta)
{
	DurationTime += _Delta;
	if (DurationTime > EffectCreateTime)
	{
		DurationTime = 0.0f;

		float4 CreatePos = float4::ZERO;
		
		float RandomDeg = GameEngineRandom::MainRandom.RandomFloat(0.0f, 360.0f);
		float4 CreateDir = float4::GetUnitVectorFromDeg(RandomDeg);
		float CreateDistance = GameEngineRandom::MainRandom.RandomFloat(SPARKLEEFFECTCREATEMINDISTANCE, SPARKLEEFFECTCREATEMAXDISTANCE);
		CreatePos = CreateDir* CreateDistance;

		SparkleEffect* SparkleEffectPtr = GetLevel()->CreateActor<SparkleEffect>(UpdateOrder::Ability);
		if (nullptr == SparkleEffectPtr)
		{
			MsgBoxAssert("액터가 널일 이유가 없어...");
			return;
		}
		SparkleEffectPtr->init(GetPos() + CreatePos);

		++EffectCreateCount;
	}


	if (10 == EffectCreateCount)
	{
		Death();
	}
}
