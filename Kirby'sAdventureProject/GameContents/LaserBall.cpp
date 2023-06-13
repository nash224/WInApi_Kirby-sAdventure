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

#include "GlobalContents.h"
#include "Kirby.h"
#include "LaserEffect.h"
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

	GlobalContents::SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	GlobalContents::SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Fly", "Left_PowerEnemy.bmp", 0, 0, 0.3f, false);
	MainRenderer->CreateAnimation("Right_Fly", "Right_PowerEnemy.bmp", 0, 0, 0.3f, false);

	MainRenderer->CreateAnimation("Left_Charging", "Left_PowerEnemy.bmp", 5, 3, LASERBALLSHOOTCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimation("Right_Charging", "Right_PowerEnemy.bmp", 5, 3, LASERBALLSHOOTCHANGEFRAMETIME, true);

	MainRenderer->CreateAnimation("Left_Shoot", "Left_PowerEnemy.bmp", 5, 2, LASERBALLSHOOTCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimation("Right_Shoot", "Right_PowerEnemy.bmp", 5, 2, LASERBALLSHOOTCHANGEFRAMETIME, true);

	MainRenderer->CreateAnimation("Right_RunAway", "Left_PowerEnemy.bmp", 0, 0, 0.3f, false);
	MainRenderer->CreateAnimation("Left_RunAway", "Right_PowerEnemy.bmp", 0, 0, 0.3f, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void LaserBall::init(const std::string& _FileName, LaserBallState _State, const float4& _Pos)
{
	Attribute = AttributeType::Fire;
	Ability = AbilityStar::Laser;

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
	CurrentSpeed = 0.0f;
	CurentVerticalSpeed = 0.0f;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("Fly");
}

void LaserBall::FlyUpdate(float _Delta)
{
	StateTime += _Delta;

	float4 LaserBallPos = GetPos();
	float4 KirbyPos = Kirby::GetMainKirby()->GetPos();
	float4 OpponentDistance = KirbyPos - LaserBallPos;

	if (LASERBALLSHOOTVERTICALDETECTRANGE > abs(OpponentDistance.Y) &&
		LASERBALLSHOOTDETECTMINRANGE < abs(OpponentDistance.X) && 
		abs(OpponentDistance.X) < LASERBALLSHOOTDETECTMAXRANGE)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(LaserBallState::Charging);
		return;
	}


	if (LASERBALLRUNAWAYDETECTRANGE > abs(OpponentDistance.X))
	{
		if (LaserBallPos.Y < KirbyPos.Y)
		{
			if (OpponentDistance.Y < LASERBALLVERTICALDETECTRANGE)
			{
				CurentVerticalSpeed -= LASERBALLACELECTIONSPEED * _Delta;
			}
			else if (OpponentDistance.Y > LASERBALLVERTICALDETECTRANGE)
			{
				CurentVerticalSpeed += LASERBALLACELECTIONSPEED * _Delta;
			}
		}
		else if (LaserBallPos.Y > KirbyPos.Y)
		{
			if (OpponentDistance.Y > -LASERBALLVERTICALDETECTRANGE)
			{
				CurentVerticalSpeed += LASERBALLACELECTIONSPEED * _Delta;
			}
			else if (OpponentDistance.Y < -LASERBALLVERTICALDETECTRANGE)
			{
				CurentVerticalSpeed -= LASERBALLACELECTIONSPEED * _Delta;
			}
		}
	}
	else if (LASERBALLRUNAWAYDETECTRANGE < abs(OpponentDistance.X))
	{
		if (LaserBallPos.Y < KirbyPos.Y)
		{
			CurentVerticalSpeed += LASERBALLACELECTIONSPEED * _Delta;
		}
		else if (LaserBallPos.Y > KirbyPos.Y)
		{
			CurentVerticalSpeed -= LASERBALLACELECTIONSPEED * _Delta;
		}
	}

	if (OpponentDistance.X < LASERBALLRUNAWAYDETECTRANGE && KirbyPos.X > LaserBallPos.X)
	{
		if (ActorDir::Right == Dir)
		{
			Dir = ActorDir::Left;
			MainRenderer->ChangeAnimation("Left_Fly");
		}
		CurrentSpeed -= LASERBALLACELECTIONSPEED * _Delta;
	}
	else if (OpponentDistance.X > -LASERBALLRUNAWAYDETECTRANGE && KirbyPos.X < LaserBallPos.X)
	{
		if (ActorDir::Left == Dir)
		{
			Dir = ActorDir::Right;
			MainRenderer->ChangeAnimation("Right_Fly");
		}
		CurrentSpeed += LASERBALLACELECTIONSPEED * _Delta;
	}

	if (OpponentDistance.X > LASERBALLRUNAWAYDETECTRANGE)
	{
		if (ActorDir::Left == Dir)
		{
			Dir = ActorDir::Right;
			MainRenderer->ChangeAnimation("Right_Fly");
		}
		CurrentSpeed += LASERBALLACELECTIONSPEED * _Delta;
	}
	else if (OpponentDistance.X < -LASERBALLRUNAWAYDETECTRANGE)
	{
		if (ActorDir::Right == Dir)
		{
			Dir = ActorDir::Left;
			MainRenderer->ChangeAnimation("Left_Fly");
		}
		CurrentSpeed -= LASERBALLACELECTIONSPEED * _Delta;
	}

	VerticalSpeedLimitBasedlevitation(LAZERBALLLIMITSPEED);
	VerticalUpdateBasedlevitation(_Delta);

	HorizontalSpeedLimit(LAZERBALLLIMITSPEED);
	HorizontalUpdate(_Delta);
}


void LaserBall::ChargingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChargingCount = GameEngineRandom::MainRandom.RandomInt(4, 12);
	ShootCount = (ChargingCount - 4) / 2 + 1;
	GetKirbyDirection();
	ChangeAnimationState("Charging");
}

void LaserBall::ChargingUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		--ChargingCount;
	}

	if (0 == ChargingCount)
	{
		ChangeState(LaserBallState::Shoot);
		return;
	}
}


void LaserBall::ShootStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	CurentVerticalSpeed = 0.0f;
	ChangeAnimationState("Shoot");
}

void LaserBall::ShootUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		LaserEffect* LaserEffect1 = GetLevel()->CreateActor<LaserEffect>();
		LaserEffect1->init(GetPos(), Scale, GetAbilityDir());
		LaserEffect1->SetActorCollision(CollisionOrder::MonsterAbility, CollisionType::Rect);
		--ShootCount;
	}

	if (0 == ShootCount)
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
	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = LASERBALLRUNAWAYSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = -LASERBALLRUNAWAYSPEED;
	}

	ReverseGravity(_Delta);
	VerticalUpdate(_Delta);

	HorizontalUpdate(_Delta);
}



void LaserBall::Render(float _Delta)
{
	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//int CameraPos = GetLevel()->GetMainCamera()->GetPos().iX();

	//GameEngineWindowTexture* Backbuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	//HDC LineDC = Backbuffer->GetImageDC();

	//MoveToEx(LineDC, GetPos().iX() - CameraPos + static_cast<int>(LASERBALLSHOOTDETECTMINRANGE), 0, NULL);
	//LineTo(LineDC, GetPos().iX() - CameraPos + static_cast<int>(LASERBALLSHOOTDETECTMINRANGE), WinScale.iY());

	//MoveToEx(LineDC, GetPos().iX() - CameraPos + static_cast<int>(LASERBALLRUNAWAYDETECTRANGE), 0, NULL);
	//LineTo(LineDC, GetPos().iX() - CameraPos + static_cast<int>(LASERBALLRUNAWAYDETECTRANGE), WinScale.iY());

	//MoveToEx(LineDC, GetPos().iX() - CameraPos + static_cast<int>(LASERBALLSHOOTDETECTMAXRANGE), 0, NULL);
	//LineTo(LineDC, GetPos().iX() - CameraPos + static_cast<int>(LASERBALLSHOOTDETECTMAXRANGE), WinScale.iY());
}