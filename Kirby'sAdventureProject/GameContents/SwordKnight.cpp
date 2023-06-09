#include "SwordKnight.h"
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

SwordKnight::SwordKnight()
{
}

SwordKnight::~SwordKnight()
{
}


void SwordKnight::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_SwordKnight.bmp", "Resources\\Unit\\Grunt", 7, 3);
	ResourcesManager::GetInst().SpriteFileLoad("Right_SwordKnight.bmp", "Resources\\Unit\\Grunt", 7, 3);
	 
	MainRenderer->CreateAnimation("Left_PendulumStride", "Left_SwordKnight.bmp", 14, 19, 0.2f, true);
	MainRenderer->CreateAnimation("Right_PendulumStride", "Right_SwordKnight.bmp", 14, 19, 0.2f, true);

	MainRenderer->CreateAnimation("Left_RaiseSword", "Left_SwordKnight.bmp", 7, 7, SwordKnightROLLINGCHANGEFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_RaiseSword", "Right_SwordKnight.bmp", 7, 7, SwordKnightROLLINGCHANGEFRAMETIME, false);

	MainRenderer->CreateAnimation("Left_Slash", "Left_SwordKnight.bmp", 7, 13, SwordKnightROLLINGCHANGEFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_Slash", "Right_SwordKnight.bmp", 7, 13, SwordKnightROLLINGCHANGEFRAMETIME, false);

	MainRenderer->CreateAnimation("Left_Underhand", "Left_SwordKnight.bmp", 0, 0, SwordKnightROLLINGCHANGEFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_Underhand", "Right_SwordKnight.bmp", 0, 0, SwordKnightROLLINGCHANGEFRAMETIME, false);

	MainRenderer->CreateAnimation("Left_ReversingSlash", "Left_SwordKnight.bmp", 0, 6, SwordKnightROLLINGCHANGEFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_ReversingSlash", "Right_SwordKnight.bmp", 0, 6, SwordKnightROLLINGCHANGEFRAMETIME, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void SwordKnight::init(const std::string& _FileName, SwordKnightState _State, const float4& _Pos)
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

void SwordKnight::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}

void SwordKnight::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SwordKnightState::PendulumStride:				return PendulumStrideUpdate(_Delta);
	case SwordKnightState::RaiseSword:					return RaiseSwordUpdate(_Delta);
	case SwordKnightState::Slash:						return SlashUpdate(_Delta);
	case SwordKnightState::Underhand:					return UnderhandUpdate(_Delta);
	case SwordKnightState::ReversingSlash:				return ReversingSlashUpdate(_Delta);
	default:
		break;
	}
}

void SwordKnight::ChangeState(SwordKnightState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case SwordKnightState::PendulumStride:				PendulumStrideStart();				break;
		case SwordKnightState::RaiseSword:					RaiseSwordStart();					break;
		case SwordKnightState::Slash:						SlashStart();						break;
		case SwordKnightState::Underhand:					UnderhandStart();					break;
		case SwordKnightState::ReversingSlash:				ReversingSlashStart();				break;
		default:
			break;
		}
	}

	State = _State;
}

void SwordKnight::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void SwordKnight::PendulumStrideStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("PendulumStride");
}

void SwordKnight::PendulumStrideUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SwordKnightROLLINGCOOLDOWN)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SwordKnightState::RaiseSword);
		return;
	}

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}
	VerticalUpdate(_Delta);
}


void SwordKnight::RaiseSwordStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BounceCount = 0;
	GetKirbyDirection();
	GravityReset();
	ChangeAnimationState("RaiseSword");
}

void SwordKnight::RaiseSwordUpdate(float _Delta)
{
	if (true == IsChangeState)
	{
		ChangeState(SwordKnightState::Slash);
		return;
	}

	BlockedByGround();

	Gravity(_Delta);
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);
}


void SwordKnight::SlashStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BounceCount = 0;
	GetKirbyDirection();
	GravityReset();
	ChangeAnimationState("Slash");
}

void SwordKnight::SlashUpdate(float _Delta)
{
	if (true == IsChangeState)
	{
		ChangeState(SwordKnightState::ReversingSlash);
		return;
	}

	BlockedByGround();

	Gravity(_Delta);
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);
}


void SwordKnight::UnderhandStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BounceCount = 0;
	GetKirbyDirection();
	GravityReset();
	ChangeAnimationState("Underhand");
}

void SwordKnight::UnderhandUpdate(float _Delta)
{
	if (true == IsChangeState)
	{
		ChangeState(SwordKnightState::ReversingSlash);
		return;
	}

	BlockedByGround();

	Gravity(_Delta);
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);
}


void SwordKnight::ReversingSlashStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsRollingSpeedZero = false;
	CurrentSpeed = SwordKnightROLLINGSPEED;
	RollingSpeedZeroTime = SwordKnightCLIFFSTOPTIME;
	GetKirbyDirection();
	ChangeAnimationState("ReversingSlash");
}

void SwordKnight::ReversingSlashUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SwordKnightROLLINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SwordKnightState::PendulumStride);
		return;
	}

	if ((ActorDir::Left == Dir && true == LeftGroundIsCliff()) ||
		(ActorDir::Right == Dir && true == RightGroundIsCliff()))
	{
		IsRollingSpeedZero = true;
	}

	BlockedByGround();
	BlockedByWall();

	if (false == IsRollingSpeedZero)
	{
		HorizontalUpdate(_Delta);
	}
}

