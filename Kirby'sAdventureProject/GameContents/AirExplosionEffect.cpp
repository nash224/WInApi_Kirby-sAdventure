#include "AirExplosionEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "GlobalContents.h"
#include "AirExplosionAEffect.h"
#include "AirExplosionBEffect.h"

AirExplosionEffect::AirExplosionEffect()
{
}

AirExplosionEffect::~AirExplosionEffect()
{
}


void AirExplosionEffect::Start()
{
	Scale = float4{ (AIREXPLOSIONEFFECTDISTANCE) * 2.0f , (AIREXPLOSIONEFFECTDISTANCE) * 2.0f };


	// ���� �ε�
	GlobalContents::SoundFileLoad("Scrafy_Bomb.wav", "Resources\\SoundResources\\EffectVoice");
}

void AirExplosionEffect::init(const float4& _Pos, const float4& _MaterScale)
{
	SetPos(_Pos + float4{ 0.0f , -_MaterScale.Half().Y });

	
	// ���� ���
	GameEngineSound::SoundPlay("Scrafy_Bomb.wav");
}


void AirExplosionEffect::Update(float _Delta)
{
	ImageFrameChangeTime += _Delta;

	if (ImageFrameChangeTime > AIREXPLOSIONEFFECTFRAMECHANGETIME)
	{
		ImageFrameChangeTime = 0.0f;


		// ��ġ����
		float4 AirExplosionAEffectPos = float4::ZERO;
		float4 AirExplosionB1EffectPos = float4::ZERO;
		float4 AirExplosionB2EffectPos = float4::ZERO;

		// �� ȸ���� ���� ������ġ�� Ư�� �簢�� �𼭸� ��ġ�� ����
		switch (ImagePosNumber)
		{
		case 0:
			AirExplosionAEffectPos = float4{ AIREXPLOSIONEFFECTADISTANCE, AIREXPLOSIONEFFECTADISTANCE };
			break;
		case 1:
			AirExplosionAEffectPos = float4{ -AIREXPLOSIONEFFECTADISTANCE, AIREXPLOSIONEFFECTADISTANCE };
			break;
		case 2:
			AirExplosionAEffectPos = float4{ -AIREXPLOSIONEFFECTADISTANCE, -AIREXPLOSIONEFFECTADISTANCE };
			break;
		case 3:
			AirExplosionAEffectPos = float4{ AIREXPLOSIONEFFECTADISTANCE, -AIREXPLOSIONEFFECTADISTANCE };
			break;
		default:
			break;
		}


		// A����Ʈ ����
		AirExplosionAEffect* AirExplosionAEffectPtr = GetLevel()->CreateActor<AirExplosionAEffect>(UpdateOrder::Ability);
		if (nullptr == AirExplosionAEffectPtr)
		{
			MsgBoxAssert("���Ͱ� Null �Դϴ�.");
			return;
		}
		
		AirExplosionAEffectPtr->init(AirExplosionAEffectPos + GetPos());




		// ������ �簢�� ������ ����Ʈ ����
		float XCoordinate = 0.0f;
		float YCoordinate = 0.0f;

		switch (ImagePosNumber % 2)
		{
		case 0:
			XCoordinate = GameEngineRandom::MainRandom.RandomFloat(0.0f, 72.0f) - 36.0f;
			AirExplosionB1EffectPos = float4{ XCoordinate, 36.0f };
			if (XCoordinate > 0.0f)
			{
				XCoordinate = -GameEngineRandom::MainRandom.RandomFloat(0.0f, 36.0f);
			}
			else
			{
				XCoordinate = GameEngineRandom::MainRandom.RandomFloat(0.0f, 36.0f);
			}
			AirExplosionB2EffectPos = float4{ XCoordinate, -36.0f };
			break;
		case 1:
			YCoordinate = GameEngineRandom::MainRandom.RandomFloat(0.0f, 72.0f) - 36.0f;
			AirExplosionB1EffectPos = float4{ 36.0f, YCoordinate };
			if (XCoordinate > 0.0f)
			{
				YCoordinate = -GameEngineRandom::MainRandom.RandomFloat(0.0f, 36.0f);
			}
			else
			{
				YCoordinate = GameEngineRandom::MainRandom.RandomFloat(0.0f, 36.0f);
			}
			AirExplosionB2EffectPos = float4{ -36.0f, YCoordinate };
			break;
		default:
			break;
		}


		// ������ ��ġ�� ����Ʈ ����
		AirExplosionBEffect* AirExplosionB1EffectPtr = GetLevel()->CreateActor<AirExplosionBEffect>(UpdateOrder::Ability);
		if (nullptr == AirExplosionB1EffectPtr)
		{
			MsgBoxAssert("���Ͱ� Null �Դϴ�.");
			return;
		}

		AirExplosionB1EffectPtr->init(GetPos() + AirExplosionB1EffectPos);



		// ������ ��ġ�� ����Ʈ ����
		AirExplosionBEffect* AirExplosionB2EffectPtr = GetLevel()->CreateActor<AirExplosionBEffect>(UpdateOrder::Ability);
		if (nullptr == AirExplosionB2EffectPtr)
		{
			MsgBoxAssert("���Ͱ� Null �Դϴ�.");
			return;
		}

		AirExplosionB2EffectPtr->init(GetPos() + AirExplosionB2EffectPos);


		// A����Ʈ �̹��� ��ġ����
		ImagePosNumber++;

		// 4��°�� �ٽ� ó������
		if (4 == ImagePosNumber)
		{
			ImagePosNumber = 0;
			++EndCycle;
		}
	}


	// �����ϰ� �ʱ�ȭ
	if (2 == EndCycle)
	{
		Death();
		EffectPointerRelease();
		return;
	}


	if (false == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::PlayerBody);
	}
}
