#include "BroomHatter.h"
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

#include "GlobalContents.h"
#include "Kirby.h"

BroomHatter::BroomHatter() 
{
}

BroomHatter::~BroomHatter() 
{
}


void BroomHatter::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	GlobalContents::SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	GlobalContents::SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 3, 3, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 3, 3, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Sweep", "Left_NormalEnemy.bmp", 2, 2, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Sweep", "Right_NormalEnemy.bmp", 2, 2, 0.5f, false);

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

void BroomHatter::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}


void BroomHatter::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Idle");
}

void BroomHatter::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= BROOMHATTERCHANGETIME)
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


void BroomHatter::SweepStart() 
{
	StateTime = 0.0f;
	++SweepCount;
	GetKirbyDirection();

	if (3 == SweepCount)
	{
		SweepCount = 0;
	}

	if (Dir == ActorDir::Left)
	{
		CurrentSpeed = -BROOMHATTERSPEED;
	}
	else if (Dir == ActorDir::Right)
	{
		CurrentSpeed = BROOMHATTERSPEED;
	}

	if (2 == SweepCount)
	{
		if (Dir == ActorDir::Left)
		{
			Dir = ActorDir::Right;
		}
		else if (Dir == ActorDir::Right)
		{
			Dir = ActorDir::Left;
		}
		CurrentSpeed = -CurrentSpeed;
	}

	ChangeAnimationState("Sweep");
}

void BroomHatter::SweepUpdate(float _Delta) 
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
		MainRenderer->ChangeAnimation("Right_Sweep");
	}
	else if (true == CheckRightWall() || RightGroundIsCliff())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Left_Sweep");
	}

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	DecelerationUpdate(BROOMHATTERDECELERATIONSPEED, _Delta);
	HorizontalSpeedLimit(BROOMHATTERMAXSPEED);
	HorizontalUpdate(_Delta);
}
