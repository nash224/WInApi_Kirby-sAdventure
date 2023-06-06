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

	ResourcesManager::GetInst().SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 16, 16, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 16, 16, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Walk", "Left_NormalEnemy.bmp", 16, 17, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_NormalEnemy.bmp", 16, 17, 0.5f, true);

	MainRenderer->CreateAnimation("Left_Jump", "Left_NormalEnemy.bmp", 17, 17, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Jump", "Right_NormalEnemy.bmp", 17, 17, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Fall", "Left_NormalEnemy.bmp", 16, 17, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Fall", "Right_NormalEnemy.bmp", 16, 17, 0.5f, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(ScarfyState::Idle);


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
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
	case ScarfyState::Fly:					return FlyUpdate(_Delta);
	case ScarfyState::WaveFlight:			return WaveFlightUpdate(_Delta);
	case ScarfyState::Exit:					return ExitUpdate(_Delta);
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
		case ScarfyState::Fly:					FlyStart();						break;
		case ScarfyState::WaveFlight:			WaveFlightStart();				break;
		case ScarfyState::Exit:					ExitStart();					break;
		default:
			break;
		}
	}

	State = _State;
}



void Scarfy::IdleStart()
{

}

void Scarfy::IdleUpdate(float _Delta)
{

}

void Scarfy::FlyStart()
{

}

void Scarfy::FlyUpdate(float _Delta)
{

}

void Scarfy::WaveFlightStart()
{

}

void Scarfy::WaveFlightUpdate(float _Delta)
{

}

void Scarfy::ExitStart()
{

}

void Scarfy::ExitUpdate(float _Delta)
{

}

