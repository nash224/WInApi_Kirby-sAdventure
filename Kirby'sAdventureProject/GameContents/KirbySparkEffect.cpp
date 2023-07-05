#include "KirbySparkEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>



KirbySparkEffect::KirbySparkEffect()
{
}

KirbySparkEffect::~KirbySparkEffect()
{
}


void KirbySparkEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("KirbySparkEffect_1x3_144x48.bmp", "Resources\\Effect\\KirbyBaseEffect", 3, 1);

	MainRenderer->CreateAnimation("KirbySparkEffect", "KirbySparkEffect_1x3_144x48.bmp", 0, 2, ChangeFrameInter, false);
	MainRenderer->ChangeAnimation("KirbySparkEffect");


	// 사운드 로드
	GlobalContents::SoundFileLoad("Ability_Spark1.wav", "Resources\\SoundResources\\EffectVoice");
}

void KirbySparkEffect::init(const float4& _Pos, const float4& _MaterScale)
{
	float4 StartPos = float4::ZERO;

	float RandomDeg = GameEngineRandom::MainRandom.RandomFloat(0.0f, 360.0f);
	EffectDir = float4::GetUnitVectorFromDeg(RandomDeg);
	StartPos = EffectDir * StartDistance;

	SetPos(_Pos + float4{ 0.0f , -_MaterScale.Half().Y } + StartPos);

	
	GameEngineSound::SoundPlay("Ability_Spark1.wav");

}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void KirbySparkEffect::Update(float _Delta)
{
	AddPos(EffectDir * EffectSpeed * _Delta);

	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		EffectPointerRelease();
		return;
	}
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void KirbySparkEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}