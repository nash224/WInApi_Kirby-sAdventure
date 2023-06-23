#include "BeamEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameENgineCore/GameEngineLevel.h>

#include "GlobalContents.h"
#include "CommonSkillEffect.h"
#include "Kirby.h"

BeamEffect::BeamEffect()
{
}

BeamEffect::~BeamEffect()
{
}


void BeamEffect::Start()
{
}

void BeamEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _EffectDir)
{
	SetPos(_Pos + float4{ 0.0f , -_MaterScale.Half().Y });

	EffectDir = _EffectDir;
}



void BeamEffect::SetActorCollision(CollisionOrder _Order, CollisionType _Type)
{
	BeamOrder = _Order;
	BeamType = _Type;

}




void BeamEffect::Update(float _Delta)
{
	EffectFrameChangeTime += _Delta;


	float4 BeamDir = float4::ZERO;
	float4 EffectPos = float4::ZERO;


	// ������� ����Կ��� for������ ���� ���� : �̶� ������ ���߽��ϴ�.. 
	if (EffectFrameChangeTime > BEAMEFFECTFRAMECHANGETIME)
	{
		EffectFrameChangeTime = 0.0f;

		switch (EffectPosNumber)
		{
		case 7:
			BeamDir = float4::GetUnitVectorFromDeg(90.0f);
			break;
		case 6:
			BeamDir = float4::GetUnitVectorFromDeg(102.5f);
			break;
		case 5:
			BeamDir = float4::GetUnitVectorFromDeg(135.0f);
			break;
		case 4:
			BeamDir = float4::GetUnitVectorFromDeg(157.5f);
			break;
		case 3:
			BeamDir = float4::GetUnitVectorFromDeg(180.0f);
			break;
		case 2:
			BeamDir = float4::GetUnitVectorFromDeg(202.5f);
			break;
		case 1:
			BeamDir = float4::GetUnitVectorFromDeg(225.0f);
			break;
		default:
			break;
		}

		BeamDir = float4{ BeamDir.X , -BeamDir.Y };

		if (EffectDir.X > 0.0f)
		{
			BeamDir = float4{ -BeamDir.X , BeamDir.Y };
		}


		if (1 == BeamChangePosCount)
		{
			// ù��° ��
			{
				EffectPos = BeamDir * BEAMEFFECTSHORTDISTANCE + GetPos();

				CommonSkillEffect* BeamUnitEffectPtr = GetLevel()->CreateActor<CommonSkillEffect>(UpdateOrder::Ability);
				if (nullptr == BeamUnitEffectPtr)
				{
					MsgBoxAssert("������ Effect�� Null�Դϴ�.");
					return;
				}

				BeamUnitEffectPtr->init("Resources\\Effect\\SkillEffect", "BeamEffect_1x1_8x8.bmp", EffectPos);
				BeamUnitEffectPtr->SetExpressionTime(BEAMEFFECTTIME);
				BeamUnitEffectPtr->SetActorCollision(BeamOrder, BeamType);
			}

			// �ι�° ��
			{
				EffectPos = BeamDir * BEAMEFFECTMIDDLEDISTANCE + GetPos();

				CommonSkillEffect* BeamUnitEffectPtr = GetLevel()->CreateActor<CommonSkillEffect>(UpdateOrder::Ability);
				if (nullptr == BeamUnitEffectPtr)
				{
					MsgBoxAssert("������ Effect�� Null�Դϴ�.");
					return;
				}

				BeamUnitEffectPtr->init("Resources\\Effect\\SkillEffect", "BeamEffect_1x1_8x8.bmp", EffectPos);
				BeamUnitEffectPtr->SetExpressionTime(BEAMEFFECTTIME);
				BeamUnitEffectPtr->SetActorCollision(BeamOrder, BeamType);
			}
		}

		if (3 == BeamChangePosCount)
		{
			EffectPos = BeamDir * BEAMEFFECTLONGDISTANCE + GetPos();
			CommonSkillEffect* BeamUnitEffectPtr = GetLevel()->CreateActor<CommonSkillEffect>(UpdateOrder::Ability);
			if (nullptr == BeamUnitEffectPtr)
			{
				MsgBoxAssert("������ Effect�� Null�Դϴ�.");
				return;
			}
			BeamUnitEffectPtr->init("Resources\\Effect\\SkillEffect", "BeamEffect_1x1_8x8.bmp", EffectPos);
			BeamUnitEffectPtr->SetExpressionTime(BEAMEFFECTTIME);
			BeamUnitEffectPtr->SetActorCollision(BeamOrder, BeamType);
		}


		if (3 == BeamChangePosCount)
		{
			BeamChangePosCount = 0;
			--EffectPosNumber;
		}

		++BeamChangePosCount;
	}


	if (0 == EffectPosNumber)
	{
		Death();
		return;
	}
}
