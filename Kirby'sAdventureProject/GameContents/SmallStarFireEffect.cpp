#include "SmallStarFireEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"
#include "ActorUtils.h"
#include "ObejctDisapearingEffect.h"
#include "Boss.h"



SmallStarFireEffect::SmallStarFireEffect()
{
}

SmallStarFireEffect::~SmallStarFireEffect()
{
}


void SmallStarFireEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GlobalContents::SpriteFileLoad("SpitStar_1x4_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 4, 1);

	MainRenderer->CreateAnimation("SmallStarFire", "SpitStar_1x4_16x16.bmp", 0, 3, FramesInter);
	MainRenderer->ChangeAnimation("SmallStarFire");

	Scale = ResourcesManager::GetInst().FindSprite("SpitStar_1x4_16x16.bmp")->GetSprite(0).RenderScale;
	SetCheckPoint(Scale);
}

void SmallStarFireEffect::init(const std::string& _FileName, const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });
	SetGroundTexture(_FileName);
}


void SmallStarFireEffect::Update(float _Delta)
{
	// 앞쪽이 벽이면
	if (true == CheckCenterPoint())
	{
		// 별이 사라지는 모션
		ObejctDisapearingEffect* ObejctDisapearing = GetLevel()->CreateActor<ObejctDisapearingEffect>(UpdateOrder::Ability);
		if (nullptr == ObejctDisapearing)
		{
			MsgBoxAssert("액터가 Null 입니다.");
			return;
		}

		ObejctDisapearing->init(GetPos());


		// 죽고 정리
		Death();
		EffectPointerRelease();

		return;
	}

	// 카메라 밖으로 넘어가면 
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetCameraPos();
	if (CameraPos.X > GetPos().X && GetPos().X > CameraPos.X + WinScale.X)
	{
		// 죽고 정리
		Death();
		EffectPointerRelease();

		return;
	}



	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);

	if (false == IsAbilityCollisionCheck)
	{
		int Damage = GameEngineRandom::MainRandom.RandomInt(3, 4);
		AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage, true);
	}

	AddPos(EffectDir * SMALLSTARFIREEFFECTSPEED * _Delta);
}



void SmallStarFireEffect::SkillDeathEffect()
{
	// 별이 사라지는 모션
	ObejctDisapearingEffect* ObejctDisapearing = GetLevel()->CreateActor<ObejctDisapearingEffect>(UpdateOrder::Ability);
	if (nullptr == ObejctDisapearing)
	{
		MsgBoxAssert("액터가 Null 입니다.");
		return;
	}

	ObejctDisapearing->init(GetPos());

}




void SmallStarFireEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}