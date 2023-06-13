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

#include "GlobalContents.h"
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

	GlobalContents::SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	GlobalContents::SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_PowerEnemy.bmp", 12, 13, 0.2f, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_PowerEnemy.bmp", 12, 13, 0.2f, true);

	MainRenderer->CreateAnimationToFrame("Left_Bounce", "Left_PowerEnemy.bmp", {14, 15, 16, 29}, TOGEZOROLLINGCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Bounce", "Right_PowerEnemy.bmp", { 14, 15, 16, 29 }, TOGEZOROLLINGCHANGEFRAMETIME, true);

	MainRenderer->CreateAnimationToFrame("Left_Roll", "Left_PowerEnemy.bmp", { 14, 15, 16, 29 }, TOGEZOROLLINGCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Roll", "Right_PowerEnemy.bmp", { 14, 15, 16, 29 }, TOGEZOROLLINGCHANGEFRAMETIME, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionPos(float4{ 0.0f, -Scale.hY()});
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->On();

	AbilityCollision = CreateCollision(CollisionOrder::MonsterBody);
	AbilityCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY()});
	AbilityCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	AbilityCollision->SetCollisionType(CollisionType::Rect);
	AbilityCollision->Off();
}

void Togezo::init(const std::string& _FileName, TogezoState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Thorn;

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

	if (StateTime > TOGEZOROLLINGCOOLDOWN)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(TogezoState::Bounce);
		return;
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
		CurrentSpeed = -TOGEZOSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = TOGEZOSPEED;
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


void Togezo::BounceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BounceCount = 0;
	GetKirbyDirection();
	GravityReset();
	AbilityCollision->On();
	ChangeAnimationState("Bounce");
}

void Togezo::BounceUpdate(float _Delta)
{
	if (true == GetGroundState() && 0.0f < GetGravityVector().Y)
	{
		switch (BounceCount)
		{
		case 0:
			++BounceCount;
			SetGravityVector(float4::UP * TOGEZOJUMPDISTANCE);
			break;
		case 1:
			++BounceCount;
			SetGravityVector(float4::UP * TOGEZOJUMPDISTANCE * 0.7f);
			break;
		case 2:
			++BounceCount;
			SetGravityVector(float4::UP * TOGEZOJUMPDISTANCE * 0.35f);
			break;
		case 3:
			IsChangeState = true;
			break;
		default:
			break;
		}
	}

	if (true == IsChangeState)
	{
		ChangeState(TogezoState::Roll);
		return;
	}

	BlockedByGround();

	Gravity(_Delta);
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);
}

void Togezo::RollStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsRollingSpeedZero = false;
	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -TOGEZOROLLINGSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = TOGEZOROLLINGSPEED;
	}
	ChangeAnimationState("Roll");
}

void Togezo::RollUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > TOGEZOROLLINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		AbilityCollision->Off();
		ChangeState(TogezoState::Walk);
		return;
	}

	if (ActorDir::Left == Dir && true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = TOGEZOROLLINGSPEED;
		ChangeAnimationState("Roll");
	}
	else if (ActorDir::Right == Dir && true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -TOGEZOROLLINGSPEED;
		ChangeAnimationState("Roll");
	}

	if ((ActorDir::Left == Dir && true == LeftGroundIsCliff()) || 
		(ActorDir::Right == Dir && true == RightGroundIsCliff()))
	{
		IsRollingSpeedZero = true;
	}

	if (true == IsRollingSpeedZero)
	{
		RollingSpeedZeroTime -= _Delta;
	}

	if (RollingSpeedZeroTime < 0.0f && true == IsRollingSpeedZero)
	{
		if (ActorDir::Left == Dir)
		{
			Dir = ActorDir::Right;
		}
		else if (ActorDir::Right == Dir)
		{
			Dir = ActorDir::Left;
		}
		CurrentSpeed = !CurrentSpeed;
		ChangeAnimationState("Roll");
		IsRollingSpeedZero = false;
	}


	BlockedByGround();
	BlockedByWall();

	if (false == IsRollingSpeedZero)
	{
		HorizontalUpdate(_Delta);
	}
}

