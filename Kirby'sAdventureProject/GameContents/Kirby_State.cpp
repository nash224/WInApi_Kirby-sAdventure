#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>



void Kirby::AccelerateDownStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("AccelerateDown");
}

void Kirby::BounceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Bounce");
}

void Kirby::LandingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Landing");
}

void Kirby::LowerPostureStart()
{
	StateTime = 0.0f;
	BodyState = KirbyBodyState::Lower;
	ChangeAnimationState("LowerPosture");
}

void Kirby::LowerAttackStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("LowerAttack");
}

void Kirby::HittheWallStart()
{
	StateTime = 0.0f;
	CurrentSpeed = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("HittheWall");
}

void Kirby::HittheCeilingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	ChangeAnimationState("HittheCeiling");
}

void Kirby::TakeOffStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BodyState = KirbyBodyState::Fat;
	SetAirResistance(0.4f);
	ChangeAnimationState("TakeOff");
}

void Kirby::FlyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Fly");
}


// =============================================//

void Kirby::IdleStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Idle");
}

void Kirby::IdleUpdate(float _Delta)
{

	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::LowerPosture);
		return;
	}
	if (true == (GameEngineInput::IsDown('Z')))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}
	if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}
	if (true == CheckLeftWall() && GameEngineInput::IsPress('A') && CurrentSpeed == 0.0f)
	{
		return;
	}
	if (true == CheckRightWall() && GameEngineInput::IsPress('D') && CurrentSpeed == 0.0f)
	{
		return;
	}
	if ((true == CheckLeftWall() || true == CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
		return;
	}
	if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Walk);
		return;
	}

	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta); 
}


void Kirby::WalkStart()
{
	StateTime = 0.0f;
	DirCheck();
	ChangeAnimationState("Walk");
}

void Kirby::WalkUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::LowerPosture);
		return;
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (CurrentSpeed < WALKMAXSPEED * 0.2f * _Delta && true == GameEngineInput::IsDown('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Run);
		return;
	}

	if (CurrentSpeed > WALKMAXSPEED * 0.2f * _Delta && true == GameEngineInput::IsDown('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if ((true == CheckLeftWall() || true == CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
		return;
	}

	if (CurrentSpeed == 0.0f && 
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
			(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	
	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}


void Kirby::RunStart()
{
	StateTime = 0.0f;
	DirCheck();
	ChangeAnimationState("Run");
}

void Kirby::RunUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::LowerPosture);
		return;
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if ((true == CheckLeftWall() || true == CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
		return;
	}

	if (CurrentSpeed == 0.0f &&
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
			(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Idle);
		return;
	}


	MoveHorizontal(RUNSPEED, _Delta);
	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}


void Kirby::TurnStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	if (CurrentSpeed > 0.0f)
	{
		Dir = ActorDir::Right;
	}

	if (CurrentSpeed < 0.0f)
	{
		Dir = ActorDir::Left;
	}

	ChangeAnimationState("Turn");
}

void Kirby::TurnUpdate(float _Delta)
{
	if (CurrentSpeed == 0.0f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == CheckLeftWall() || true == CheckRightWall())
	{
		CurrentSpeed = 0.0f;
		ChangeState(KirbyState::HittheWall);
	}

	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta, BRAKESPEED);
	MoveUpdate(_Delta);
}


void Kirby::JumpStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	DirCheck();
	GravityReset();
	ChangeAnimationState("Jump");
}

void Kirby::JumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (true == GameEngineInput::IsFree('X'))
	{
		IsChangeState = true;
	}

	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (IsChangeState = true && 0.0f < GetGravityVector().Y)
	{
		ChangeState(KirbyState::AerialMotion);
		return;
	}

	if (true == CeilingCheck())
	{
		ChangeState(KirbyState::HittheCeiling);
		return;
	}

	if (true == GameEngineInput::IsUp('X'))
	{
		AbleJump = false;
	}

	if (true == GameEngineInput::IsPress('X') && StateTime < 0.4f && true == AbleJump)
	{
		SetGravityVector(float4::UP * (JUMPPOWER * _Delta));
	}


	BlockedByCeiling();
	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();


	ChangeAnimationState("Jump");

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}


void Kirby::AerialMotionStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	DirCheck();
	ChangeAnimationState("AerialMotion");
}

void Kirby::AerialMotionUpdate(float _Delta)
{
	StateTime += _Delta;

	bool LeftCheck = MainRenderer->FindAnimation("Normal_Left_AerialMotion")->IsEnd;
	bool RightCheck = MainRenderer->FindAnimation("Normal_Right_AerialMotion")->IsEnd;

	if (LeftCheck || RightCheck)
	{
		IsChangeState = true;
		MainRenderer->FindAnimation("Normal_Left_AerialMotion")->IsEnd = false;
		MainRenderer->FindAnimation("Normal_Right_AerialMotion")->IsEnd = false;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (IsChangeState == true)
	{
		ChangeState(KirbyState::Fall);
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GetGroundState())
	{
		ChangeState(KirbyState::Landing);
	}

	if (true == CheckLeftWallBasedSpeed() && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
	}
	if (true == CheckRightWallBasedSpeed() && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
	}



	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}


void Kirby::FallStart()
{
	StateTime = 0.0f;
	FallDistance = 0.0f;
	ChangeAnimationState("Fall");
}

void Kirby::FallUpdate(float _Delta)
{
	StateTime += _Delta;
	FallDistance += GetGravityVector().Y;

	if (FallDistance > 150.0f)
	{
		ChangeState(KirbyState::AccelerateDown);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GetGroundState())
	{
		ChangeState(KirbyState::Landing);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		ChangeState(KirbyState::HittheWall);
	}
	if (true == CheckRightWallBasedSpeed())
	{
		ChangeState(KirbyState::HittheWall);
	}


	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();
	ChangeAnimationState("Fall");

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}

void Kirby::AccelerateDownUpdate(float _Delta)
{
	BlockedByWall();

	if (true == GetGroundState())
	{
		SetGravityVector(float4::UP * GravityMaxVector * _Delta);
		ChangeState(KirbyState::Bounce);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	BlockedByGround();
	BlockedByWall();

	MoveUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}

void Kirby::BounceUpdate(float _Delta)
{
	StateTime += _Delta;

	BlockedByWall();

	if (StateTime >= 0.2f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Landing);
		return;
	}


	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();

	MoveUpdate(_Delta);
	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}


void Kirby::LandingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= HITTHEMAPTIME)
	{
		IsChangeState = true;
	}

	if (0.0f == CurrentSpeed && true == IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	else if (0.0f != CurrentSpeed && true == IsChangeState)
	{
		ChangeState(KirbyState::Walk);
		return;
	}



	BlockedByWall();
	BlockedByGround();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}

void Kirby::LowerPostureUpdate(float _Delta)
{

	if (false == GetGroundState())
	{
		BodyState = KirbyBodyState::Little;
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GetGroundState() && (GameEngineInput::IsDown('Z') || GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::LowerAttack);
		return;
	}
	if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f == CurrentSpeed)
	{
		BodyState = KirbyBodyState::Little;
		ChangeState(KirbyState::Idle);
		return;
	}
	if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f != CurrentSpeed)
	{
		BodyState = KirbyBodyState::Little;
		ChangeState(KirbyState::Walk);
		return;
	}


	BlockedByWall();
	BlockedByGround();

	DecelerationUpdate(_Delta, DECELERATIONSPEED);
	MoveUpdate(_Delta);
}

void Kirby::LowerAttackUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime < 0.4f)
	{
		if (Dir == ActorDir::Left)
		{
			CurrentSpeed = -RUNMAXSPEED * _Delta;
		}

		if (Dir == ActorDir::Right)
		{
			CurrentSpeed = RUNMAXSPEED * _Delta;
		}
	}
	
	if (true == CheckLeftWall() || true == CheckRightWall())
	{
		BodyState = KirbyBodyState::Little;
		ChangeState(KirbyState::HittheWall);
		return;
	}

	if (false == GetGroundState())
	{
		BodyState = KirbyBodyState::Little;
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == GetGroundState() && 0.0f == CurrentSpeed)
	{
		BodyState = KirbyBodyState::Little;
		ChangeState(KirbyState::Idle);
		return;
	}


	BlockedByWall();
	BlockedByGround();

	DecelerationUpdate(_Delta, DECELERATIONSPEED);
	MoveUpdate(_Delta);
}

void Kirby::HittheWallUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HITTHEMAPTIME)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	else if (false == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Fall);
		return;
	}

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate();
	}
}


void Kirby::HittheCeilingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (HITTHEMAPTIME <= StateTime)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(KirbyState::Fall);
		return;
	}

	BlockedByCeiling();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate();
	}
}

void Kirby::TakeOffUpdate(float _Delta)
{
	bool LeftCheck = MainRenderer->FindAnimation("Normal_Left_TakeOff")->IsEnd;
	bool RightCheck = MainRenderer->FindAnimation("Normal_Right_TakeOff")->IsEnd;
	if (LeftCheck || RightCheck)
	{
		IsChangeState = true;
		MainRenderer->FindAnimation("Normal_Left_TakeOff")->IsEnd = false;
		MainRenderer->FindAnimation("Normal_Right_TakeOff")->IsEnd = false;
	}

	if (true == IsChangeState)
	{
		ChangeState(KirbyState::Fly);
		return;
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		SetGravityVector(float4::UP * (FLYPOWER * _Delta));
	}



	BlockedByGround();
	BlockedByCeiling();
	MoveHorizontal(FLYSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}

void Kirby::FlyUpdate(float _Delta)
{
	StateTime += _Delta;

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::ExhaleAttack);
		return;
	}


	if (true == GameEngineInput::IsPress('W') || true == GameEngineInput::IsPress('X'))
	{
		MainRenderer->FindAnimation("Normal_Left_Fly")->Inters = { 0.1f, 0.1f };
		MainRenderer->FindAnimation("Normal_Right_Fly")->Inters = { 0.1f, 0.1f };
		SetGravityVector(float4::UP * (FLYPOWER * _Delta));
	}

	if (false == GameEngineInput::IsPress('W') && false == GameEngineInput::IsPress('X'))
	{
		MainRenderer->FindAnimation("Normal_Left_Fly")->Inters = { 0.2f, 0.2f };
		MainRenderer->FindAnimation("Normal_Right_Fly")->Inters = { 0.2f, 0.2f };
	}

	if (true == CeilingCheck())
	{
		SetGravityVector(float4::ZERO);
	}

	if (true == IsSolidGround() && false == (GameEngineInput::IsPress('W') || GameEngineInput::IsPress('X')))
	{
		SetGravityVector(float4::ZERO);
	}

	if (true == IsPassableGround() && GetGravityVector().Y >= 0.0f && false == (GameEngineInput::IsPress('W') || GameEngineInput::IsPress('X')))
	{
		SetGravityVector(float4::ZERO);
	}


	BlockedByGround();
	BlockedByCeiling();
	MoveHorizontal(FLYSPEED, _Delta);
	BlockedByWall();

	ChangeAnimationState("Fly");

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	if (false == GetGroundState() || (true == GameEngineInput::IsPress('W') || true == GameEngineInput::IsPress('X')))
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate();
}

void Kirby::ExhaleAttackStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BodyState = KirbyBodyState::Little;
	ChangeAnimationState("ExhaleAttack");
}

void Kirby::ExhaleAttackUpdate(float _Delta)
{
	StateTime += _Delta;

	IsChangeState = CheckEndAnimation(MainRenderer, CurMode + "_Left_ExhaleAttack", CurMode + "_Right_ExhaleAttack");

	if (true == IsChangeState && false == GetGroundState())
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == IsChangeState && CurrentSpeed == 0.0f && true == GetGroundState())
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Idle);
		return;
	}

	if (true == IsChangeState && CurrentSpeed != 0.0f && true == GetGroundState())
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Walk);
		return;
	}


	BlockedByGround();
	MoveHorizontal(FLYSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate();
	}
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
	StateTime += _Delta;

	IsChangeState = CheckEndAnimation(MainRenderer, CurMode + "_Left_UseSpecialAbility", CurMode + "_Right_UseSpecialAbility");

	if (true == IsChangeState)
	{
		IstriggerOn = true;
	}

	if (true == IstriggerOn)
	{
		Duration += _Delta;
	}

	if (Duration > 0.2f && true == GameEngineInput::IsFree('Z'))
	{
		ChangeState(KirbyState::ReleaseAbility);
		return;
	}

	if (KirbyMode::Normal == Mode && true == swallowedObject)
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	UseAbility();

	BlockedByWall();
	BlockedByGround();

	DecelerationUpdate(_Delta, DECELERATIONSPEED);
	MoveUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate();
	}
}


void Kirby::ReleaseAbilityStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("ReleaseAbility");
}

void Kirby::ReleaseAbilityUpdate(float _Delta)
{
	IsChangeState = CheckEndAnimation(MainRenderer, CurMode + "_Left_ReleaseAbility", CurMode + "_Right_ReleaseAbility");

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

	DecelerationUpdate(_Delta, DECELERATIONSPEED);
	MoveUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate();
	}
}


void Kirby::GetAbilityStart()
{

}

void Kirby::GetAbilityUpdate(float _Delta)
{

}


// ============================================




void Kirby::UseAbility()
{
	switch (Mode)
	{
	case KirbyMode::Normal:
		InhaleAbility();
		break;
	case KirbyMode::Spark:
		SparkAbility();
		break;
	case KirbyMode::Max:
		break;
	default:
		break;
	}
}

void Kirby::InhaleAbility()
{
	if (StateTime > 1.0f)
	{
		swallowedObject = true;
		Star = AbilityStar::None;
		StarPower = 1;
	}
}


void Kirby::SparkAbility()
{

}



//Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
//NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
//NewRazer->SetDir(float4::RIGHT);
//NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
//NewRazer->SetSpeed(300.0f);