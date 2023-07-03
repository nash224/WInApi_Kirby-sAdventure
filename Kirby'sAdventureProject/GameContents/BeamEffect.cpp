#include "BeamEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameENgineCore/GameEngineLevel.h>

#include "GlobalContents.h"
#include "CommonSkillEffect.h"
#include "Kirby.h"



bool BeamEffect::BeamEndValue = false;
BeamEffect::BeamEffect()
{
}

BeamEffect::~BeamEffect()
{
}


void BeamEffect::Start()
{

	// 사운드 로드
	GlobalContents::SoundFileLoad("BeamSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("BeamExtraSound.wav", "Resources\\SoundResources\\EffectVoice");
}

void BeamEffect::init(const float4& _Pos, const float4& _MasterScale, const float4& _EffectDir)
{
	SetPos(_Pos + float4{ 0.0f , -_MasterScale.Half().Y });

	MasterScale = _MasterScale;

	EffectDir = _EffectDir;
}



void BeamEffect::SetActorCollision(CollisionOrder _Order, CollisionType _Type, const float4& _None)
{
	BeamOrder = _Order;
	BeamType = _Type;

	if (CollisionOrder::PlayerAbility == _Order)
	{
		BeamEndValue = false;
	}
}




void BeamEffect::Update(float _Delta)
{
	EffectFrameChangeTime += _Delta;

	float4 BeamDir = float4::ZERO;
	float4 EffectPos = float4::ZERO;


	// 빔 각도 설정
	if (EffectFrameChangeTime > BEAMEFFECTFRAMECHANGETIME)
	{
		EffectFrameChangeTime = 0.0f;


		if (CollisionOrder::PlayerAbility == BeamOrder)
		{
			Kirby* KirbyPtr = Kirby::GetMainKirby();
			if (nullptr == KirbyPtr)
			{
				MsgBoxAssert("커비를 불러오지 못했습니다.");
				return;
			}

			SetPos(KirbyPtr->GetPos() + float4{ 0.0f , -MasterScale.Half().Y });
		}



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
			// 첫번째 빔
			{
				EffectPos = BeamDir * BEAMEFFECTSHORTDISTANCE + GetPos();

				CommonSkillEffect* BeamUnitEffectPtr = GetLevel()->CreateActor<CommonSkillEffect>(UpdateOrder::Ability);
				if (nullptr == BeamUnitEffectPtr)
				{
					MsgBoxAssert("생성한 Effect가 Null입니다.");
					return;
				}

				BeamUnitEffectPtr->init("Resources\\Effect\\SkillEffect", "BeamEffect_1x1_8x8.bmp", EffectPos);
				BeamUnitEffectPtr->SetExpressionTime(BEAMEFFECTTIME);
				BeamUnitEffectPtr->SetActorCollision(BeamOrder, BeamType, float4{ 16.0f , 16.0f });


				// 사운드 재생
				GameEngineSound::SoundPlay("BeamSound.wav");
			}

			// 두번째 빔
			{
				EffectPos = BeamDir * BEAMEFFECTMIDDLEDISTANCE + GetPos();

				CommonSkillEffect* BeamUnitEffectPtr = GetLevel()->CreateActor<CommonSkillEffect>(UpdateOrder::Ability);
				if (nullptr == BeamUnitEffectPtr)
				{
					MsgBoxAssert("생성한 Effect가 Null입니다.");
					return;
				}

				BeamUnitEffectPtr->init("Resources\\Effect\\SkillEffect", "BeamEffect_1x1_8x8.bmp", EffectPos);
				BeamUnitEffectPtr->SetExpressionTime(BEAMEFFECTTIME);
				BeamUnitEffectPtr->SetActorCollision(BeamOrder, BeamType, float4{ 16.0f , 16.0f });
			}
		}

		if (3 == BeamChangePosCount)
		{
			EffectPos = BeamDir * BEAMEFFECTLONGDISTANCE + GetPos();
			CommonSkillEffect* BeamUnitEffectPtr = GetLevel()->CreateActor<CommonSkillEffect>(UpdateOrder::Ability);
			if (nullptr == BeamUnitEffectPtr)
			{
				MsgBoxAssert("생성한 Effect가 Null입니다.");
				return;
			}
			BeamUnitEffectPtr->init("Resources\\Effect\\SkillEffect", "BeamEffect_1x1_8x8.bmp", EffectPos);
			BeamUnitEffectPtr->SetExpressionTime(BEAMEFFECTTIME);
			BeamUnitEffectPtr->SetActorCollision(BeamOrder, BeamType, float4{ 16.0f , 16.0f });


			// 사운드 재생
			GameEngineSound::SoundPlay("BeamExtraSound.wav");
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
		if (CollisionOrder::PlayerAbility == BeamOrder)
		{
			BeamEndValue = true;
		}

		Death();
		EffectPointerRelease();
		return;
	}
}



void BeamEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}