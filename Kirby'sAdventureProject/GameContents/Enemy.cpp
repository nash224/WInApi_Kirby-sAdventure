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





// 커비를 바라보는 함수
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

// 커비 방향의 단위벡터를 반환
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

// 몬스터와 커비 사이의 거리를 반환
float4 Enemy::GetKirbyOpponentDistance()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return float4::ZERO;
	}

	float4 OpponentDistance = KirbyPtr->GetPos() - GetPos();
	return OpponentDistance;
}



float4 Enemy::KirbyActorCameraPos()
{
	static float4 ReturnValue;

	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return ReturnValue;
	}

	float4 KirbyPos = KirbyPtr->GetPos();

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return ReturnValue;
	}

	GameEngineCamera* MainCameraPtr = CurLevelPtr->GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return ReturnValue;
	}

	float4 CameraPos = MainCameraPtr->GetPos();

	float4 KirbyActorCameraPos = KirbyPos - CameraPos;

	return KirbyActorCameraPos;
}



// 왼쪽 절벽을 확인함
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

// 오른쪽 절벽을 확인함
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





// 몬스터가가 카메라 밖으로 나가면 Off
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


// 리스폰 위치를 기준으로 화면 밖으로 나가면 부활가능
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


// 리스폰 부활 전체 트리거
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






// 커비를 바라보는 좌우 방향과 렌더러를 변경하는 함수
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
		MsgBoxAssert("몬스터의 리스폰 위치가 잘못 지정 되었습니다.");
		return;
	}
}


// 몬스터 방향을 기준으로 몬스터의 렌더러를 좌,우 애니메이션 변경 함수
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




// 커비에게 빨려가는 상태패턴
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
		MsgBoxAssert("플레이어를 불러오지 못했습니다.");
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




// 피해를 입은 상태패턴
void Enemy::HittedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	CurrentSpeed = 0.0f;
	IsHitted = true;




	CrossDeathEffect* CrossDeathEffectPtr = GetLevel()->CreateActor<CrossDeathEffect>(UpdateOrder::Ability);
	if (nullptr == CrossDeathEffectPtr)
	{
		MsgBoxAssert("액터가 Null 일리가 없어..");
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


void Enemy::EnemyDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	{
		std::string Text = "";
		Text += "현재 상태 : ";
		Text += CurState;
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "Dir : ";
		if (ActorDir::Left == Dir)
		{
			Text += "Left";
		}
		else if (ActorDir::Right == Dir)
		{
			Text += "Right";
		}
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	{
		std::string Text = "";
		Text += "Ability : ";
		switch (Ability)
		{
		case AbilityStar::Normal:
			Text += "Normal";
			break;
		case AbilityStar::Spark:
			Text += "Spark";
			break;
		case AbilityStar::Laser:
			Text += "Laser";
			break;
		case AbilityStar::Beam:
			Text += "Beam";
			break;
		case AbilityStar::Fire:
			Text += "Fire";
			break;
		case AbilityStar::Thorn:
			Text += "Thorn";
			break;
		case AbilityStar::Sword:
			Text += "Sword";
			break;
		case AbilityStar::Ice:
			Text += "Ice";
			break;
		case AbilityStar::UFO:
			break;
		case AbilityStar::Max:
			break;
		default:
			break;
		}
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}

	if (true == Gravitational_Influence)
	{
		std::string Text = "";
		Text += "GravityVector : ";
		Text += std::to_string(GetGravityVector().Y);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
	else if (false == Gravitational_Influence)
	{
		std::string Text = "";
		Text += "CurentVerticalSpeed : ";
		Text += std::to_string(CurentVerticalSpeed);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "X Speed : ";
		Text += std::to_string(CurrentSpeed);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}