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

	MainRenderer->CreateAnimation("Left_Rise", "Left_AerialEnemy.bmp", 6, 7, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Rise", "Right_AerialEnemy.bmp", 6, 7, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Fly", "Left_AerialEnemy.bmp", 6, 7, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Fly", "Right_AerialEnemy.bmp", 6, 7, 0.5f, true);

	MainRenderer->CreateAnimation("Left_WaveFlight", "Left_AerialEnemy.bmp", 6, 7, 0.5f, false);
	MainRenderer->CreateAnimation("Right_WaveFlight", "Right_AerialEnemy.bmp", 6, 7, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Fall", "Left_AerialEnemy.bmp", 6, 6, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Fall", "Right_AerialEnemy.bmp", 6, 6, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Exit", "Left_AerialEnemy.bmp", 6, 7, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Exit", "Right_AerialEnemy.bmp", 6, 7, 0.5f, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(BrontoState::Idle);


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void BrontoBurt::Update(float _Delta)
{
	GroundCheck();

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
	case BrontoState::WaveFlight:			return WaveFlightUpdate(_Delta);
	case BrontoState::Fall:					return FallUpdate(_Delta);
	case BrontoState::Exit:					return ExitUpdate(_Delta);
	default:
		break;
	}
}

void BrontoBurt::ChangeState(BrontoState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BrontoState::Idle:					IdleStart();					break;
		case BrontoState::Rise:					RiseStart();					break;
		case BrontoState::Fly:					FlyStart();						break;
		case BrontoState::WaveFlight:			WaveFlightStart();				break;
		case BrontoState::Fall:					FallStart();					break;
		case BrontoState::Exit:					ExitStart();					break;
		default:
			break;
		}
	}

	State = _State;
}



void BrontoBurt::IdleStart()
{

}

void BrontoBurt::IdleUpdate(float _Delta)
{

}


void BrontoBurt::RiseStart()
{

}

void BrontoBurt::RiseUpdate(float _Delta)
{

}


void BrontoBurt::FlyStart()
{

}

void BrontoBurt::FlyUpdate(float _Delta)
{

}


void BrontoBurt::WaveFlightStart()
{

}

void BrontoBurt::WaveFlightUpdate(float _Delta)
{

}


void BrontoBurt::FallStart()
{

}

void BrontoBurt::FallUpdate(float _Delta)
{

}


void BrontoBurt::ExitStart()
{

}

void BrontoBurt::ExitUpdate(float _Delta)
{

}

