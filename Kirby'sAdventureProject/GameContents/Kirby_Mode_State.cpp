#include "Kirby.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>


void Kirby::DropAbility()
{
	Mode = KirbyMode::Normal;
	ChangeAnimationState(CurState);
}


void Kirby::UseSpecialAbilityStart()
{
	StateTime = 0.0f;
	Duration = 0.0f;
	IsChangeState = false;
	swallowedObject = false;
	IstriggerOn = false;
	ChangeAnimationState("UseSpecialAbility");
}

void Kirby::UseSpecialAbilityUpdate(float _Delta)
{
	UseAbility(_Delta);
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


void Kirby::UseAbility(float _Delta)
{
	switch (Mode)
	{
	case KirbyMode::Normal:
		InhaleAbility(_Delta);
		break;
	case KirbyMode::Spark:
		SparkAbility(_Delta);
		break;
	case KirbyMode::Max:
		break;
	default:
		break;
	}
}

void Kirby::InhaleAbility(float _Delta)
{
	StateTime += _Delta;

	IsChangeState = MainRenderer->IsAnimationEnd();
	

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
		Star = AbilityStar::None;
		CurMode = "Normal";
		StarPower = 1;
	}

	if (KirbyMode::Normal == Mode && true == swallowedObject)
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == GameEngineInput::IsFree('Z') && true == IstriggerOn)
	{
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


void Kirby::SparkAbility(float _Delta)
{

}