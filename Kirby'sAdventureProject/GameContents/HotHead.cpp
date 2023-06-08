#include "HotHead.h"
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

HotHead::HotHead()
{
}

HotHead::~HotHead()
{
}


void HotHead::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_PowerEnemy.bmp", 21, 20, HotHeadWALKINGCHANGEANIMATIONTIME, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_PowerEnemy.bmp", 21, 20, HotHeadWALKINGCHANGEANIMATIONTIME, true);

	MainRenderer->CreateAnimation("Left_FireBallCharging", "Left_PowerEnemy.bmp", 21, 20, HotHeadJUMPCHANGEANIMATIONTIME, true);
	MainRenderer->CreateAnimation("Right_FireBallCharging", "Right_PowerEnemy.bmp", 21, 20, HotHeadJUMPCHANGEANIMATIONTIME, true);

	MainRenderer->CreateAnimationToFrame("Left_FireBall", "Left_PowerEnemy.bmp", { 20 , 22 }, HotHeadWOBBLETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_FireBall", "Right_PowerEnemy.bmp", { 20 , 22 }, HotHeadWOBBLETIME, true);

	MainRenderer->CreateAnimation("Left_FlameBreathCharging", "Left_PowerEnemy.bmp", 20, 20, 0.1f, false);
	MainRenderer->CreateAnimation("Right_FlameBreathCharging", "Right_PowerEnemy.bmp", 20, 20, 0.1f, false);

	MainRenderer->CreateAnimation("Left_FlameBreath", "Left_PowerEnemy.bmp", 20, 20, 0.1f, false);
	MainRenderer->CreateAnimation("Right_FlameBreath", "Right_PowerEnemy.bmp", 20, 20, 0.1f, false);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void HotHead::init(const std::string& _FileName, HotHeadState _State, const float4& _Pos)
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

void HotHead::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}

void HotHead::StateUpdate(float _Delta)
{
	switch (State)
	{
	case HotHeadState::Walk:					return WalkUpdate(_Delta);
	case HotHeadState::FireBallCharging:		return FireBallChargingUpdate(_Delta);
	case HotHeadState::FireBall:				return FireBallUpdate(_Delta);
	case HotHeadState::FlameBreathCharging:		return FlameBreathChargingUpdate(_Delta);
	case HotHeadState::FlameBreath:				return FlameBreathUpdate(_Delta);
	default:
		break;
	}
}

void HotHead::ChangeState(HotHeadState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case HotHeadState::Walk:					WalkStart();					break;
		case HotHeadState::FireBallCharging:		FireBallChargingStart();		break;
		case HotHeadState::FireBall:				FireBallStart();				break;
		case HotHeadState::FlameBreathCharging:		FlameBreathChargingStart();		break;
		case HotHeadState::FlameBreath:				FlameBreathStart();				break;
		default:
			break;
		}
	}

	State = _State;
}

void HotHead::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void HotHead::WalkStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	ChangeAnimationState("Walk");
}

void HotHead::WalkUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HotHeadWALKINGCHANGESTATETIME)
	{
		StateTime = 0.0f;

		int ChangeStateNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

		if (1 == ChangeStateNumber / 4)
		{
			ChangeState(HotHeadState::FireBallCharging);
			return;
		}
		else
		{
			ChangeState(HotHeadState::FlameBreathCharging);
			return;
		}
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
		CurrentSpeed = -HotHeadSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = HotHeadSPEED;
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


void HotHead::FireBallChargingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	AbleJump = true;
	EndCount = 0;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	ChangeAnimationState("FireBallCharging");
}

void HotHead::FireBallChargingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HotHeadJUMPCHANGEANIMATIONTIME)
	{
		StateTime = 0.0f;
		++EndCount;
	}


	if (true == IsChangeState)
	{
		ChangeState(HotHeadState::FireBallCharging);
		return;
	}


	BlockedByGround();

	HorizontalUpdate(_Delta);
}


void HotHead::FireBallStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	ChangeAnimationState("FireBall");
}

void HotHead::FireBallUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HotHeadWOBBLETIME)
	{
		StateTime = 0.0f;

		++WobbleCount;
		if (1 == WobbleCount % 2)
		{
			AddPos(float4::UP * 3.0f);
		}
		else
		{
			AddPos(float4::DOWN * 3.0f);
		}
	}

	if (20 == WobbleCount)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		//ChangeState(HotHeadState::);
		return;
	}
}


void HotHead::FlameBreathChargingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("FlameBreathCharging");
}

void HotHead::FlameBreathChargingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 1.5f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(HotHeadState::Walk);
		return;
	}
}


void HotHead::FlameBreathChargingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("FlameBreathCharging");
}

void HotHead::FlameBreathChargingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 1.5f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(HotHeadState::FlameBreath);
		return;
	}
}


void HotHead::FlameBreathStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("FlameBreath");
}

void HotHead::FlameBreathUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 1.5f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(HotHeadState::Walk);
		return;
	}
}
