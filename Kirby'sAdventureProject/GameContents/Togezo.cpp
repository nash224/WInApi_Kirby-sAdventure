#include "Togezo.h"
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

Togezo::Togezo()
{
}

Togezo::~Togezo()
{
}


void Togezo::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_PowerEnemy.bmp", 12, 13, TogezoWALKINGCHANGEANIMATIONTIME, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_PowerEnemy.bmp", 12, 13, TogezoWALKINGCHANGEANIMATIONTIME, true);

	MainRenderer->CreateAnimationToFrame("Left_Jump", "Left_PowerEnemy.bmp", {14, 15, 16, 15}, TogezoWOBBLETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Jump", "Right_PowerEnemy.bmp", { 14, 15, 16, 15 }, TogezoWOBBLETIME, true);

	MainRenderer->CreateAnimationToFrame("Left_Bounce", "Left_PowerEnemy.bmp", { 14, 15, 16, 15 }, TogezoWOBBLETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Bounce", "Right_PowerEnemy.bmp", { 14, 15, 16, 15 }, TogezoWOBBLETIME, true);

	MainRenderer->CreateAnimationToFrame("Left_Roll", "Left_PowerEnemy.bmp", { 14, 15, 16, 15 }, TogezoWOBBLETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Roll", "Right_PowerEnemy.bmp", { 14, 15, 16, 15 }, TogezoWOBBLETIME, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Togezo::init(const std::string& _FileName, TogezoState _State, const float4& _Pos)
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

void Togezo::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}

void Togezo::StateUpdate(float _Delta)
{
	switch (State)
	{
	case TogezoState::Walk:						return WalkUpdate(_Delta);
	case TogezoState::Jump:						return JumpUpdate(_Delta);
	case TogezoState::Bounce:					return BounceUpdate(_Delta);
	case TogezoState::Roll:						return RollUpdate(_Delta);
	default:
		break;
	}
}

void Togezo::ChangeState(TogezoState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case TogezoState::Walk:						WalkStart();					break;
		case TogezoState::Jump:						JumpStart();					break;
		case TogezoState::Bounce:					BounceStart();					break;
		case TogezoState::Roll:						RollStart();					break;
		default:
			break;
		}
	}

	State = _State;
}

void Togezo::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void Togezo::WalkStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("Walk");
}

void Togezo::WalkUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > TogezoWALKINGCHANGESTATETIME)
	{
		StateTime = 0.0f;

		if (TogezoFIREBALLRANGEDETECTION > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
		{
			ChangeState(TogezoState::Jump);
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
		CurrentSpeed = -TogezoSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = TogezoSPEED;
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


void Togezo::JumpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("Jump");
}

void Togezo::JumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > TogezoFIREBALLCHARGINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(TogezoState::Bounce);
		return;
	}
}


void Togezo::BounceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	ChangeAnimationState("Bounce");
}

void Togezo::BounceUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > TogezoWOBBLETIME)
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
		ChangeState(TogezoState::Roll);
		return;
	}
}

void Togezo::RollStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("Roll");
}

void Togezo::RollUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > TogezoFLAMEBREATHCHARGINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(TogezoState::Walk);
		return;
	}
}

