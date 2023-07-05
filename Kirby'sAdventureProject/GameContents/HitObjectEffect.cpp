#include "HitObjectEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>




HitObjectEffect::HitObjectEffect()
{
}

HitObjectEffect::~HitObjectEffect()
{
}


void HitObjectEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::TextureFileLoad("Left_StarEffect_1x1_8x8.bmp", "Resources\\Effect\\KirbyBaseEffect");


	MainRenderer->SetTexture("Left_StarEffect_1x1_8x8.bmp");

	Scale = float4{ 16.0f , 16.0f };
	MainRenderer->SetRenderScale(Scale);


}


void HitObjectEffect::init(const float4& _MasterPos, const float4& _Pos)
{
	// 45도 각도로 8방향이 랜덤으로 결정
	int DirNumber = GameEngineRandom::MainRandom.RandomInt(0, 7);
	switch (DirNumber)
	{
	case 0:
		EffectDir = float4{ 0.0f , -UNIT };
		break;
	case 1:
		EffectDir = float4{ UNIT , -UNIT };
		break;
	case 2:
		EffectDir = float4{ UNIT , 0.0f };
		break;
	case 3:
		EffectDir = float4{ UNIT , UNIT };
		break;
	case 4:
		EffectDir = float4{ 0.0f , UNIT };
		break;
	case 5:
		EffectDir = float4{ -UNIT , UNIT };
		break;
	case 6:
		EffectDir = float4{ -UNIT , 0.0f };
		break;
	case 7:
		EffectDir = float4{ -UNIT , -UNIT };
		break;
	default:
		break;
	}

	EffectDir.Normalize();

	SetPos(_MasterPos + _Pos);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void HitObjectEffect::Update(float _Delta)
{
	if (GetLiveTime() < EffectTime)
	{
		AddPos(EffectDir * EffectSpeed * _Delta);
	}


	if (GetLiveTime() > DeathTime)
	{
		Death();
		EffectPointerRelease();
		return;
	}
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void HitObjectEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}