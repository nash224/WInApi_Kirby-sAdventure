#include "SparkEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>




SparkEffect::SparkEffect()
{
}

SparkEffect::~SparkEffect()
{
}


void SparkEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GameEngineWindowTexture* Texture = 
		GlobalContents::TextureFileLoad("SparkEffect_1x1_16x16.bmp", "Resources\\Effect\\SkillEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	MainRenderer->SetTexture("SparkEffect_1x1_16x16.bmp");

	Scale = Texture->GetScale();


	GlobalContents::SoundFileLoad("Ability_Spark1.wav", "Resources\\SoundResources\\EffectVoice");

}

void SparkEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + _Dir * _MaterScale.Half().Max2D() + float4{ 0.0f , -_MaterScale.Half().Y });

	GameEngineSound::SoundPlay("Ability_Spark1.wav");
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void SparkEffect::Update(float _Delta)
{
	float EffectSpeed = EffectDistance / EffectDurtion;
	CurrentEffectDistance += EffectSpeed * _Delta;

	AddPos(EffectDir * EffectSpeed * _Delta);


	// 일정 범위를 넘어가면 죽어야됨
	if (CurrentEffectDistance > EffectDistance)
	{
		Death();
		EffectPointerRelease();
		return;
	}
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void SparkEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}