#include "Scarfy.h"
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

Scarfy::Scarfy()
{
}

Scarfy::~Scarfy()
{
}


void Scarfy::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);
	ResourcesManager::GetInst().SpriteFileLoad("Right_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);

	MainRenderer->CreateAnimation("Left_Idle", "Left_AerialEnemy.bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Right_Idle", "Right_AerialEnemy.bmp", 0, 1, 0.2f, true);

	MainRenderer->CreateAnimation("Left_TransFormingBefore", "Left_AerialEnemy.bmp", 0, 1, SCARFYWOBBLETIME, true);
	MainRenderer->CreateAnimation("Right_TransFormingBefore", "Right_AerialEnemy.bmp", 0, 1, SCARFYWOBBLETIME, true);

	MainRenderer->CreateAnimationToFrame("Left_TransFormingAfter", "Left_AerialEnemy.bmp", { 2 , 4 } , SCARFYWOBBLETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_TransFormingAfter", "Right_AerialEnemy.bmp", { 2 , 4 } , SCARFYWOBBLETIME, true);

	MainRenderer->CreateAnimation("Left_Following", "Left_AerialEnemy.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Following", "Right_AerialEnemy.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Left_Bomb", "Left_AerialEnemy.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Bomb", "Right_AerialEnemy.bmp", 2, 5, 0.1f, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Scarfy::init(const std::string& _FileName, ScarfyState _State, const float4& _Pos)
{

	Attribute = AttributeType::None;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	SetPos(RespawnLocation);
	ChangeState(_State);
}


void Scarfy::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}


void Scarfy::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ScarfyState::Idle:					return IdleUpdate(_Delta);
	case ScarfyState::TransFormingBefore:	return TransFormingBeforeUpdate(_Delta);
	case ScarfyState::TransFormingAfter:	return TransFormingAfterUpdate(_Delta);
	case ScarfyState::Following:			return FollowingUpdate(_Delta);
	case ScarfyState::Bomb:					return BombUpdate(_Delta);
	default:
		break;
	}
}

void Scarfy::ChangeState(ScarfyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case ScarfyState::Idle:					IdleStart();					break;
		case ScarfyState::TransFormingBefore:	TransFormingBeforeStart();		break;
		case ScarfyState::TransFormingAfter:	TransFormingAfterStart();		break;
		case ScarfyState::Following:			FollowingStart();				break;
		case ScarfyState::Bomb:					BombStart();					break;
		default:
			break;
		}
	}

	State = _State;
}




void Scarfy::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsGravityReverse = false;
	ChangeGravityDistance = RespawnLocation.Y + SCARFYFLIGHTCHANGRAVITYCONVERSIONPOINT;
	GravityReset();
	ChangeAnimationState("Idle");
}

void Scarfy::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	GetKirbyDirection();

	if (GetPos().Y > ChangeGravityDistance && false == IsGravityReverse)
	{
		IsGravityReverse = true;
	}
	else if (GetPos().Y < ChangeGravityDistance && true == IsGravityReverse)
	{
		IsGravityReverse = false;
	}

	if (SCARFYRECOGNITIONRANGE > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(ScarfyState::TransFormingBefore);
		return;
	}

	if (true == IsGravityReverse)
	{
		ReverseGravity(_Delta);
	}
	else if (false == IsGravityReverse)
	{
		Gravity(_Delta);
	}

	VerticalUpdate(_Delta);
}


void Scarfy::TransFormingBeforeStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	GravityReset();
	ChangeAnimationState("TransFormingBefore");
}

void Scarfy::TransFormingBeforeUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SCARFYWOBBLETIME)
	{
		StateTime = 0.0f;
		++WobbleCount;
		if (1 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::RIGHT * 12.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::LEFT * 12.0f);
			}
		}
		else if (0 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::LEFT * 6.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::RIGHT * 6.0f);
			}
		}
	}

	if (6 == WobbleCount)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(ScarfyState::TransFormingAfter);
		return;
	}
}


void Scarfy::TransFormingAfterStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	GravityReset();
	ChangeAnimationState("TransFormingAfter");
}

void Scarfy::TransFormingAfterUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SCARFYWOBBLETIME)
	{
		StateTime = 0.0f;
		++WobbleCount;
		if (1 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::RIGHT * 12.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::LEFT * 12.0f);
			}
		}
		else if (0 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::LEFT * 6.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::RIGHT * 6.0f);
			}
		} 
	}

	if (10 == WobbleCount)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(ScarfyState::Following);
		return;
	}
}


void Scarfy::FollowingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("Following");
}

void Scarfy::FollowingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (SCARFYRECOGNITIONRANGE > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X) || StateTime > SCARFYFOLLOWINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(ScarfyState::Bomb);
		return;
	}

	float4 KirbyUnitVector = GetKirbyUnitVector();
	KirbyUnitVector *= SCARFYFOLLOWINGSPEED;

	AddPos(KirbyUnitVector * _Delta);
}


void Scarfy::BombStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BombCount = 0;
	ChangeAnimationState("Bomb");
}

void Scarfy::BombUpdate(float _Delta)
{
	StateTime += _Delta;


	if (StateTime >= SCARFYVIBRATIONTIME)
	{
		StateTime = 0.0f;

		++BombCount;
		if (1 == BombCount % 2)
		{
			AddPos(float4::UP * SCARFYVIBRATIONDISTANCE);
		}
		else if (0 == BombCount % 2)
		{
			AddPos(float4::DOWN * SCARFYVIBRATIONDISTANCE);
		}
	}

	if (30 == BombCount)
	{
		// effect
		ChangeState(ScarfyState::Idle);
		Off();
		return;
	}
}

