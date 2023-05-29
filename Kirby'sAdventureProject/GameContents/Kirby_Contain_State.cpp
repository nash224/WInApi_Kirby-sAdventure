#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>


void Kirby::Contain_StateResourceLoad()
{
	ResourcesManager::GetInst().SpriteFileLoad("Contain_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 2);
	ResourcesManager::GetInst().SpriteFileLoad("Contain_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 2);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Idle", "Contain_Left_Kirby.bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Idle", "Contain_Right_Kirby.bmp", 0, 0, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Walk", "Contain_Left_Kirby.bmp", 1, 4, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Walk", "Contain_Right_Kirby.bmp", 1, 4, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Run", "Contain_Left_Kirby.bmp", 1, 4, 0.1f, true);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Run", "Contain_Right_Kirby.bmp", 1, 4, 0.1f, true);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Turn", "Contain_Left_Kirby.bmp", 1, 1, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Turn", "Contain_Right_Kirby.bmp", 1, 1, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Jump", "Contain_Left_Kirby.bmp", 1, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Jump", "Contain_Right_Kirby.bmp", 1, 2, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Fall", "Contain_Left_Kirby.bmp", 2, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Fall", "Contain_Right_Kirby.bmp", 2, 2, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Gulp", "Contain_Left_Kirby.bmp", 9, 11, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Gulp", "Contain_Right_Kirby.bmp", 9, 11, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Disgorge", "Contain_Left_Kirby.bmp", 5, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Disgorge", "Contain_Right_Kirby.bmp", 5, 8, 0.1f, false);

	MainRenderer->FindAnimation("Normal_Left_Contain_Walk")->Inters = { 0.2f , 0.3f , 0.2f , 0.3f };
	MainRenderer->FindAnimation("Normal_Right_Contain_Walk")->Inters = { 0.2f , 0.3f , 0.2f , 0.3f };

	MainRenderer->FindAnimation("Normal_Left_Contain_Run")->Inters = { 0.12f , 0.2f , 0.12f , 0.2f };
	MainRenderer->FindAnimation("Normal_Right_Contain_Run")->Inters = { 0.12f , 0.2f , 0.12f , 0.2f };
}

void Kirby::Contain_IdleStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Contain_Idle");
}

void Kirby::Contain_IdleUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Contain_Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		//ChangeState(KirbyState::Contain_Gulp);
		return;
	}
	if (true == (GameEngineInput::IsDown('Z')))
	{
		//ChangeState(KirbyState::Contain_Disgorge);
		return;
	}
	if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Contain_Jump);
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

	if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Walk);
		return;
	}

	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}


void Kirby::Contain_WalkStart()
{
	StateTime = 0.0f;
	DirCheck();
	ChangeAnimationState("Contain_Walk");
}

void Kirby::Contain_WalkUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Contain_Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Contain_Gulp);
		return;
	}

	if (CurrentSpeed < WALKMAXSPEED * 0.2f * _Delta && true == GameEngineInput::IsDown('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Run);
		return;
	}

	if (CurrentSpeed > WALKMAXSPEED * 0.2f * _Delta && true == GameEngineInput::IsDown('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Run);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Contain_Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		// 별 효과
		CurrentSpeed = 0.0f;
	}
	if (true == CheckLeftWallBasedSpeed())
	{
		// 별 효과
		CurrentSpeed = 0.0f;
	}

	if (CurrentSpeed == 0.0f &&
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
			(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}


void Kirby::Contain_RunStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Contain_Run");
}

void Kirby::Contain_RunUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Contain_Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Contain_Gulp);
		return;
	}
	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Contain_Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		// 별 효과
		CurrentSpeed = 0.0f;
	}
	if (true == CheckLeftWallBasedSpeed())
	{
		// 별 효과
		CurrentSpeed = 0.0f;
	}

	if (CurrentSpeed == 0.0f &&
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
			(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}


	MoveHorizontal(RUNSPEED, _Delta);
	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}


void Kirby::Contain_TurnStart()
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

	ChangeAnimationState("Contain_Turn");
}

void Kirby::Contain_TurnUpdate(float _Delta)
{
	if (CurrentSpeed == 0.0f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Contain_Fall);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		// 별 효과
		CurrentSpeed = 0.0f;
	}
	if (true == CheckLeftWallBasedSpeed())
	{
		// 별 효과
		CurrentSpeed = 0.0f;
	}


	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta, BRAKESPEED);
	MoveUpdate(_Delta);
}


void Kirby::Contain_JumpStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	DirCheck();
	GravityReset();
	ChangeAnimationState("Contain_Jump");
}

void Kirby::Contain_JumpUpdate(float _Delta)
{

	StateTime += _Delta;

	if (true == GameEngineInput::IsFree('X'))
	{
		IsChangeState = true;
	}


	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (IsChangeState = true && 0.0f < GetGravityVector().Y)
	{
		ChangeState(KirbyState::Contain_Fall);
		return;
	}

	if (true == CeilingCheck())
	{
		// 별 효과
		GravityReset();
	}

	if (true == GameEngineInput::IsUp('X'))
	{
		AbleJump = false;
	}

	if (true == GameEngineInput::IsPress('X') && StateTime < JUMPTIME && true == AbleJump)
	{
		SetGravityVector(float4::UP * (JUMPPOWER * _Delta));
	}


	BlockedByCeiling();
	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();


	ChangeAnimationState("Contain_Jump");

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}


void Kirby::Contain_FallStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Contain_Fall");
}

void Kirby::Contain_FallUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (true == GetGroundState() && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::Contain_Walk);
		return;
	}

	if (true == GetGroundState() && CurrentSpeed == 0.0f)
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		// 별효과
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWallBasedSpeed())
	{
		// 별효과
		CurrentSpeed = 0.0f;
	}


	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();
	ChangeAnimationState("Contain_Fall");

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate();
}


void Kirby::Contain_GulpStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Contain_Gulp");
}

void Kirby::Contain_GulpUpdate(float _Delta)
{
	IsChangeState = CheckEndAnimation(MainRenderer, "Normal_Left_Contain_Gulp", "Normal_Right_Contain_Gulp");

	if (true == IsChangeState && AbilityStar::None == CurStar->StartAbility && true == GameEngineInput::IsPress('S'))
	{
		delete CurStar;
		CurStar = nullptr;

		ChangeState(KirbyState::LowerPosture);
		return;
	}

	if (true == IsChangeState && AbilityStar::None == CurStar->StartAbility && false == GameEngineInput::IsPress('S'))
	{
		delete CurStar;
		CurStar = nullptr;

		ChangeState(KirbyState::Idle);
		return;
	}

	if (true == IsChangeState && AbilityStar::None != CurStar->StartAbility)
	{
		delete CurStar;
		CurStar = nullptr;

		ChangeState(KirbyState::GetAbility);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		// 별효과
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWallBasedSpeed())
	{
		// 별효과
		CurrentSpeed = 0.0f;
	}


	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	MoveUpdate(_Delta);
}


void Kirby::Contain_DisgorgeStart()
{

}

void Kirby::Contain_DisgorgeUpdate(float _Delta)
{

}