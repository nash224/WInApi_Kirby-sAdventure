#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"
#include "DustEffect.h"
#include "HitObjectEffect.h"
#include "ExhaleEffect.h"


void Kirby::Normal_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Normal_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	GlobalContents::SpriteFileLoad("Normal_RIght_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	MainRenderer->CreateAnimation("Normal_Left_Idle", "Normal_Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Normal_Right_Idle", "Normal_RIght_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Normal_Left_Walk", "Normal_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Walk", "Normal_RIght_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Left_Run", "Normal_Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Normal_Right_Run", "Normal_RIght_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Normal_Left_Turn", "Normal_Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Normal_Right_Turn", "Normal_RIght_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Normal_Left_Jump", "Normal_Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Jump", "Normal_RIght_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_AerialMotion", "Normal_Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Normal_Right_AerialMotion", "Normal_RIght_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Normal_Left_Fall", "Normal_Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Fall", "Normal_RIght_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_AccelerateDown", "Normal_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_AccelerateDown", "Normal_RIght_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Bounce", "Normal_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Bounce", "Normal_RIght_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Landing", "Normal_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Landing", "Normal_RIght_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_LowerPosture", "Normal_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_LowerPosture", "Normal_RIght_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_LowerAttack", "Normal_Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_LowerAttack", "Normal_RIght_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_HittheWall", "Normal_Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_HittheWall", "Normal_RIght_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_HittheCeiling", "Normal_Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_HittheCeiling", "Normal_RIght_Kirby.bmp", 91, 91, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_TakeOff", "Normal_Left_Kirby.bmp", 15, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_TakeOff", "Normal_RIght_Kirby.bmp", 15, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Fly", "Normal_Left_Kirby.bmp", 19, 20, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Fly", "Normal_RIght_Kirby.bmp", 19, 20, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Left_ExhaleAttack", "Normal_Left_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Normal_Right_ExhaleAttack", "Normal_RIght_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Normal_Left_UseSpecialAbility", "Normal_Left_Kirby.bmp", 24, 26, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_UseSpecialAbility", "Normal_RIght_Kirby.bmp", 24, 26, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_ReleaseSpecialAbility", "Normal_Left_Kirby.bmp", 25, 25, 0.15f, false);
	MainRenderer->CreateAnimation("Normal_Right_ReleaseSpecialAbility", "Normal_RIght_Kirby.bmp", 25, 25, 0.15f, false);

	MainRenderer->CreateAnimation("Normal_Left_Damaged", "Normal_Left_Kirby.bmp", 12, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Damaged", "Normal_RIght_Kirby.bmp", 12, 10, 0.1f, false);
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



	// 데미지 상태 패턴
	CheckKirbyCollision();



	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
}


void Kirby::WalkStart()
{
	StateTime = 0.0f;
	KirbyDirCheck();
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


	// 데미지 상태 패턴
	CheckKirbyCollision();


	
	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
}


void Kirby::RunStart()
{
	StateTime = 0.0f;
	DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>();
	DustEffectPtr->init(GetPos(), GetKirbyScale(), -GetDirUnitVector());

	KirbyDirCheck();
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



	// 데미지 상태 패턴
	CheckKirbyCollision();




	BlockedByGround();
	BlockedByWall();


	MoveHorizontal(RUNSPEED, _Delta);
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
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

	DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>();
	DustEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
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
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == CheckLeftWall() || true == CheckRightWall())
	{
		CurrentSpeed = 0.0f;
		ChangeState(KirbyState::HittheWall);
	}



	// 데미지 상태 패턴
	CheckKirbyCollision();




	BlockedByGround();
	BlockedByWall();

	ActorUtils::DecelerationUpdate(_Delta, BRAKESPEED);
	HorizontalUpdate(_Delta);
}


void Kirby::JumpStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	KirbyDirCheck();
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



	// 데미지 상태 패턴
	CheckKirbyCollision();





	float JumpPower = JUMPMAXDISTANCE / JUMPTIME;
	CurrentJumpDistance += JumpPower * _Delta;

	if (true == GameEngineInput::IsUp('X') || CurrentJumpDistance > JUMPMAXDISTANCE)
	{
		AbleJump = false;
	}

	if (true == GameEngineInput::IsPress('X') && CurrentJumpDistance < JUMPMAXDISTANCE && true == AbleJump)
	{
		SetGravityVector(float4::UP * JumpPower);
	}


	BlockedByCeiling();
	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();


	ChangeAnimationState("Jump");

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void Kirby::AerialMotionStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	KirbyDirCheck();
	ChangeAnimationState("AerialMotion");
}

void Kirby::AerialMotionUpdate(float _Delta)
{
	StateTime += _Delta;

	IsChangeState = MainRenderer->IsAnimationEnd();

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



	// 데미지 상태 패턴
	CheckKirbyCollision();




	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
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
	FallDistance += GetGravityVector().Y * _Delta;

	if (FallDistance > FALLDISTANCE)
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



	// 데미지 상태 패턴
	CheckKirbyCollision();



	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();
	ChangeAnimationState("Fall");

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void Kirby::AccelerateDownStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("AccelerateDown");
}

void Kirby::AccelerateDownUpdate(float _Delta)
{
	BlockedByWall();

	if (true == GetGroundState())
	{
		SetGravityVector(float4::UP * BOUNCEPOWER);
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



	// 데미지 상태 패턴
	CheckKirbyCollision();




	BlockedByGround();
	BlockedByWall();

	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void Kirby::BounceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

	ChangeAnimationState("Bounce");
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



	// 데미지 상태 패턴
	CheckKirbyCollision();





	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();

	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void Kirby::LandingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

	ChangeAnimationState("Landing");
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



	// 데미지 상태 패턴
	CheckKirbyCollision();





	BlockedByWall();
	BlockedByGround();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
}


void Kirby::LowerPostureStart()
{
	StateTime = 0.0f;
	ChangeKirbyBodyState(KirbyBodyState::Lower);
	ChangeAnimationState("LowerPosture");
}

void Kirby::LowerPostureUpdate(float _Delta)
{

	if (false == GetGroundState())
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
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
		ChangeKirbyBodyState(KirbyBodyState::Little);
		ChangeState(KirbyState::Idle);
		return;
	}
	if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f != CurrentSpeed)
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		ChangeState(KirbyState::Walk);
		return;
	}



	// 데미지 상태 패턴
	CheckKirbyCollision();



	BlockedByWall();
	BlockedByGround();

	ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);
}


void Kirby::LowerAttackStart()
{
	StateTime = 0.0f;
	IsChangeState = false; 

	float4 KirbyDirUnitVector = GetDirUnitVector();
	if (KirbyDirUnitVector.X < 0.0f)
	{
		KirbyDirUnitVector =
			float4{ -(LOWERATTACKCOLLISIONSCALE + LOWERTYPECOLLISIONSCALE).Half().X, -LOWERATTACKCOLLISIONSCALE.Half().Y };
	}
	else if (KirbyDirUnitVector.X > 0.0f)
	{
		KirbyDirUnitVector =
			float4{ (LOWERATTACKCOLLISIONSCALE + LOWERTYPECOLLISIONSCALE).Half().X, -LOWERATTACKCOLLISIONSCALE.Half().Y };
	}
	LowerAttackCollision->SetCollisionPos(KirbyDirUnitVector);
	LowerAttackCollision->On();
	Duration = 0.0f;
	ChangeAnimationState("LowerAttack");
}

void Kirby::LowerAttackUpdate(float _Delta)
{
	StateTime += _Delta;
	Duration += _Delta;

	if (StateTime < 0.3f)
	{
		if (Dir == ActorDir::Left)
		{
			CurrentSpeed = -RUNMAXSPEED;
		}

		if (Dir == ActorDir::Right)
		{
			CurrentSpeed = RUNMAXSPEED;
		}
	}
	
	// 벽에 막히면 벽에 부딫힘
	if (true == CheckLeftWall() || true == CheckRightWall())
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		LowerAttackCollision->Off();
		ChangeState(KirbyState::HittheWall);
		return;
	}

	// 슬라이딩 중 바닥이 없으면 낙하
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeKirbyBodyState(KirbyBodyState::Little);
		LowerAttackCollision->Off();
		ChangeState(KirbyState::Fall);
		return;
	}

	// 슬라이딩이 끝내 멈추면 아이들
	if (true == GetGroundState() && 0.0f == CurrentSpeed)
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		LowerAttackCollision->Off();
		ChangeState(KirbyState::Idle);
		return;
	}



	// 데미지 상태 패턴
	CheckKirbyCollision();




	// 슬라이딩 모션에서 먼지 효과
	if (Duration > LOWERATTACKDUSTOCCURRENCECYCLE)
	{
		Duration = 0.0f;

		DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>();
		DustEffectPtr->init(GetPos(), GetKirbyScale(), -GetDirUnitVector());
	}


	BlockedByWall();
	BlockedByGround();

	ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);
}



void Kirby::HittheWallStart()
{
	StateTime = 0.0f;
	CurrentSpeed = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

	ChangeAnimationState("HittheWall");
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



	// 데미지 상태 패턴
	CheckKirbyCollision();




	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void Kirby::HittheCeilingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

	ChangeAnimationState("HittheCeiling");
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




	// 데미지 상태 패턴
	CheckKirbyCollision();




	BlockedByCeiling();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void Kirby::TakeOffStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeKirbyBodyState(KirbyBodyState::Fat);
	SetAirResistance(0.4f);
	ChangeAnimationState("TakeOff");
}

void Kirby::TakeOffUpdate(float _Delta)
{
	IsChangeState = MainRenderer->IsAnimationEnd();

	if (true == IsChangeState)
	{
		ChangeState(KirbyState::Fly);
		return;
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		SetGravityVector(float4::UP * FLYPOWER);
	}


	if (true == CeilingCheck())
	{
		GravityReset();
	}

	int CurFrame = static_cast<int>(MainRenderer->GetCurFrame());
	ChangeAnimationState("TakeOff", CurFrame);



	// 데미지 상태 패턴
	CheckKirbyCollision();



	BlockedByGround();
	BlockedByCeiling();
	MoveHorizontal(FLYSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void Kirby::FlyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Fly");
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
		SetGravityVector(float4::UP * FLYPOWER);
	}

	if (false == GameEngineInput::IsPress('W') && false == GameEngineInput::IsPress('X'))
	{
		MainRenderer->FindAnimation("Normal_Left_Fly")->Inters = { 0.2f, 0.2f };
		MainRenderer->FindAnimation("Normal_Right_Fly")->Inters = { 0.2f, 0.2f };
	}

	// 천장에 닿았을 때
	if (true == CeilingCheck())
	{
		GravityReset();
	}

	// 청록색 비트맵일 때
	if (true == IsSolidGround() && false == (GameEngineInput::IsPress('W') || GameEngineInput::IsPress('X')))
	{
		GravityReset();
	}

	if (true == IsPassableGround() && GetGravityVector().Y >= 0.0f && false == (GameEngineInput::IsPress('W') || GameEngineInput::IsPress('X')))
	{
		GravityReset();
	}



	// 데미지 상태 패턴
	CheckKirbyCollision();




	BlockedByGround();
	BlockedByCeiling();
	MoveHorizontal(FLYSPEED, _Delta);
	BlockedByWall();

	ChangeAnimationState("Fly");

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	if (false == GetGroundState() || (true == GameEngineInput::IsPress('W') || true == GameEngineInput::IsPress('X')))
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void Kirby::ExhaleAttackStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeKirbyBodyState(KirbyBodyState::Little);

	ExhaleEffect* ExhaleEffectPtr = GetLevel()->CreateActor<ExhaleEffect>();
	ExhaleEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
	ExhaleEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);

	ChangeAnimationState("ExhaleAttack");
}

void Kirby::ExhaleAttackUpdate(float _Delta)
{
	StateTime += _Delta;

	IsChangeState = MainRenderer->IsAnimationEnd();

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



	// 데미지 상태 패턴
	CheckKirbyCollision();



	if (true == CeilingCheck())
	{
		GravityReset();
	}


	BlockedByGround();
	BlockedByCeiling();
	MoveHorizontal(FLYSPEED, _Delta);
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}




void Kirby::DamagedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;


	ImmuneState = true;
	KirbyBodyCollisonOff();



	// 피해를 입으면 기본 상태로
	if (AbilityStar::Normal != Mode)
	{
		Mode = AbilityStar::Normal;
	}



	ChangeAnimationState("Damaged");
}

void Kirby::DamagedUpdate(float _Delta)
{
	StateTime += _Delta;


	// 상태 지속시간
	if (MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}


	// 커비가 땅에 붙어있을 때 => 아이들
	if (true == IsChangeState && true == GetGroundState())
	{
		ChangeState(KirbyState::Idle);
		return;
	}



	// 커비가 체공 상태일 때 => Fall
	if (true == IsChangeState && false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}





	// 맵을 벗어나지 못함
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();



	// 체공상태일 때 중력 적용
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}


	// 감속
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
}