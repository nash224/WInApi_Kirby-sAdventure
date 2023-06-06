#include "PoppyBrosJr.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Kirby.h"
#include <vector>

PoppyBrosJr::PoppyBrosJr()
{
}

PoppyBrosJr::~PoppyBrosJr()
{
}


void PoppyBrosJr::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 16, 16, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 16, 16, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Walk", "Left_NormalEnemy.bmp", 16, 17, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_NormalEnemy.bmp", 16, 17, 0.5f, true);

	MainRenderer->CreateAnimation("Left_Jump", "Left_NormalEnemy.bmp", 17, 17, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Jump", "Right_NormalEnemy.bmp", 17, 17, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Fall", "Left_NormalEnemy.bmp", 16, 17, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Fall", "Right_NormalEnemy.bmp", 16, 17, 0.5f, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(NormalState::Idle);


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void PoppyBrosJr::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}


void PoppyBrosJr::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Idle");
}

void PoppyBrosJr::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= POPPYBROSJRCHANGETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Jump);
		return;
	}

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void PoppyBrosJr::JumpStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	ChangeAnimationState("Jump");
}

void PoppyBrosJr::JumpUpdate(float _Delta)
{
	if (0.0f < GetGravityVector().Y)
	{
		ChangeState(NormalState::Fall);
		return;
	}

	float JumpPower = POPPYBROSJRJUMPDISTANCE / POPPYBROSJRJUMPTIME;
	CurrentJumpDistance += JumpPower * _Delta;

	if (CurrentJumpDistance > POPPYBROSJRJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (CurrentJumpDistance < POPPYBROSJRJUMPDISTANCE && true == AbleJump)
	{
		SetGravityVector(float4::UP * JumpPower);
	}

	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Right_Jump");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Left_Jump");
	}

	if (ActorDir::Left == Dir)
	{
		AddPos(float4::LEFT * POPPYBROSJRSPEED * _Delta);
	}

	if (ActorDir::Right == Dir)
	{
		AddPos(float4::RIGHT * POPPYBROSJRSPEED * _Delta);
	}


	BlockedByGround();
	BlockedByWall();

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void PoppyBrosJr::FallStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	ChangeAnimationState("Fall");
}

void PoppyBrosJr::FallUpdate(float _Delta)
{
	if (true == GetGroundState())
	{
		ChangeState(NormalState::Idle);
		return;
	}

	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Right_Fall");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Left_Fall");
	}

	if (ActorDir::Left == Dir)
	{
		AddPos(float4::LEFT * POPPYBROSJRSPEED * _Delta);
	}

	if (ActorDir::Right == Dir)
	{
		AddPos(float4::RIGHT * POPPYBROSJRSPEED * _Delta);
	}


	BlockedByGround();
	BlockedByWall();

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}
