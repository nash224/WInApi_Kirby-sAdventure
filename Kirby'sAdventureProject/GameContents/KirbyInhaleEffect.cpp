#include "KirbyInhaleEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameENgineCore/GameEngineLevel.h>

#include "GlobalContents.h"
#include "CommonSkillEffect.h"

KirbyInhaleEffect::KirbyInhaleEffect()
{
}

KirbyInhaleEffect::~KirbyInhaleEffect()
{
}



void KirbyInhaleEffect::Start()
{
}


void KirbyInhaleEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _EffectDir)
{
	SetPos(_Pos + float4{ 0.0f , -_MaterScale.Half().Y });

	EffectDir = _EffectDir;
}




void KirbyInhaleEffect::Update(float _Delta)
{
	if (GetLiveTime() > 10.0f)
	{
		Death();
		EffectPointerRelease();
	}
}



void KirbyInhaleEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}