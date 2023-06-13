#include "Kirby.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "VegetableValleyPlayLevel.h"


void Kirby::DropAbility()
{
	Mode = KirbyMode::Normal;
	ChangeAnimationState(CurState);
}


void Kirby::UseSpecialAbilityStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	UseAbilityStart();
	ChangeAnimationState("UseSpecialAbility");
}

void Kirby::UseSpecialAbilityUpdate(float _Delta)
{
	UseAbilityUpdate(_Delta);
}



void Kirby::ReleaseAbilityStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("ReleaseAbility");
}

void Kirby::ReleaseAbilityUpdate(float _Delta)
{
	IsChangeState = MainRenderer->IsAnimationEnd();

	if (true == IsChangeState && false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == IsChangeState && true == GetGroundState())
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	BlockedByWall();
	BlockedByGround();

	ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void Kirby::GetAbilityStart()
{

}

void Kirby::GetAbilityUpdate(float _Delta)
{

}


void Kirby::UseAbilityStart()
{
	switch (Mode)
	{
	case KirbyMode::Normal:
		InhaleAbilityStart();
		break;
	case KirbyMode::Spark:
		SparkAbilityStart();
		break;
	case KirbyMode::Max:
		break;
	default:
		break;
	}
}

void Kirby::UseAbilityUpdate(float _Delta)
{
	switch (Mode)
	{
	case KirbyMode::Normal:
		InhaleAbilityUpdate(_Delta);
		break;
	case KirbyMode::Spark:
		SparkAbilityUpdate(_Delta);
		break;
	case KirbyMode::Max:
		break;
	default:
		break;
	}
}



void Kirby::InhaleAbilityStart()
{
	Duration = 0.0f;
	swallowedObject = false;
	IstriggerOn = false;
	Star.SwallowedEnemyNumber = 0;
	Star.SwallowedPowerEnemyNumber = 0;

	float4 KirbyDirUnitVector = GetDirUnitVector();
	if (KirbyDirUnitVector.X < 0.0f)
	{
		KirbyDirUnitVector =
			float4{ -(INHALEEFFECTCOLLISIONSCALE + SMALLTYPECOLLISIONSCALE).Half().X, -INHALEEFFECTCOLLISIONSCALE.Half().Y };
	}
	else if (KirbyDirUnitVector.X > 0.0f)
	{
		KirbyDirUnitVector =
			float4{ (INHALEEFFECTCOLLISIONSCALE + LOWERTYPECOLLISIONSCALE).Half().X, -INHALEEFFECTCOLLISIONSCALE.Half().Y };
	}
	InhaleEffectCollision->SetCollisionPos(KirbyDirUnitVector);
	InhaleEffectCollision->On();
	CollisionCheck.reserve(dynamic_cast<VegetableValleyPlayLevel*>(GetLevel())->GetLevelEnemyCount());
}

void Kirby::InhaleAbilityUpdate(float _Delta)
{
	StateTime += _Delta;

	IsChangeState = MainRenderer->IsAnimationEnd();

	if (true == InhaleEffectCollision->Collision(CollisionOrder::MonsterBody, CollisionCheck, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : CollisionCheck)
		{
			AbilityStar EnemyAbility = static_cast<ActorUtils*>(Collision->GetActor())->Ability;

			if (AbilityStar::Max != EnemyAbility)
			{
				++Star.SwallowedEnemyNumber;
			}

			if (AbilityStar::None != EnemyAbility && AbilityStar::Max != EnemyAbility)
			{
				CurrentAbilityStar = EnemyAbility;
				++Star.SwallowedPowerEnemyNumber;
			}
		}
	}
	

	if (true == IsChangeState)
	{
		IstriggerOn = true;
	}

	if (true == IstriggerOn)
	{
		Duration += _Delta;
	}

	if (StateTime > 1.0f)
	{
		swallowedObject = true;
		CurrentAbilityStar = AbilityStar::None;
		CurMode = "Normal";
		StarPower = 1;
	}

	if (KirbyMode::Normal == Mode && true == swallowedObject)
	{
		CollisionCheck.clear();
		InhaleEffectCollision->Off();
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == GameEngineInput::IsFree('Z') && true == IstriggerOn)
	{
		CollisionCheck.clear();
		InhaleEffectCollision->Off();
		ChangeState(KirbyState::ReleaseAbility);
		return;
	}


	BlockedByWall();
	BlockedByGround();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	ContentsActor::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);
}


void Kirby::SparkAbilityStart()
{

}

void Kirby::SparkAbilityUpdate(float _Delta)
{

}