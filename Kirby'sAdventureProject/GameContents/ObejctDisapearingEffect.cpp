#include "ObejctDisapearingEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
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
	GlobalContents::SpriteFileLoad("DispareringEffect_1x3_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 3, 1);
	MainRenderer->CreateAnimation("ObejctDisapearing", "DispareringEffect_1x3_16x16.bmp" , 0, 2, ChangeEffectFramesInter, false);

	MainRenderer->ChangeAnimation("ObejctDisapearing");
}

void ObejctDisapearingEffect::init(const float4& _Pos)
{
	SetPos(_Pos);
}

void ObejctDisapearingEffect::Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
	}
}
