#include "DustEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>



DustEffect::DustEffect()
{
}

DustEffect::~DustEffect()
{
}


void DustEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	GlobalContents::SpriteFileLoad("Smoke_1x2_8x10.bmp", "Resources\\Effect\\KirbyBaseEffect", 2, 1);

	MainRenderer->CreateAnimation("DustEffectAnimation", "Smoke_1x2_8x10.bmp", 0, 1, FrameChangeTime, false);
	MainRenderer->ChangeAnimation("DustEffectAnimation");
}


void DustEffect::init(const float4& _MasterPos, const float4& _MasterScale, const float4& _Dir, int _ItersCount/* = 1*/)
{
	SetPos(_MasterPos + _Dir * (_MasterScale.Half().X + 12.0f));

	EffectDir = _Dir;

	// ���� ���� ���� ������ ������
	if (EffectDir.X > 0.0f)
	{
		EffectDir = float4{ 0.8f, -0.2f };
	}
	else
	{
		EffectDir = float4{ -0.8f, -0.2f };
	}
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void DustEffect::Update(float _Delta)
{
	AddPos(EffectDir * EffectSpeed * _Delta);

	if (MainRenderer->IsAnimationEnd())
	{
		Death();
		EffectPointerRelease();
		return;
	}
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void DustEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}