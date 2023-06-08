#include "BrontoBurt.h"
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

BrontoBurt::BrontoBurt()
{
}

BrontoBurt::~BrontoBurt()
{
}


void BrontoBurt::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);
	ResourcesManager::GetInst().SpriteFileLoad("Right_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);

	MainRenderer->CreateAnimation("Left_Idle", "Left_AerialEnemy.bmp", 7, 7, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_AerialEnemy.bmp", 7, 7, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Rise", "Left_AerialEnemy.bmp", 6, 7, 0.3f, true);
	MainRenderer->CreateAnimation("Right_Rise", "Right_AerialEnemy.bmp", 6, 7, 0.3f, true);

	MainRenderer->CreateAnimation("Left_Fly", "Left_AerialEnemy.bmp", 6, 7, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Fly", "Right_AerialEnemy.bmp", 6, 7, 0.1f, true);

	MainRenderer->CreateAnimation("Left_WaveFlightRise", "Left_AerialEnemy.bmp", 6, 7, 0.15f, true);
	MainRenderer->CreateAnimation("Right_WaveFlightRise", "Right_AerialEnemy.bmp", 6, 7, 0.15f, true);

	MainRenderer->CreateAnimation("Left_WaveFlightFall", "Left_AerialEnemy.bmp", 6, 6, 0.5f, false);
	MainRenderer->CreateAnimation("Right_WaveFlightFall", "Right_AerialEnemy.bmp", 6, 6, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Exit", "Left_AerialEnemy.bmp", 6, 7, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Exit", "Right_AerialEnemy.bmp", 6, 7, 0.5f, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void BrontoBurt::init(const std::string& _FileName, BrontoState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void BrontoBurt::Update(float _Delta)
{
	StateUpdate(_Delta);

	CheckOverScreen();
}


void BrontoBurt::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BrontoState::Idle:					return IdleUpdate(_Delta);
	case BrontoState::Rise:					return RiseUpdate(_Delta);
	case BrontoState::Fly:					return FlyUpdate(_Delta);
	case BrontoState::WaveFlightRise:		return WaveFlightRiseUpdate(_Delta);
	case BrontoState::WaveFlightFall:		return WaveFlightFallUpdate(_Delta);
	default:
		break;
	}
}

void BrontoBurt::ChangeState(BrontoState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case BrontoState::Idle:					IdleStart();					break;
		case BrontoState::Rise:					RiseStart();					break;
		case BrontoState::Fly:					FlyStart();						break;
		case BrontoState::WaveFlightRise:		WaveFlightRiseStart();			break;
		case BrontoState::WaveFlightFall:		WaveFlightFallStart();			break;
		default:
			break;
		}
	}

	State = _State;
}

void BrontoBurt::ChangeRespawnState()
{
	ChangeState(RespawnState);
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void BrontoBurt::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Idle");
}

void BrontoBurt::IdleUpdate(float _Delta)
{
	if (BRONTORECOGNITIONRANGE > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(BrontoState::Rise);
		return;
	}

	BlockedByGround();
	BlockedByWall();
}


void BrontoBurt::RiseStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	StopRise = false;
	RiseDistance = 0.0f;
	ParabolicRiseStartDistance = GetPos().Y - BRONTORISEDISTANCE;
	GravityReset();
	ChangeAnimationState("Rise");
}

void BrontoBurt::RiseUpdate(float _Delta)
{
	if (RiseDistance > BRONTORISEDISTANCE && false == StopRise)
	{
		StopRise = true;
	}

	if (true == StopRise && GetPos().Y > ParabolicRiseStartDistance && GetGravityVector().Y > 0.0f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(BrontoState::Fly);
		return;
	}

	if (RiseDistance < BRONTORISEDISTANCE && false == StopRise)
	{
		float RisePower = BRONTORISEDISTANCE / BRONTORISETIME;
		RiseDistance += RisePower * _Delta;
		SetGravityVector(float4::UP * RisePower);
	}


	if (true == StopRise)
	{
		Gravity(_Delta);
	}

	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void BrontoBurt::FlyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsGoForward = false;
	CurrentSpeed = 0.0f;
	ChangeAnimationState("Fly");
}

void BrontoBurt::FlyUpdate(float _Delta)
{
	if (GetGravityVector().Y < 0.0f)
	{
		IsGoForward = true;
	}

	if (false == IsGoForward)
	{
		float NowGravityVector = GetGravityVector().Y;
		SetGravityVector(float4::UP * ( NowGravityVector - BRONTOFLYPOWER * _Delta ));
		VerticalUpdate(_Delta);
	}

	if (true == IsGoForward)
	{
		if (ActorDir::Left == Dir)
		{
			CurrentSpeed -= BRONTOFLYSPEED / BRONTOFLYSPEEDACCELERATIONTIME * _Delta;
		}
		else if (ActorDir::Right == Dir)
		{
			CurrentSpeed += BRONTOFLYSPEED / BRONTOFLYSPEEDACCELERATIONTIME * _Delta;
		}

		HorizontalUpdate(_Delta);
	}
}


void BrontoBurt::WaveFlightRiseStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsChangeGravityReverse = false;
	ChangeGravityDistance = RespawnLocation.Y + BRONTOWAVEFLIGHTCHANGEHEIGHT;
	ChangeAnimationState("WaveFlightRise");
}

void BrontoBurt::WaveFlightRiseUpdate(float _Delta)
{
	if (GetPos().Y < ChangeGravityDistance)
	{
		IsChangeGravityReverse = true;
	}

	if (GetGravityVector().Y > 0.0f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(BrontoState::WaveFlightFall);
		return;
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -BRONTOWAVEFLIGHTSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = BRONTOWAVEFLIGHTSPEED;
	}

	if (false == IsChangeGravityReverse)
	{
		ReverseGravity(_Delta);
	}
	else if (true == IsChangeGravityReverse)
	{
		Gravity(_Delta);
	}

	VerticalUpdate(_Delta);
	HorizontalUpdate(_Delta);
}


void BrontoBurt::WaveFlightFallStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsChangeGravityReverse = false;

	if (WaveFlightCountBasedFall == 3)
	{
		GravityReset();
		WaveFlightCountBasedFall = 0;
	}
	++WaveFlightCountBasedFall;

	ChangeGravityDistance = RespawnLocation.Y + BRONTOWAVEFLIGHTCHANGEHEIGHT;
	//RespawnState = BrontoState::WaveFlightFall;
	ChangeAnimationState("WaveFlightFall");
}

void BrontoBurt::WaveFlightFallUpdate(float _Delta)
{
	if (GetPos().Y > ChangeGravityDistance)
	{
		IsChangeGravityReverse = true;
	}

	if (GetGravityVector().Y < 0.0f)
	{
		IsChangeState = true;
	}


	if (true == IsChangeState && WaveFlightCountBasedFall < 3)
	{
		ChangeState(BrontoState::WaveFlightRise);
		return;
	}


	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -BRONTOWAVEFLIGHTSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = BRONTOWAVEFLIGHTSPEED;
	}

	if (false == IsChangeGravityReverse)
	{
		Gravity(_Delta);
	}
	else if (true == IsChangeGravityReverse)
	{
		ReverseGravity(_Delta);
	}

	VerticalUpdate(_Delta);
	HorizontalUpdate(_Delta);
}

