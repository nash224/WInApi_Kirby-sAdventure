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

	// ���� �ð��� �Ǹ� �� ��ȯ
	if (EffectDuration > STAREFFECTENDTIME || true == IsFrist)
	{
		EffectDuration = 0.0f;

		// for���� ���鼭 ��ȿ���� ���������� ��ȯ
		for (size_t i = 0; i < STAREFFECTCREATECOUNT; i++)
		{
			StarEffectCreateAngle += 90.0f;

			EffectDir = float4::GetUnitVectorFromDeg(StarEffectCreateAngle);

			MoveStarEffect* MoveStarEffectPtr = GetLevel()->CreateActor<MoveStarEffect>(UpdateOrder::Ability);
			if (nullptr == MoveStarEffectPtr)
			{
				MsgBoxAssert("Effect�� ���ϸ��� ����..");
				return;
			}
			MoveStarEffectPtr->init(GetPos(), EffectDir);
		}

		// ���� ���۰���
		StarEffectCreateAngle = 45.0f;

		++CreateStarNumber;
		IsFrist = false;
	}

	// �������� 2�� ��ȯ�Ǹ� �޸� ����
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