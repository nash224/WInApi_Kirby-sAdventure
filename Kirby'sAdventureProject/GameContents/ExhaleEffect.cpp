#include "ExhaleEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>


ExhaleEffect::ExhaleEffect()
{
}

ExhaleEffect::~ExhaleEffect()
{
}


void ExhaleEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::TextureFileLoad("Left_ExhaleEffect_1x1_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect");
	GlobalContents::TextureFileLoad("Right_ExhaleEffect_1x1_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect");

	MainRenderer->SetTexture("Left_ExhaleEffect_1x1_16x16.bmp");

	Scale = float4{ 48.0f , 48.0f };
	MainRenderer->SetRenderScale(Scale);
}


void ExhaleEffect::init(const float4& _MasterPos, const float4& _MasterScale, const float4& _EffectDir)
{
	EffectDir = _EffectDir;



	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	if (_EffectDir.X > 0.0f)
	{
		MainRenderer->SetTexture("Right_ExhaleEffect_1x1_16x16.bmp");
	}
	else
	{
		MainRenderer->SetTexture("Left_ExhaleEffect_1x1_16x16.bmp");
	}

	SetPos(_MasterPos + float4{ 0.0f , -_MasterScale.Half().Y } + _EffectDir * (24.0f + Scale.Half().X));
	
	if (EffectDir.X < 0.0f)
	{
		CurrentSpeed = -EffectDistance;
	}
	else if (EffectDir.X > 0.0f)
	{
		CurrentSpeed = EffectDistance;
	}
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void ExhaleEffect::Update(float _Delta)
{
	if (GetLiveTime() < ForwardTime)
	{
		float DecelerationSpeed = EffectDistance / ForwardTime;
		DecelerationUpdate(_Delta, DecelerationSpeed);
		HorizontalUpdate(_Delta);
	}

	if (GetLiveTime() > EffectTime)
	{
		Death();
		EffectPointerRelease();
		return;
	}

	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void ExhaleEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}