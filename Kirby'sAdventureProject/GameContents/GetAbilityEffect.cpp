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



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void GetAbilityEffect::Update(float _Delta)
{
	DurationTime += _Delta;
	if (DurationTime > EffectCreateTime)
	{
		DurationTime = 0.0f;

		// ������ ������ ��ġ�� ���� ����
		float RandomDeg = GameEngineRandom::MainRandom.RandomFloat(0.0f, 360.0f);
		float4 CreateDir = float4::GetUnitVectorFromDeg(RandomDeg);
		float CreateDistance = GameEngineRandom::MainRandom.RandomFloat(CreateMinDistance, CreateMaxDistance);

		float4 CreatePos = float4::ZERO;
		CreatePos = CreateDir* CreateDistance;



		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�");
			return;
		}

		SparkleEffect* SparkleEffectPtr = CurLevelPtr->CreateActor<SparkleEffect>(UpdateOrder::Other);
		if (nullptr == SparkleEffectPtr)
		{
			MsgBoxAssert("���Ͱ� ���� ������ ����...");
			return;
		}

		SparkleEffectPtr->init(GetPos() + CreatePos);


		++EffectCreateCount;
	}


	if (10 == EffectCreateCount)
	{
		Death();
		EffectPointerRelease();
	}
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void GetAbilityEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}
