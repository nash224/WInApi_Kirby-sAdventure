#include "MoveStarEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"


MoveStarEffect::MoveStarEffect()
{
}

MoveStarEffect::~MoveStarEffect()
{
}


// �ε� �� �ؽ�ó ����
void MoveStarEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	GlobalContents::TextureFileLoad("StarEffect_1x1_24x24.bmp", "Resources\\Effect\\SkillEffect");

	MainRenderer->SetTexture("StarEffect_1x1_24x24.bmp");
}


// ���� �� ��ġ ����
void MoveStarEffect::init(const float4& _Pos, const float4& _Dir)
{
	EffectDir = _Dir;
	EffectDir.Normalize();

	SetPos(_Pos);
}

void MoveStarEffect::SetSpeedAndDuration(float _Speed, float _Duration)
{
	StarEffectSpeed = _Speed;
	StarEffectMoveDuration = _Duration;
}


// ������ ������ �����̴� ����
void MoveStarEffect::Update(float _Delta)
{
	AddPos(EffectDir * StarEffectSpeed * _Delta);

	if (GetLiveTime() > StarEffectMoveDuration)
	{
		Death();
		EffectPointerRelease();
	}
}


void MoveStarEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}