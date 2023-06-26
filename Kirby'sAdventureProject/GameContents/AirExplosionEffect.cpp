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


	// 사운드 로드
	GlobalContents::SoundFileLoad("Scrafy_Bomb.wav", "Resources\\SoundResources\\EffectVoice");
}

void AirExplosionEffect::init(const float4& _Pos, const float4& _MaterScale)
{
	SetPos(_Pos + float4{ 0.0f , -_MaterScale.Half().Y });

	
	// 사운드 재생
	GameEngineSound::SoundPlay("Scrafy_Bomb.wav");
}


void AirExplosionEffect::Update(float _Delta)
{
	ImageFrameChangeTime += _Delta;

	if (ImageFrameChangeTime > AIREXPLOSIONEFFECTFRAMECHANGETIME)
	{
		ImageFrameChangeTime = 0.0f;


		// 위치선언
		float4 AirExplosionAEffectPos = float4::ZERO;
		float4 AirExplosionB1EffectPos = float4::ZERO;
		float4 AirExplosionB2EffectPos = float4::ZERO;

		// 몇 회차에 따라 등장위치가 특정 사각형 모서리 위치로 지정
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


		// A이펙트 생성
		AirExplosionAEffect* AirExplosionAEffectPtr = GetLevel()->CreateActor<AirExplosionAEffect>(UpdateOrder::Ability);
		if (nullptr == AirExplosionAEffectPtr)
		{
			MsgBoxAssert("액터가 Null 입니다.");
			return;
		}
		
		AirExplosionAEffectPtr->init(AirExplosionAEffectPos + GetPos());




		// 지정된 사각형 선위에 이펙트 생성
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


		// 지정된 위치에 이펙트 생성
		AirExplosionBEffect* AirExplosionB1EffectPtr = GetLevel()->CreateActor<AirExplosionBEffect>(UpdateOrder::Ability);
		if (nullptr == AirExplosionB1EffectPtr)
		{
			MsgBoxAssert("액터가 Null 입니다.");
			return;
		}

		AirExplosionB1EffectPtr->init(GetPos() + AirExplosionB1EffectPos);



		// 지정된 위치에 이펙트 생성
		AirExplosionBEffect* AirExplosionB2EffectPtr = GetLevel()->CreateActor<AirExplosionBEffect>(UpdateOrder::Ability);
		if (nullptr == AirExplosionB2EffectPtr)
		{
			MsgBoxAssert("액터가 Null 입니다.");
			return;
		}

		AirExplosionB2EffectPtr->init(GetPos() + AirExplosionB2EffectPos);


		// A임펙트 이미지 위치변경
		ImagePosNumber++;

		// 4번째면 다시 처음으로
		if (4 == ImagePosNumber)
		{
			ImagePosNumber = 0;
			++EndCycle;
		}
	}


	// 해제하고 초기화
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
