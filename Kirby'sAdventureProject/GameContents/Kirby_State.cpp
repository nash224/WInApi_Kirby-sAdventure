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
	IsAbleJump = true;
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
	IsAbleJump = false;
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
	if (true == CheckLeftWall())
	{
		int a = 0;
	}


	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}
	else if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::LowerPosture);
		return;
	}
	else if (true == (GameEngineInput::IsDown('Z')))
	{
		// 스킬 미구현
		return;
	}
	else if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	else if (true == (GameEngineInput::IsDown('W')))
	{
		// Fly
		return;
	}
	else if (true == CheckLeftWall() && GameEngineInput::IsPress('A') && CurrentSpeed == 0.0f)
	{
		return;
	}
	else if (true == CheckRightWall() && GameEngineInput::IsPress('D') && CurrentSpeed == 0.0f)
	{
		return;
	}
	else if ((true == CheckLeftWall() || true == CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
		return;
	}
	else if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Walk);
		return;
	}

	MoveUpdate(_Delta); 


	// 서있는 위치에 발판이 있는가
	//if(false == GetGroundState())
	//{
	//	Gravity(_Delta);
	//}
	//else
	//{
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

	if (true == CheckLeftWall())
	{
		int a = 0;
	}

	if (true == CheckRightWall())
	{
		int a = 0;
	}

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
		(GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) || 
		(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D')))
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	

	if (true == GameEngineInput::IsPress('A') && false == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Left;
		CurrentSpeed -= 0.8f * _Delta;
	}
	else if (false == GameEngineInput::IsPress('A') && true == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Right;
		CurrentSpeed += 0.8f * _Delta;
	}

	MoveUpdate(_Delta);

	//unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
	//if (Color == RGB(255,255,255))
	//{
	//	AddPos(MovePos);
	//}

	//{
	//	unsigned int CheckColorTop = GetGroundColor(RGB(255, 255, 255), float4::UP * 30.f);
	//	unsigned int CheckColorBottom = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);

	//	while (CheckColorBottom != RGB(255, 255, 255) && CheckColorTop == RGB(255, 255, 255))
	//	{
	//		CheckColorBottom = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);
	//		AddPos(float4::UP * 3);
	//	}

	//	GravityReset();
	//}


}

// RunUpdate중에 A와 D가 프레임사이로 연속적으로 입력됐을 경우
// 좌우 애니메이션이 전환되지 않는 버그가 있음
void Kirby::RunUpdate(float _Delta)
{

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
	else if (false == GetGroundState())
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
		SetGravityVector(float4::UP * (350.0f * _Delta));
	}

	if (true == GameEngineInput::IsPress('A') && false == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Left;
		CurrentSpeed -= 0.8f * _Delta;
	}
	else if (false == GameEngineInput::IsPress('A') && true == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Right;
		CurrentSpeed += 0.8f * _Delta;
	}

	if (true == CheckLeftWall() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWall() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
	}

	ChangeAnimationState("Jump");

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

	if (true == CheckLeftWall() && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
	}
	if (true == CheckRightWall() && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
	}

	if (true == GameEngineInput::IsPress('A') && false == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Left;
		CurrentSpeed -= 0.8f * _Delta;
	}
	else if (false == GameEngineInput::IsPress('A') && true == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Right;
		CurrentSpeed += 0.8f * _Delta;
	}

	if (true == CheckLeftWall() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWall() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
	}


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


	if (true == GameEngineInput::IsPress('A') && false == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Left;
		CurrentSpeed -= 0.8f * _Delta;
	}
	else if (false == GameEngineInput::IsPress('A') && true == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Right;
		CurrentSpeed += 0.8f * _Delta;
	}

	if (true == CheckLeftWall() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWall() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
	}

	ChangeAnimationState("Fall");

	MoveUpdate(_Delta);
	Gravity(_Delta);
}

void Kirby::AccelerateDownUpdate(float _Delta)
{

	if (true == GetGroundState())
	{
		SetGravityVector(float4::UP * GravityMaxVector * _Delta);
		ChangeState(KirbyState::Bounce);
		return;
	}

	//if (true == GameEngineInput::IsPress('A') && false == GameEngineInput::IsPress('D'))
	//{
	//	Dir = ActorDir::Left;
	//	CurrentSpeed -= 0.8f * _Delta;
	//}
	//else if (false == GameEngineInput::IsPress('A') && true == GameEngineInput::IsPress('D'))
	//{
	//	Dir = ActorDir::Right;
	//	CurrentSpeed += 0.8f * _Delta;
	//}

	if (true == CheckLeftWall() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWall() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
	}

	{
		//unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);

		//while (CheckColor != RGB(255, 255, 255))
		//{
		//	CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);
		//	AddPos(float4::UP*3);
		//}
	}

	MoveUpdate(_Delta);
	Gravity(_Delta);
}

void Kirby::BounceUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= 0.2f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Landing);
		return;
	}

	if (true == CheckLeftWall() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWall() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
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

	if (true == CheckLeftWall() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWall() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
	}

	SetDecelerationSpeed(4.0f);

	MoveUpdate(_Delta);

	SetDecelerationSpeed(1.0f);
}

void Kirby::LowerPostureUpdate(float _Delta)
{

	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}
	else if (true == GetGroundState() && (GameEngineInput::IsDown('Z') || GameEngineInput::IsDown('X')))
	{// 수정 예정
		return;
	}
	else if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f == CurrentSpeed)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	else if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f != CurrentSpeed)
	{
		ChangeState(KirbyState::Walk);
		return;
	}

	if ((CheckLeftWall() || CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		CurrentSpeed = 0.0f;
	}

	MoveUpdate(_Delta);
}

void Kirby::LowerAttackUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}
	// 수정
	else if (true == GetGroundState())
	{
		ChangeState(KirbyState::Idle);
		return;
	}
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

	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}

	MoveUpdate(_Delta);
}


// ============================================








//Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
//NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
//NewRazer->SetDir(float4::RIGHT);
//NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
//NewRazer->SetSpeed(300.0f);