#include "FrameBreathEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>



FrameBreathEffect::FrameBreathEffect()
{
}

FrameBreathEffect::~FrameBreathEffect()
{
}


void FrameBreathEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("Left_FireEffect_2x1_16x16.bmp", "Resources\\Effect\\SkillEffect", 2, 1);
	GlobalContents::SpriteFileLoad("Right_FireEffect_2x1_16x16.bmp", "Resources\\Effect\\SkillEffect", 2, 1);

	MainRenderer->CreateAnimation("Left_FireEffect", "Left_FireEffect_2x1_16x16.bmp", 0, 1, 0.1f, true);
	MainRenderer->CreateAnimation("Right_FireEffect", "Right_FireEffect_2x1_16x16.bmp", 0, 1, 0.1f, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 48.0f , 48.0f };
	SetCheckPoint(Scale);



	// 사운드 로드
	GlobalContents::SoundFileLoad("Ability_Frame.wav", "Resources\\SoundResources\\EffectVoice");
}

void FrameBreathEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });


	if (EffectDir.X < 0.0f)
	{
		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("랜더러가 널일 이유가 없어..");
			return;
		}

		MainRenderer->ChangeAnimation("Left_FireEffect");
	}
	else if (EffectDir.X >= 0.0f)
	{
		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("랜더러가 널일 이유가 없어..");
			return;
		}

		MainRenderer->ChangeAnimation("Right_FireEffect");
	}

	// 불꽃 방사를 위해 랜덤의 방향값 지정
	if (EffectDir.X < 0.0f)
	{
		float Degree = GameEngineRandom::MainRandom.RandomFloat(165.0f, 195.0f );
		EffectDir = float4::GetUnitVectorFromDeg(Degree);
	}
	else if (EffectDir.X > 0.0f)
	{
		float Degree = GameEngineRandom::MainRandom.RandomFloat(-15.0f, 15.0f);
		EffectDir = float4::GetUnitVectorFromDeg(Degree);
	}


	// 사운드 재생
	GameEngineSound::SoundPlay("Ability_Frame.wav");
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void FrameBreathEffect::Update(float _Delta)
{
	if (true == IsPassGround)
	{
		GroundPassUpdate(_Delta);
	}
	else if (false == IsPassGround)
	{
		GroundNotPassUpdate(_Delta);
	}
}


void FrameBreathEffect::GroundPassUpdate(float _Delta)
{
	if (GetLiveTime() > EffectDuration)
	{
		Death();
		EffectPointerRelease();
		return;
	}


	if (true == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::MonsterBody);

		int Damage = GameEngineRandom::MainRandom.RandomInt(1, 3);
		AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage);
	}
	else if (false == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::PlayerBody);
	}


	float EffectSpeed = EffectDistance / EffectDuration;
	AddPos(EffectDir * EffectSpeed * _Delta);
}


void FrameBreathEffect::GroundNotPassUpdate(float _Delta)
{

}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void FrameBreathEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}
