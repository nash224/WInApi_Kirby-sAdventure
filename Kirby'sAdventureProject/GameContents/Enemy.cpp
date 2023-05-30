#include "Enemy.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Kirby.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy() 
{
}



void Enemy::MoveHorizontal(float _Speed, float _Delta)
{
	if (Dir == ActorDir::Left)
	{
		CurrentSpeed -= _Speed * _Delta;
	}
	else if (Dir == ActorDir::Right)
	{
		CurrentSpeed += _Speed * _Delta;
	}
}

void Enemy::DecelerationUpdate(float _Speed, float _Delta)
{
	if (CurrentSpeed < 0.0f)
	{
		CurrentSpeed += _Speed * _Delta;

		if (CurrentSpeed > 0.0f)
		{
			CurrentSpeed = 0.0f;
		}
	}
	else if (CurrentSpeed > 0.0f)
	{
		CurrentSpeed -= _Speed * _Delta;

		if (CurrentSpeed < 0.0f)
		{
			CurrentSpeed = 0.0f;
		}
	}
}

void Enemy::MoveUpdate(float _MaxSpeed, float _Delta)
{
	if ((CurrentSpeed > _MaxSpeed * _Delta || CurrentSpeed < -_MaxSpeed * _Delta))
	{
		if (CurrentSpeed <= -_MaxSpeed * _Delta)
		{
			CurrentSpeed = -_MaxSpeed * _Delta;
		}

		if (CurrentSpeed >= _MaxSpeed * _Delta)
		{
			CurrentSpeed = _MaxSpeed * _Delta;
		}
	}

	AddPos({ CurrentSpeed, 0.0f });
}


void Enemy::CheckOverScreen()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	if (CameraPos.X > GetPos().X + Scale.X * 3.0f || CameraPos.X + WinScale.X < GetPos().X - Scale.X * 3.0f
		|| CameraPos.Y > GetPos().Y + Scale.X * 3.0f || CameraPos.Y + WinScale.Y < GetPos().Y - Scale.X * 3.0f)
	{
		Off();
	}
}