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
}


void CrossDeathEffect::Update(float _Delta)
{
	EffectDuration += _Delta;

	// 일정 시간이 되면 별 소환
	if (EffectDuration > STAREFFECTENDTIME || true == IsFrist)
	{
		EffectDuration = 0.0f;

		// for문을 돌면서 별효과를 십자형으로 소환
		for (size_t i = 0; i < STAREFFECTCREATECOUNT; i++)
		{
			StarEffectCreateAngle += 90.0f;

			EffectDir = float4::GetUnitVectorFromDeg(StarEffectCreateAngle);

			MoveStarEffect* MoveStarEffectPtr = GetLevel()->CreateActor<MoveStarEffect>(UpdateOrder::Ability);
			if (nullptr == MoveStarEffectPtr)
			{
				MsgBoxAssert("Effect가 널일리가 없어..");
				return;
			}
			MoveStarEffectPtr->init(GetPos(), EffectDir);
		}

		// 다음 시작각도
		StarEffectCreateAngle = 45.0f;

		++CreateStarNumber;
		IsFrist = false;
	}

	// 십자형이 2번 소환되면 메모리 해제
	if (CreateStarNumber >= 2)
	{
		Death();
		EffectPointerRelease();
	}
}



void CrossDeathEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}