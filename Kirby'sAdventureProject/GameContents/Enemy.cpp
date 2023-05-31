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

bool Enemy::LeftGroundIsCliff()
{
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint);
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint);
	if (((RGB(0, 255, 255) != LeftBottomColor) && (RGB(0, 255, 255) == RightBottomColor))
		|| (RGB(0, 0, 255) != LeftBottomColor && (RGB(0, 0, 255) == RightBottomColor)))
	{
		return true;
	}

	return false;
}

bool Enemy::RightGroundIsCliff()
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

// 화면밖으로 나가면 TriggerOn
void Enemy::RespawnLocationOverCamera()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	if (RespawnLocation.X < CameraPos.X)
	{
		IsRespawnLocationOverCamera = true;
		return;
	}

	if (RespawnLocation.Y < CameraPos.Y)
	{
		IsRespawnLocationOverCamera = true;
		return;
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	if (RespawnLocation.X > CameraPos.X + WinScale.X)
	{
		IsRespawnLocationOverCamera = true;
		return;
	}

	if (RespawnLocation.Y > CameraPos.Y + WinScale.Y)
	{
		IsRespawnLocationOverCamera = true;
		return;
	}

	IsRespawnLocationOverCamera = false;
}


void Enemy::RespawnTrigger()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	RespawnLocationOverCamera();

	if (true == IsRespawnLocationOverCamera)
	{
		On();
		SetPos(RespawnLocation);
		SetDirectionAndFirstAnimation();
	}
}