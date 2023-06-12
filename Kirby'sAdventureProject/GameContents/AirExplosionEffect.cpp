#include "AirExplosionEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameENgineCore/GameEngineLevel.h>

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
}

void AirExplosionEffect::init(const float4& _Pos, const float4& _MaterScale)
{
	SetPos(_Pos + float4{ 0.0f , -_MaterScale.Half().Y });
}


void AirExplosionEffect::Update(float _Delta)
{
	ImageFrameChangeTime += _Delta;

	if (ImageFrameChangeTime > AIREXPLOSIONEFFECTFRAMECHANGETIME)
	{
		ImageFrameChangeTime = 0.0f;

		float4 AirExplosionAEffectPos = float4::ZERO;
		float4 AirExplosionB1EffectPos = float4::ZERO;
		float4 AirExplosionB2EffectPos = float4::ZERO;

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

		AirExplosionAEffect* AirExplosionAEffectPtr = GetLevel()->CreateActor<AirExplosionAEffect>();
		AirExplosionAEffectPtr->init(AirExplosionAEffectPos + GetPos());


		float XCoordinate = 0.0f;
		float YCoordinate = 0.0f;

		switch (ImagePosNumber % 2)
		{
		case 0:
			XCoordinate = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(0, 72) - 36);
			AirExplosionB1EffectPos = float4{ XCoordinate, 36.0f };
			if (XCoordinate > 0.0f)
			{
				XCoordinate = -static_cast<float>(GameEngineRandom::MainRandom.RandomInt(0, 36));
			}
			else
			{
				XCoordinate = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(0, 36));
			}
			AirExplosionB2EffectPos = float4{ XCoordinate, -36.0f };
			break;
		case 1:
			YCoordinate = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(0, 72) - 36);
			AirExplosionB1EffectPos = float4{ 36.0f, YCoordinate };
			if (XCoordinate > 0.0f)
			{
				YCoordinate = -static_cast<float>(GameEngineRandom::MainRandom.RandomInt(0, 36));
			}
			else
			{
				YCoordinate = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(0, 36));
			}
			AirExplosionB2EffectPos = float4{ -36.0f, YCoordinate };
			break;
		default:
			break;
		}

		AirExplosionBEffect* AirExplosionB1EffectPtr = GetLevel()->CreateActor<AirExplosionBEffect>();
		AirExplosionB1EffectPtr->init(GetPos() + AirExplosionB1EffectPos);

		AirExplosionBEffect* AirExplosionB2EffectPtr = GetLevel()->CreateActor<AirExplosionBEffect>();
		AirExplosionB2EffectPtr->init(GetPos() + AirExplosionB2EffectPos);


		ImagePosNumber++;

		if (4 == ImagePosNumber)
		{
			ImagePosNumber = 0;
		}
	}

	if (GetLiveTime() > AIREXPLOSIONEFFECTTIME)
	{
		Death();
	}
}
