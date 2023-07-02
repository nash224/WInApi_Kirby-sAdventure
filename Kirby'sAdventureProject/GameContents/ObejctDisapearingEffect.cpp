#include "ObejctDisapearingEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"

ObejctDisapearingEffect::ObejctDisapearingEffect()
{
}

ObejctDisapearingEffect::~ObejctDisapearingEffect()
{
}


void ObejctDisapearingEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("DispareringEffect_1x3_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 3, 1);

	MainRenderer->CreateAnimation("ObejctDisapearing", "DispareringEffect_1x3_16x16.bmp" , 0, 2, ChangeEffectFramesInter, false);
	MainRenderer->ChangeAnimation("ObejctDisapearing");


	// 사운드
	GlobalContents::SoundFileLoad("Effect_DisapearSound.wav", "Resources\\SoundResources\\EffectVoice");
}

void ObejctDisapearingEffect::init(const float4& _Pos, bool _Sound /*= true*/)
{
	SetPos(_Pos);

	if (true == _Sound)
	{
		// 사운드 재생
		GameEngineSound::SoundPlay("Effect_DisapearSound.wav");
	}
}

void ObejctDisapearingEffect::Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		EffectPointerRelease();
		return;
	}
}


void ObejctDisapearingEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}