#include "Enemy.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Kirby.h"
#include "PlayUI.h"
#include "CrossDeathEffect.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy() 
{
}





// Ŀ�� �ٶ󺸴� �Լ�
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

// Ŀ�� ������ �������͸� ��ȯ
float4 Enemy::GetKirbyUnitVector()
{
	if (nullptr == Kirby::GetMainKirby())
	{
		MsgBoxAssert("Ŀ�� ������ �������� �ʽ��ϴ�.");
		return float4::ZERO;
	}

	float4 StartDir = Kirby::GetMainKirby()->GetPos() - GetPos();
	StartDir.Normalize();
	return StartDir;
}

// ���Ϳ� Ŀ�� ������ �Ÿ��� ��ȯ
float4 Enemy::GetKirbyOpponentDistance()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Ŀ�� �ҷ����� ���߽��ϴ�.");
		return float4::ZERO;
	}

	float4 OpponentDistance = KirbyPtr->GetPos() - GetPos();
	return OpponentDistance;
}


// ���� ������ Ȯ����
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

// ������ ������ Ȯ����
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





// ���Ͱ��� ī�޶� ������ ������ Off
void Enemy::CheckOverScreen()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	if (CameraPos.X > GetPos().X + CHECKOVERSCREENGAP || CameraPos.X + WinScale.X < GetPos().X - CHECKOVERSCREENGAP
		|| CameraPos.Y > GetPos().Y + CHECKOVERSCREENGAP || CameraPos.Y + WinScale.Y < GetPos().Y - CHECKOVERSCREENGAP)
	{
		Off(); 
	}
}


// ������ ��ġ�� �������� ȭ�� ������ ������ ��Ȱ����
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


// ������ ��Ȱ ��ü Ʈ����
void Enemy::RespawnTrigger()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	float4 KirbyPos = Kirby::GetMainKirby()->GetKirbyMovePos();

	RespawnLocationOverCamera();
	if (CameraPos.X + WinScale.X + KirbyPos.X >= RespawnLocation.X &&
		CameraPos.X + KirbyPos.X <= RespawnLocation.X &&
		CameraPos.Y + KirbyPos.Y <= RespawnLocation.Y &&
		CameraPos.Y + WinScale.Y + KirbyPos.Y >= RespawnLocation.Y)
	{
		if (true == IsRespawnLocationOverCamera && false == IsUpdate())
		{
			ChangeRespawnState();
			On();
			SetPos(RespawnLocation);
			SetDirectionAndFirstAnimation(StringRespawnState);
		}
	}
	CheckOverScreen();
}






// Ŀ�� �ٶ󺸴� �¿� ����� �������� �����ϴ� �Լ�
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
		MsgBoxAssert("������ ������ ��ġ�� �߸� ���� �Ǿ����ϴ�.");
		return;
	}
}


// ���� ������ �������� ������ �������� ��,�� �ִϸ��̼� ���� �Լ�
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




// Ŀ�񿡰� �������� ��������
void Enemy::BeInhaledStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	CurrentSpeed = 0.0f;

	IsInhaledStateOn = false;
	BodyCollision->Off();
	ActorDirUnitVector = GetKirbyOpponentDistance();

	MyInhaledStartPos = GetPos();


	if ("Pengi" != GetName())
	{
		PlayUI::PlayUI_Score += 300;
	}
}

void Enemy::BeInhaledUpdate(float _Delta)
{
	StateTime += _Delta;

	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("�÷��̾ �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 KirbyPos = KirbyPtr->GetPos();

	InhaleTargetPos = KirbyPos - MyInhaledStartPos;
	InhaleTargetPosXDistance = InhaleTargetPos.X;
	InhaleTargetPosYDistance = InhaleTargetPos.Y;
	Inhaled_Initial_YDistance = GetKirbyOpponentDistance().Y - Enemy_KIRBYCENTERYPOINT;


	// Y Speed Measurement
	{
		YDecelationSpeed += InhaleTargetPosYDistance / InhaledTime * _Delta;
		CurentVerticalSpeed = Inhaled_Initial_YDistance + YDecelationSpeed;

		VerticalUpdateBasedlevitation(_Delta);
	}


	if (ActorDirUnitVector.X < 0.0f)
	{
		InhaleXSpeed = InhaleTargetPosXDistance / InhaledTime * _Delta;
		CurrentSpeed += InhaleXSpeed;

		HorizontalUpdate(_Delta);

		if (GetPos().X < KirbyPos.X)
		{
			BeInhaledRelease();
			return;
		}
	}
	else if (ActorDirUnitVector.X > 0.0f)
	{
		InhaleXSpeed = InhaleTargetPosXDistance / InhaledTime * _Delta;
		CurrentSpeed += InhaleXSpeed;
		
		HorizontalUpdate(_Delta);

		if (GetPos().X > KirbyPos.X)
		{
			BeInhaledRelease();
			return;
		}
	}

}


void Enemy::BeInhaledRelease()
{
	BodyCollision->On();
	Off();
}




// ���ظ� ���� ��������
void Enemy::HittedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	CurrentSpeed = 0.0f;
	IsHitted = true;




	CrossDeathEffect* CrossDeathEffectPtr = GetLevel()->CreateActor<CrossDeathEffect>(UpdateOrder::Ability);
	if (nullptr == CrossDeathEffectPtr)
	{
		MsgBoxAssert("���Ͱ� Null �ϸ��� ����..");
		return;
	}

	CrossDeathEffectPtr->init(GetPos(), Scale);




	PlayUI::PlayUI_Score += 200;

	GameEngineSound::SoundPlay("Enemy_DeathSound.wav");

}

void Enemy::HittedUpdate(float _Delta)
{
	IsHitted = false;
	Off();
}





void Enemy::EnemyPointerRelease()
{
	if (nullptr != MainRenderer)
	{
		MainRenderer = nullptr;
	}
	if (nullptr != BodyCollision)
	{
		BodyCollision = nullptr;
	}
	if (nullptr != GroundTexture)
	{
		GroundTexture = nullptr;
	}
}