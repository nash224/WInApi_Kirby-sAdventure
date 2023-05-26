#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>




void Kirby::IdleStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Idle");
}

void Kirby::WalkStart()
{
	StateTime = 0.0f;
	DirCheck();
	ChangeAnimationState("Walk");
}

void Kirby::RunStart()
{
	StateTime = 0.0f;
	DirCheck();
	ChangeAnimationState("Run");
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

void Kirby::JumpStart()
{
	StateTime = 0.0f;
	DirCheck();
	GravityReset();
	ChangeAnimationState("Jump");
}

void Kirby::AerialMotionStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	DirCheck();
	ChangeAnimationState("AerialMotion");
}

void Kirby::FallStart()
{
	StateTime = 0.0f;
	FallDistance = 0.0f;
	ChangeAnimationState("Fall");
}


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
	SetGravityVector(float4{ 0.0f, 0.0f });
	ChangeAnimationState("HittheCeiling");
}



// =============================================//

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
		// 스킬 미구현
		return;
	}
	if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		// Fly
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


	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta); 

	//	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);

	//	while (CheckColor != RGB(255, 255, 255))
	//	{
	//		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);
	//		AddPos(float4::UP*3);
	//	}

	//	GravityReset();
	//}

}


void Kirby::WalkUpdate(float _Delta)
{

	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
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

	

	MoveHorizontal(WALKSPEED, _Delta);
	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}

void Kirby::RunUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Jump);
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

	if (CurrentSpeed < 0.0f)
	{
		CurrentSpeed += 2.0f * _Delta;

		if (CurrentSpeed > 0.0f)
		{
			CurrentSpeed = 0.0f;
		}
	}
	else if (CurrentSpeed > 0.0f)
	{
		CurrentSpeed -= 2.0f * _Delta;

		if (CurrentSpeed < 0.0f)
		{
			CurrentSpeed = 0.0f;
		}
	}

	DecelerationUpdate(_Delta, BRAKESPEED);
	MoveUpdate(_Delta);
}

void Kirby::JumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (true == GameEngineInput::IsFree('X'))
	{
		IsChangeState = true;
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


	if (true == GameEngineInput::IsPress('X') && StateTime < 0.4f)
	{
		SetGravityVector(float4::UP * (JUMPPOWER * _Delta));
	}

	MoveHorizontal(WALKSPEED, _Delta);

	BlockedByWall();

	ChangeAnimationState("Jump");

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
	Gravity(_Delta);
}


void Kirby::AerialMotionUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 0.3f)
	{
		ChangeState(KirbyState::Fall);
	}

	if (true == GetGroundState())
	{
		ChangeState(KirbyState::Landing);
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		ChangeState(KirbyState::HittheWall);
	}
	if (true == CheckRightWallBasedSpeed())
	{
		ChangeState(KirbyState::HittheWall);
	}



	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();
	BlockedByGround();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
	Gravity(_Delta);
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


	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();
	BlockedByGround();

	ChangeAnimationState("Fall");

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
	Gravity(_Delta);
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

	BlockedByGround();

	MoveUpdate(_Delta);
	Gravity(_Delta);
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

	MoveUpdate(_Delta);
	Gravity(_Delta);
}


void Kirby::LandingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= HITTHEMAPTime)
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
		ChangeState(KirbyState::Idle);
		return;
	}
	if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f != CurrentSpeed)
	{
		ChangeState(KirbyState::Walk);
		return;
	}


	BlockedByWall();
	BlockedByGround();

	DecelerationUpdate(_Delta);
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
		ChangeState(KirbyState::HittheWall);
		return;
	}

	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == GetGroundState() && 0.0f == CurrentSpeed)
	{
		ChangeState(KirbyState::Idle);
		return;
	}


	BlockedByWall();
	BlockedByGround();

	MoveUpdate(_Delta);
	DecelerationUpdate(_Delta);
}

void Kirby::HittheWallUpdate(float _Delta)
{
	StateTime += _Delta;

	if (HITTHEMAPTime <= StateTime)
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
	}
}


void Kirby::HittheCeilingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (HITTHEMAPTime <= StateTime)
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
	}
}


// ============================================








//Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
//NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
//NewRazer->SetDir(float4::RIGHT);
//NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
//NewRazer->SetSpeed(300.0f);