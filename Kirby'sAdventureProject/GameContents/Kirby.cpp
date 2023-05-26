#include "Kirby.h"
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

#include "Grunt.h"
#include "Projectile.h"

#include <Windows.h>


Kirby* Kirby::MainKirby = nullptr;


Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::Start()
{
	// 비트맵 파일이 없으면 하나 만들어줘야한다.

	ResourcesManager::GetInst().SpriteFileLoad("Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	ResourcesManager::GetInst().SpriteFileLoad("Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	MainRenderer = CreateRenderer(RenderOrder::Play);


	MainRenderer->CreateAnimation("Left_Idle", "Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Idle", "RIght_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Left_Walk", "Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Right_Walk", "RIght_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Left_Run", "Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Run", "RIght_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Left_Turn", "Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Right_Turn", "RIght_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Left_Jump", "Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Jump", "Right_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Left_AerialMotion", "Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Right_AerialMotion", "Right_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Left_Fall", "Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Fall", "Right_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Left_AccelerateDown", "Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Right_AccelerateDown", "Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Bounce", "Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Bounce", "Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Landing", "Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Landing", "Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Left_LowerPosture", "Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Right_LowerPosture", "Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Left_LowerAttack", "Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Right_LowerAttack", "Right_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Left_HittheWall", "Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Right_HittheWall", "Right_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Left_HittheCeiling", "Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Right_HittheCeiling", "Right_Kirby.bmp", 91, 91, 0.1f, false);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);
	
	MainRenderer->FindAnimation("Left_Idle")->Inters = { 2.5f, 0.1f };
	MainRenderer->FindAnimation("Right_Idle")->Inters = { 2.5f, 0.1f };



	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.Half());

	Dir = ActorDir::Right;
	ChangeState(KirbyState::Idle);
	BodyState = KirbyBodyState::Little;


	BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
	BodyCollision->SetCollisionScale(GetKirbyScale());
	BodyCollision->SetCollisionType(CollisionType::CirCle);
}

void Kirby::Update(float _Delta)
{
	//std::vector<GameEngineCollision*> _Col;
	//if (true == BodyCollision->Collision(CollisionOrder::MonsterBody, _Col
	//	, CollisionType::CirCle
	//	, CollisionType::CirCle))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collision = _Col[i];
	//		GameEngineActor* Actor = Collision->GetActor();
	//		Actor->Death();
	//	}
	//}

	if (true == GameEngineInput::IsDown('Y'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown('L'))
	{
		Grunt::AllMonsterDeath();
	}

	StateUpdate(_Delta);

	CameraFocus();
}

void Kirby::StateUpdate(float _Delta)
{
	SetCheckPoint(GetKirbyScale());
	GroundCheck();

	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::Walk:
		return WalkUpdate(_Delta);
	case KirbyState::Run:
		return RunUpdate(_Delta);
	case KirbyState::Turn:
		return TurnUpdate(_Delta);
	case KirbyState::Jump:
		return JumpUpdate(_Delta);
	case KirbyState::AerialMotion:
		return AerialMotionUpdate(_Delta);
	case KirbyState::Fall:
		return FallUpdate(_Delta);
	case KirbyState::AccelerateDown:
		return AccelerateDownUpdate(_Delta);
	case KirbyState::Bounce:
		return BounceUpdate(_Delta);
	case KirbyState::Landing:
		return LandingUpdate(_Delta);
	case KirbyState::LowerPosture:
		return LowerPostureUpdate(_Delta);
	case KirbyState::LowerAttack:
		return LowerAttackUpdate(_Delta);
	case KirbyState::HittheWall:
		return HittheWallUpdate(_Delta);
	case KirbyState::HittheCeiling:
		return HittheCeilingUpdate(_Delta);
	default:
		break;
	}
}

void Kirby::ChangeState(KirbyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case KirbyState::Idle:
			IdleStart();
			break;
		case KirbyState::Walk:
			WalkStart();
			break;
		case KirbyState::Run:
			RunStart();
			break;
		case KirbyState::Turn:
			TurnStart();
			break;
		case KirbyState::Jump:
			JumpStart();
			break;
		case KirbyState::AerialMotion:
			AerialMotionStart();
			break;
		case KirbyState::Fall:
			FallStart();
			break;
		case KirbyState::AccelerateDown:
			AccelerateDownStart();
			break;
		case KirbyState::Bounce:
			BounceStart();
			break;
		case KirbyState::Landing:
			LandingStart();
			break;
		case KirbyState::LowerPosture:
			LowerPostureStart();
			break;
		case KirbyState::LowerAttack:
			LowerAttackStart();
			break;
		case KirbyState::HittheWall:
			HittheWallStart();
			break;
		case KirbyState::HittheCeiling:
			HittheCeilingStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Kirby::DirCheck()
{
	ActorDir CheckDir = ActorDir::Max;

	if (true == GameEngineInput::IsPress('A') &&
		true == GameEngineInput::IsPress('D'))
	{
		return;
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		CheckDir = ActorDir::Left;
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		CheckDir = ActorDir::Right;
	}


	if (CheckDir != ActorDir::Max)
	{
		Dir = CheckDir;
	}
}


void Kirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "";

	switch (Dir)
	{
	case ActorDir::Right:
		AnimationName = "Right_";
		break;
	case ActorDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}


// 발끝 중앙 기준
float4 Kirby::GetKirbyScale()
{
	if (BodyState == KirbyBodyState::Little)
	{
		return float4{ 24.0f, 48.0f };
	}

	if (BodyState == KirbyBodyState::Fat)
	{
		return float4{ 33.0f, 63.0f };
	}

	return float4{ 0.0f, 0.0f };
}

void Kirby::MoveHorizontal(float _Speed, float _Delta)
{
	if (true == GameEngineInput::IsPress('A') && false == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Left;
		CurrentSpeed -= _Speed * _Delta;
	}
	else if (false == GameEngineInput::IsPress('A') && true == GameEngineInput::IsPress('D'))
	{
		Dir = ActorDir::Right;
		CurrentSpeed += _Speed * _Delta;
	}
}

void Kirby::DecelerationUpdate(float _Delta)
{
	if ((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) || (GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D')))
	{
		if (CurrentSpeed < 0.0f)
		{
			CurrentSpeed += DECELERATIONSPEED * _Delta;

			if (CurrentSpeed > 0.0f)
			{
				CurrentSpeed = 0.0f;
			}
		}
		else if (CurrentSpeed > 0.0f)
		{
			CurrentSpeed -= DECELERATIONSPEED * _Delta;

			if (CurrentSpeed < 0.0f)
			{
				CurrentSpeed = 0.0f;
			}
		}
	}
}

// 커비의 위치 동기화
void Kirby::MoveUpdate(float _Delta)
{// 좌우의 속도가 다른 버그가 있음

	if (CurrentSpeed > WALKMAXSPEED * _Delta || State == KirbyState::Run)
	{
		if (CurrentSpeed <= -RUNMAXSPEED * _Delta)
		{
			CurrentSpeed = -RUNMAXSPEED * _Delta;
		}

		if (CurrentSpeed >= RUNMAXSPEED * _Delta)
		{
			CurrentSpeed = RUNMAXSPEED * _Delta;
		}
	}
	else if (CurrentSpeed <= WALKMAXSPEED * _Delta)
	{
		if (CurrentSpeed <= -WALKMAXSPEED * _Delta)
		{
			CurrentSpeed = -WALKMAXSPEED * _Delta;
		}

		if (CurrentSpeed >= WALKMAXSPEED * _Delta)
		{
			CurrentSpeed = WALKMAXSPEED * _Delta;
		}
	}

	AddPos({ CurrentSpeed, 0.0f});
}

void Kirby::BlockedByWall()
{
	if (true == CheckLeftWallBasedSpeed() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWallBasedSpeed() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
	}

	{
		unsigned int BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint + float4{ CHECKGAP , 0.0f });
		unsigned int TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint + float4{ CHECKGAP , 0.0f });

		if ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
		{
			while ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
			{
				BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint + float4{ CHECKGAP , 0.0f });
				TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint + float4{ CHECKGAP , 0.0f });
				AddPos(float4::RIGHT * 3);
			}
		}
	}

	{
		unsigned int BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint + float4{ -CHECKGAP , 0.0f });
		unsigned int TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint + float4{ -CHECKGAP , 0.0f });

		if ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
		{
			while ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
			{
				BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint + float4{ -CHECKGAP , 0.0f });
				TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint + float4{ -CHECKGAP , 0.0f });
				AddPos(float4::LEFT * 3);
			}
		}
	}
}

void Kirby::BlockedByGround()
{
	unsigned int LeftGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint + float4{ CHECKGAP , -CHECKGAP });
	unsigned int RightGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint + float4{ -CHECKGAP , -CHECKGAP });

	if ((LeftGroundCheckColor == RGB(0, 255, 255)) || (RightGroundCheckColor == RGB(0, 255, 255)))
	{
		while ((LeftGroundCheckColor == RGB(0, 255, 255)) || (RightGroundCheckColor == RGB(0, 255, 255)))
		{
			LeftGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint + float4{ CHECKGAP , -CHECKGAP });
			RightGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint + float4{ -CHECKGAP , -CHECKGAP });
			AddPos(float4::UP * 3);
		}
	}
}

void Kirby::BlockedByCeiling()
{
	unsigned int LeftCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint + float4{ CHECKGAP , CHECKGAP });
	unsigned int RightCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint + float4{ -CHECKGAP , CHECKGAP });

	if ((LeftCeilingCheckColor == RGB(0, 255, 255)) || (RightCeilingCheckColor == RGB(0, 255, 255)))
	{
		while ((LeftCeilingCheckColor == RGB(0, 255, 255)) || (RightCeilingCheckColor == RGB(0, 255, 255)))
		{
			LeftCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint + float4{ CHECKGAP , CHECKGAP });
			RightCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint + float4{ -CHECKGAP , CHECKGAP });
			AddPos(float4::UP * 3);
		}
	}
}


void Kirby::LevelStart()
{
	MainKirby = this;
}


void Kirby::Render(float _Detla)
{
	//std::string Text = "";
	//Text += "플레이어 테스트 값 : ";
	//Text += std::to_string();

	HDC BackDC = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	float4 KirbyScale = GetKirbyScale();

	// 커비 원점
	Data.Pos = ActorCameraPos();
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 바닥 왼쪽
	Data.Pos = ActorCameraPos() + GroundLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 바닥 오른쪽
	Data.Pos = ActorCameraPos() + GroundRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 하단왼쪽
	Data.Pos = ActorCameraPos() + WallBotLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 상단왼쪽
	Data.Pos = ActorCameraPos() + WallTopLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 하단오른쪽
	Data.Pos = ActorCameraPos() + WallBotRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 상단오른쪽
	Data.Pos = ActorCameraPos() + WallTopRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 천장 왼쪽
	Data.Pos = ActorCameraPos() + CeilLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 천장 오른쪽
	Data.Pos = ActorCameraPos() + CeilRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}