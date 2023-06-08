#include "Kabu.h"
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

Kabu::Kabu()
{
}

Kabu::~Kabu()
{
}


void Kabu::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 4, 7, KABUIDLESPIN, true);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 4, 7, KABUIDLESPIN, true);
	
	MainRenderer->CreateAnimation("Left_Jump", "Left_NormalEnemy.bmp", 4, 7, KABUJUMPSPIN, true);
	MainRenderer->CreateAnimation("Right_Jump", "Right_NormalEnemy.bmp", 4, 7, KABUJUMPSPIN, true);

	MainRenderer->CreateAnimation("Left_Sit", "Left_NormalEnemy.bmp", 18, 18, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Sit", "Right_NormalEnemy.bmp", 18, 18, 0.5f, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(NormalState::Idle);

	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Kabu::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}


void Kabu::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("Idle");

}

void Kabu::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= KABUCHANGETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Sit);
		return; 
	}

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void Kabu::SitStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Sit");
}

void Kabu::SitUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= KABUSITTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Jump);
		return; 
	}

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void Kabu::JumpStart()
{
	StateTime = 0.0f;
	CurrentSpeed = 0.0f;
	CurrentJumpDistance = 0.0f;
	JumpRatio = 1.0f;
	IsChangeState = false;
	AbleJump = true;

	int RatioNumber = GameEngineRandom::MainRandom.RandomInt(0,2);
	JumpRatio += static_cast<float>(RatioNumber) * 0.5f;

	GetKirbyDirection();
	GravityReset();
	ChangeAnimationState("Jump");
}

void Kabu::JumpUpdate(float _Delta)
{
	if (true == CeilingCheck())
	{
		GravityReset();
		IsChangeState = true;
		AbleJump = false;
	}

	if (GetGravityVector().Y > 0.0f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(NormalState::Idle);
		return;
	}


	if (true == AbleJump)
	{
		float JumpPower = KABUJUMPDISTANCE / KABUJUMPTIME;
		CurrentJumpDistance += JumpPower * _Delta;
	}

	if (CurrentJumpDistance > KABUJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (true == AbleJump)
	{
		SetGravityVector(float4::UP * CurrentJumpDistance);
	}

	// 버그수정
	if (false == IsChangeState)
	{
		if (ActorDir::Left == Dir)
		{
			CurrentSpeed -= KABUSPEED * _Delta;
		}
		if (ActorDir::Right == Dir)
		{
			CurrentSpeed += KABUSPEED * _Delta;
		}
	}

	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Right_Jump");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Left_Jump");
	}


	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);

	if (true == IsChangeState)
	{
		DecelerationUpdate(KABUDECELERATIONSPEED, _Delta);
	}
	HorizontalSpeedLimit(KABUMAXSPEED);
	HorizontalUpdate(_Delta);
}
