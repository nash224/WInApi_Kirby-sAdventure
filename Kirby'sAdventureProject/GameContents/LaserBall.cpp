#include "LaserBall.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
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

LaserBall::LaserBall()
{
}

LaserBall::~LaserBall()
{
}


void LaserBall::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Fly", "Left_PowerEnemy.bmp", 0, 0, 0.3f, false);
	MainRenderer->CreateAnimation("Right_Fly", "Right_PowerEnemy.bmp", 0, 0, 0.3f, false);

	MainRenderer->CreateAnimation("Left_Charging", "Left_PowerEnemy.bmp", 5, 3, LASERBALLSHOOTCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimation("Right_Charging", "Right_PowerEnemy.bmp", 5, 3, LASERBALLSHOOTCHANGEFRAMETIME, true);

	MainRenderer->CreateAnimation("Left_Shoot", "Left_PowerEnemy.bmp", 5, 2, LASERBALLSHOOTCHANGEFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_Shoot", "Right_PowerEnemy.bmp", 5, 2, LASERBALLSHOOTCHANGEFRAMETIME, false);

	MainRenderer->CreateAnimation("Left_RunAway", "Left_PowerEnemy.bmp", 0, 0, 0.3f, false);
	MainRenderer->CreateAnimation("Right_RunAway", "Right_PowerEnemy.bmp", 0, 0, 0.3f, false);

	 MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void LaserBall::init(const std::string& _FileName, LaserBallState _State, const float4& _Pos)
{
	Attribute = AttributeType::Fire;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

void LaserBall::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}

void LaserBall::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LaserBallState::Fly:					return FlyUpdate(_Delta);
	case LaserBallState::Charging:				return ChargingUpdate(_Delta);
	case LaserBallState::Shoot:					return ShootUpdate(_Delta);
	case LaserBallState::RunAway:				return RunAwayUpdate(_Delta);
	default:
		break;
	}
}

void LaserBall::ChangeState(LaserBallState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case LaserBallState::Fly:						FlyStart();					break;
		case LaserBallState::Charging:					ChargingStart();			break;
		case LaserBallState::Shoot:						ShootStart();				break;
		case LaserBallState::RunAway:					RunAwayStart();				break;
		default:
			break;
		}
	}

	State = _State;
}

void LaserBall::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void LaserBall::FlyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("Fly");
}

void LaserBall::FlyUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 3.0f)
	{
		StateTime = 0.0f;

		//if (LaserBallFIREBALLRANGEDETECTION > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
		//{
		//	ChangeState(LaserBallState::FlameBreathCharging);
		//	return;
		//}
		//else if (LaserBallRANGEDETECTION > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
		//{
		//	ChangeState(LaserBallState::FireBallCharging);
		//	return;
		//}
	}

	if (true == CheckLeftWall() || true == LeftGroundIsCliff())
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_Walk");
	}
	else if (true == CheckRightWall() || true == RightGroundIsCliff())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_Walk");
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -LASERBALLSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = LASERBALLSPEED;
	}


	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}
	VerticalUpdate(_Delta);

	HorizontalUpdate(_Delta);
}


void LaserBall::ChargingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("Charging");
}

void LaserBall::ChargingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > LASERBALLSPEED)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(LaserBallState::Shoot);
		return;
	}
}


void LaserBall::ShootStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	ChangeAnimationState("Shoot");
}

void LaserBall::ShootUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > LASERBALLSPEED)
	{
		StateTime = 0.0f;
		++WobbleCount;

		if (ActorDir::Left == Dir)
		{
			if (1 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 6.0f);
			}
			else if (2 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 4.0f);
			}
			else if (0 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 2.0f);
			}
		}
		else if (ActorDir::Right == Dir)
		{
			if (1 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 6.0f);
			}
			else if (2 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 4.0f);
			}
			else if (0 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 2.0f);
			}
		}
	}

	if (9 == WobbleCount)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(LaserBallState::RunAway);
		return;
	}
}

void LaserBall::RunAwayStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("RunAway");
}

void LaserBall::RunAwayUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > LASERBALLSPEED)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		return;
	}
}