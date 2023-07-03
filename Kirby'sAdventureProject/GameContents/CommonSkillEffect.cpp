#include "CommonSkillEffect.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineRandom.h>
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
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}
}

void CommonSkillEffect::init(const std::string& _Path, const std::string& _FileName, const float4& _Pos)
{
	GlobalContents::TextureFileLoad(_FileName, _Path);
	MainRenderer->SetTexture(_FileName);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	SetPos(_Pos);
}

void CommonSkillEffect::Update(float _Delta)
{
	if (GetLiveTime() > ExpressionTime)
	{
		Death();
		EffectPointerRelease();
		return;
	}


	if (true == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::MonsterBody);

		int Damage = GameEngineRandom::MainRandom.RandomInt(1, 4);
		AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage);
	}
	else if (false == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::PlayerBody);
	}
}




void CommonSkillEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}