#include "CommonSkillEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"

CommonSkillEffect::CommonSkillEffect()
{
}

CommonSkillEffect::~CommonSkillEffect()
{
}


void CommonSkillEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
}

void CommonSkillEffect::init(const std::string& _Path, const std::string& _FileName, const float4& _Pos)
{
	GlobalContents::TextureFileLoad(_FileName, _Path);
	MainRenderer->SetTexture(_FileName);

	SetPos(_Pos);
}

void CommonSkillEffect::Update(float _Delta)
{
	if (GetLiveTime() > ExpressionTime)
	{
		Death();
		EffectPointerRelease();
	}
}
