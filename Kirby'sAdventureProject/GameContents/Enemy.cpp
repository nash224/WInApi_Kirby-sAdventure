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


void Enemy::ChangeAnimationState(const std::string& _StateName)
{

	std::string AnimationName = "";

	switch (Dir)
	{
	case ActorDir::Left:
		AnimationName = "Left_";
		break;
	case ActorDir::Right:
		AnimationName = "Right_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
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

void Enemy::GetKirbyDirection()
{
	if (nullptr == Kirby::GetMainKirby())
	{
		Dir = ActorDir::Left;
		return;
	}

	float4 StartDir = Kirby::GetMainKirby()->GetPos() - GetPos();

	if (StartDir.X < 0.0f)
	{
		Dir = ActorDir::Left;
	}
	else if (StartDir.X >= 0.0f)
	{
		Dir = ActorDir::Right;
	}
}

float4 Enemy::GetKirbyUnitVector()
{
	if (nullptr == Kirby::GetMainKirby())
	{
		MsgBoxAssert("커비가 레벨에 존재하지 않습니다.");
		return float4::ZERO;
	}

	float4 StartDir = Kirby::GetMainKirby()->GetPos() - GetPos();
	StartDir.Normalize();
	return StartDir;
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


void Enemy::RespawnTrigger(const std::string& _StateName)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	RespawnLocationOverCamera();
	if (true == IsRespawnLocationOverCamera)
	{
		On();
		SetPos(RespawnLocation);
		SetDirectionAndFirstAnimation(_StateName);
	}
}


void Enemy::SetDirectionAndFirstAnimation(const std::string& _StateName)
{
	if (nullptr == Kirby::GetMainKirby())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_" + _StateName);
		return;
	}

	float4 StartDir = Kirby::GetMainKirby()->GetPos() - GetPos();

	if (StartDir.X < 0.0f)
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_" + _StateName);
	}
	else if (StartDir.X >= 0.0f)
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_" + _StateName);
	}
	else
	{
		MsgBoxAssert("몬스터의 리스폰 위치가 잘못되었습니다.");
		return;
	}
}