#include "ObejctDisapearingEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>



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
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	GlobalContents::SpriteFileLoad("DispareringEffect_1x3_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 3, 1);

	MainRenderer->CreateAnimation("ObejctDisapearing", "DispareringEffect_1x3_16x16.bmp" , 0, 2, ChangeEffectFramesInter, false);
	MainRenderer->ChangeAnimation("ObejctDisapearing");


	// ����
	GlobalContents::SoundFileLoad("Effect_DisapearSound.wav", "Resources\\SoundResources\\EffectVoice");
}

void ObejctDisapearingEffect::init(const float4& _Pos, bool _Sound /*= true*/)
{
	SetPos(_Pos);

	if (true == _Sound)
	{
		// ���� ���
		GameEngineSound::SoundPlay("Effect_DisapearSound.wav");
	}
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void ObejctDisapearingEffect::Update(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		EffectPointerRelease();
		return;
	}
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void ObejctDisapearingEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}