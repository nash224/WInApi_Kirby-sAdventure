#include "Enemy.h"

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

