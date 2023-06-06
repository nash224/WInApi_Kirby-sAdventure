#include "Apple.h"
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

Apple::Apple()
{
}

Apple::~Apple()
{
}


void Apple::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 12, 12, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 12, 12, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Walk", "Left_NormalEnemy.bmp", 8, 11, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_NormalEnemy.bmp", 8, 11, 0.5f, true);


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

void Apple::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}


void Apple::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Idle");
}

void Apple::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= AppleCHANGETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Sweep);
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


void Apple::JumpStart()
{
	StateTime = 0.0f;
	GetKirbyDirection();

	if (Dir == ActorDir::Left)
	{
		CurrentSpeed = -APPLESPEED;
	}
	else if (Dir == ActorDir::Right)
	{
		CurrentSpeed = APPLESPEED;
	}

	ChangeAnimationState("Jump");
}

void Apple::JumpUpdate(float _Delta)
{
	if (CurrentSpeed == 0.0f)
	{
		ChangeState(NormalState::Idle);
		return;
	}

	if (true == CheckLeftWall() || LeftGroundIsCliff())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Right_Jump");
	}
	else if (true == CheckRightWall() || RightGroundIsCliff())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Left_Jump");
	}

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	DecelerationUpdate(APPLEDECELERATIONSPEED, _Delta);
	HorizontalSpeedLimit(APPLEMAXSPEED);
	HorizontalUpdate(_Delta);
}
