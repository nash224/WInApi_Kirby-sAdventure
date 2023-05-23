#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourceManager.h>




void Kirby::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Kirby::WalkStart()
{
	DirCheck();
	IsAbleJump = true;
	ChangeAnimationState("Walk");
}

void Kirby::RunStart()
{
	DirCheck();
	ChangeAnimationState("Run");
}

void Kirby::TurnStart()
{
	ChangeAnimationState("Turn");
}

void Kirby::JumpStart()
{
	DirCheck();
	IsAbleJump = false;
	ChangeAnimationState("Jump");
}

void Kirby::AerialMotionStart()
{
	DirCheck();
	ChangeAnimationState("AerialMotion");
}

void Kirby::FallStart()
{
	DirCheck();
	FallTime = 0.0f;
	ChangeAnimationState("Fall");
}

void Kirby::LandingStart()
{
	IsAbleJump = true;
	ChangeAnimationState("Landing");
}

void Kirby::LowerPostureStart()
{
	ChangeAnimationState("LowerPosture");
}

void Kirby::LowerAttackStart()
{
	ChangeAnimationState("LowerAttack");
}



// =============================================//

void Kirby::IdleUpdate(float _Delta)
{
	MoveUpdate(_Delta);

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
	else if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	else if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) &&
		false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Walk);
	}



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
	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}
	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);
			AddPos(float4::UP * 3);
		}

		GravityReset();
	}


	float Speed = 600.0f;
	float4 CheckPos = float4::ZERO;

	if (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D'))
	{
		//MovePos = { 0.0f, MovePos.Y };
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		CheckPos = { -18.0f , -30.0f };
		//MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		CheckPos = { 18.0f , -30.0f };
		//MovePos = { Speed * _Delta, 0.0f };
	}

	MoveUpdate(_Delta);

	if (CurrentSpeed == 0.0f)
	{
		ChangeState(KirbyState::Idle);
	}


	//unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
	//if (Color == RGB(255,255,255))
	//{
	//	AddPos(MovePos);
	//}



}

// RunUpdate중에 A와 D가 프레임사이로 연속적으로 입력됐을 경우
// 좌우 애니메이션이 전환되지 않는 버그가 있음
void Kirby::RunUpdate(float _Delta)
{

}


void Kirby::TurnUpdate(float _Delta)
{

}

void Kirby::JumpUpdate(float _Delta)
{

	float4 MovePos = float4::ZERO;
	float JumpPower = 600.0f;


	if (GameEngineInput::IsPress('X') && 3.0f >= GameEngineInput::GetPressTime('X'))
	{
		IsAbleJump = true;
		MovePos = { 0.0f, - JumpPower * _Delta };
	}


	AddPos(MovePos);

	if (false == GetGroundState() && false == IsAbleJump)
	{
		Gravity(_Delta);
	}

	if (true == GetGroundState() && false == IsAbleJump)
	{
		ChangeState(KirbyState::Idle);
	}


}


void Kirby::AerialMotionUpdate(float _Delta)
{

}

void Kirby::FallUpdate(float _Delta)
{
	FallTime += _Delta;
	MoveUpdate(_Delta);
	Gravity(_Delta);

	if (true == GetGroundState())
	{
		ChangeState(KirbyState::Landing);
		return;
	}
}


void Kirby::LandingUpdate(float _Delta)
{
	MoveUpdate(_Delta);

	if (0.0f == CurrentSpeed)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	else if (0.0f != CurrentSpeed)
	{
		ChangeState(KirbyState::Walk);
		return;
	}
}

void Kirby::LowerPostureUpdate(float _Delta)
{
	MoveUpdate(_Delta);

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


// ============================================








//Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
//NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
//NewRazer->SetDir(float4::RIGHT);
//NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
//NewRazer->SetSpeed(300.0f);