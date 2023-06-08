#include "WaddleDoo.h"
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

WaddleDoo::WaddleDoo()
{
}

WaddleDoo::~WaddleDoo()
{
}


void WaddleDoo::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_PowerEnemy.bmp", 21, 20, WADDLEDOOWALKINGCHANGEANIMATIONTIME, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_PowerEnemy.bmp", 21, 20, WADDLEDOOWALKINGCHANGEANIMATIONTIME, true);

	MainRenderer->CreateAnimation("Left_Jump", "Left_PowerEnemy.bmp", 21, 20, WADDLEDOOJUMPCHANGEANIMATIONTIME, true);
	MainRenderer->CreateAnimation("Right_Jump", "Right_PowerEnemy.bmp", 21, 20, WADDLEDOOJUMPCHANGEANIMATIONTIME, true);

	MainRenderer->CreateAnimationToFrame("Left_Wobble", "Left_PowerEnemy.bmp", { 20 , 22 }, WADDLEDOOWOBBLETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Wobble", "Right_PowerEnemy.bmp", { 20 , 22 }, WADDLEDOOWOBBLETIME, true);

	MainRenderer->CreateAnimation("Left_ActivateAbility", "Left_PowerEnemy.bmp", 20, 20, 0.1f, false);
	MainRenderer->CreateAnimation("Right_ActivateAbility", "Right_PowerEnemy.bmp", 20, 20, 0.1f, false);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void WaddleDoo::init(const std::string& _FileName, WaddleDooState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天 */

void WaddleDoo::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}

void WaddleDoo::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WaddleDooState::Walk:					return WalkUpdate(_Delta);
	case WaddleDooState::Jump:					return JumpUpdate(_Delta);
	case WaddleDooState::Wobble:				return WobbleUpdate(_Delta);
	case WaddleDooState::ActivateAbility:		return ActivateAbilityUpdate(_Delta);
	default:
		break;
	}
}

void WaddleDoo::ChangeState(WaddleDooState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case WaddleDooState::Walk:					WalkStart();					break;
		case WaddleDooState::Jump:					JumpStart();					break;
		case WaddleDooState::Wobble:				WobbleStart();					break;
		case WaddleDooState::ActivateAbility:		ActivateAbilityStart();			break;
		default:
			break;
		}
	}

	State = _State;
}

void WaddleDoo::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* 天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天 */


void WaddleDoo::WalkStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	ChangeAnimationState("Walk");
}

void WaddleDoo::WalkUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > WADDLEDOOWALKINGCHANGESTATETIME)
	{
		StateTime = 0.0f;

		int ChangeStateNumber = GameEngineRandom::MainRandom.RandomInt(1, 4);

		if (1 == ChangeStateNumber / 4)
		{
			ChangeState(WaddleDooState::Jump);
			return;
		}
		else
		{
			ChangeState(WaddleDooState::Wobble);
			return;
		}
	}

	if (true == LeftGroundIsCliff() || true == RightGroundIsCliff())
	{
		ChangeState(WaddleDooState::Jump);
		return;
	}

	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_Walk");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_Walk");
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -WADDLEDOOSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = WADDLEDOOSPEED;
	}


	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}
	GravityLimit(WADDLEDOOGRAVITYLIMIT);
	VerticalUpdate(_Delta);

	HorizontalUpdate(_Delta);
}


void WaddleDoo::JumpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	AbleJump = true;
	EndCount = 0;
	CurrentJumpDistance = 0.0f;
	MainRenderer->FindAnimation("Left_Jump")->Loop = true;
	MainRenderer->FindAnimation("Right_Jump")->Loop = true;
	GravityReset();
	ChangeAnimationState("Jump");
}

void WaddleDoo::JumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > WADDLEDOOJUMPCHANGEANIMATIONTIME)
	{
		StateTime = 0.0f;
		++EndCount;
	}

	if (4 == EndCount)
	{
		MainRenderer->FindAnimation("Left_Jump")->Loop = false;
		MainRenderer->FindAnimation("Right_Jump")->Loop = false;
	}

	if (CurrentJumpDistance > WADDLEDOOJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (false == AbleJump && true == GetGroundState())
	{
		IsChangeState = true;
	}
	
	if (true == IsChangeState)
	{
		ChangeState(WaddleDooState::Walk);
		return;
	}


	if (true == CeilingCheck())
	{
		AbleJump = false;
		GravityReset();
	}

	if (true == AbleJump)
	{
		float JumpPower = WADDLEDOOJUMPDISTANCE / WADDLEDOOGRAVITYTIMETOMAXSPEED;
		CurrentJumpDistance += JumpPower * _Delta;
		SetGravityVector(float4::UP * CurrentJumpDistance);
	}


	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_Jump");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_Jump");
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -WADDLEDOOSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = WADDLEDOOSPEED;
	}



	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(WADDLEDOOGRAVITYLIMIT);
	VerticalUpdate(_Delta);

	BlockedByGround();
	BlockedByWall();

	HorizontalUpdate(_Delta);
}


void WaddleDoo::WobbleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	WobbleFrame = -1;
	ChangeAnimationState("Wobble");
}

void WaddleDoo::WobbleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > WADDLEDOOWOBBLETIME)
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
		ChangeState(WaddleDooState::ActivateAbility);
		return;
	}
}


void WaddleDoo::ActivateAbilityStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("ActivateAbility");
}

void WaddleDoo::ActivateAbilityUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > WADDLEDOOACTIVATEABILITYTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(WaddleDooState::Walk);
		return;
	}
}
