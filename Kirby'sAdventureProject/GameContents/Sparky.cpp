#include "Sparky.h"
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

Sparky::Sparky()
{
}

Sparky::~Sparky()
{
}


void Sparky::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_PowerEnemy.bmp", 25, 25, 0.3f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_PowerEnemy.bmp", 25, 25, 0.3f, false);

	MainRenderer->CreateAnimation("Left_FrontJump", "Left_PowerEnemy.bmp", 24, 24, 0.3f, false);
	MainRenderer->CreateAnimation("Right_FrontJump", "Right_PowerEnemy.bmp", 24, 24, 0.3f, false);

	MainRenderer->CreateAnimation("Left_StanceJump", "Left_PowerEnemy.bmp", 24 , 24 , 0.3f, false);
	MainRenderer->CreateAnimation("Right_StanceJump", "Right_PowerEnemy.bmp", 24 , 24 , 0.3f, false);

	MainRenderer->CreateAnimation("Left_LongJump", "Left_PowerEnemy.bmp", 24, 24, 0.1f, false);
	MainRenderer->CreateAnimation("Right_LongJump", "Right_PowerEnemy.bmp", 24, 24, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Landing", "Left_PowerEnemy.bmp", 26, 26, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Landing", "Right_PowerEnemy.bmp", 26, 26, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Spark", "Left_PowerEnemy.bmp", 27, 27, SPARKYABILITYTIME, true);
	MainRenderer->CreateAnimation("Right_Spark", "Right_PowerEnemy.bmp", 27, 27, SPARKYABILITYTIME, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Sparky::init(const std::string& _FileName, SparkyState _State, const float4& _Pos)
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

void Sparky::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}

void Sparky::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SparkyState::Idle:						return IdleUpdate(_Delta);
	case SparkyState::FrontJump:				return FrontJumpUpdate(_Delta);
	case SparkyState::StanceJump:				return StanceJumpUpdate(_Delta);
	case SparkyState::LongJump:					return LongJumpUpdate(_Delta);
	case SparkyState::Landing:					return LandingUpdate(_Delta);
	case SparkyState::Spark:					return SparkUpdate(_Delta);
	default:
		break;
	}
}

void Sparky::ChangeState(SparkyState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case SparkyState::Idle:					IdleStart();					break;
		case SparkyState::FrontJump:			FrontJumpStart();				break;
		case SparkyState::StanceJump:			StanceJumpStart();				break;
		case SparkyState::LongJump:				LongJumpStart();				break;
		case SparkyState::Landing:				LandingStart();					break;
		case SparkyState::Spark:				SparkStart();					break;
		default:
			break;
		}
	}

	State = _State;
}

void Sparky::ChangeRespawnState()
{
	ChangeState(RespawnState);
}


bool Sparky::IsRightStair()
{
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint);
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint);
	if (((RGB(0, 255, 255) == LeftBottomColor) && (RGB(0, 255, 255) != RightBottomColor))
		|| (RGB(0, 0, 255) == LeftBottomColor && (RGB(0, 0, 255) != RightBottomColor)))
	{
		return true;
	}

	return false;
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void Sparky::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsTurn = false;
	CurrentSpeed = 0.0f;
	GravityReset();
	ChangeAnimationState("Idle");
}

void Sparky::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SPARKYIDLETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		float4 CurrentDir = Kirby::GetMainKirby()->GetPos() - GetPos();

		if ((ActorDir::Left == Dir && CurrentDir.X > 0.0f) ||
			(ActorDir::Right == Dir && CurrentDir.X < 0.0f))
		{
			IsTurn = true;
			RemainStanceJumpCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
		}

		if (0 != RemainStanceJumpCount)
		{
			IsTurn = false;
			--RemainStanceJumpCount;
			ChangeState(SparkyState::StanceJump);
			return;

		}
		else if (true)
		{
			ChangeState(SparkyState::LongJump);
			return;
		}
		else
		{
			ChangeState(SparkyState::FrontJump);
			return;
		}
	}
	

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}
	VerticalUpdate(_Delta);
}


void Sparky::FrontJumpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("FrontJump");
}

void Sparky::FrontJumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 0.5f)
	{
		StateTime = 0.0f;
	}

	if (CurrentJumpDistance > 33.f)
	{
		AbleJump = false;
	}

	if (false == AbleJump && true == GetGroundState())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Landing);
		return;
	}


	if (true == CeilingCheck())
	{
		AbleJump = false;
		GravityReset();
	}

	if (true == AbleJump)
	{
		//float JumpPower = SPARKYJUMPDISTANCE / SPARKYGRAVITYTIMETOMAXSPEED;
		//CurrentJumpDistance += JumpPower * _Delta;
		//SetGravityVector(float4::UP * CurrentJumpDistance);
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
		CurrentSpeed = -SPARKYSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = SPARKYSPEED;
	}



	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(SPARKYGRAVITYLIMIT);
	VerticalUpdate(_Delta);

	BlockedByGround();
	BlockedByWall();

	HorizontalUpdate(_Delta);
}


void Sparky::LandingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Landing");
}

void Sparky::LandingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SPARKYLANDINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Idle);
		return;
	}
}


void Sparky::SparkStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Spark");
}

void Sparky::SparkUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SPARKYABILITYTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Idle);
		return;
	}
}
