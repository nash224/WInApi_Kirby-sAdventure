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
	for (const std::pair<KirbyMode, Kirby*>& Pair : AllMode)
	{
		Kirby* Modes = Pair.second;
		if (nullptr != Modes)
		{
			delete Modes;
			Modes = nullptr;
		}
	}

	if (nullptr != CurStar)
	{
		delete CurStar;
		CurStar = nullptr;
	}
}

Kirby::KirbyAbilityStar::KirbyAbilityStar(size_t _GruntCount, AbilityStar _StarAbility)
	:GruntCount(_GruntCount), StartAbility(_StarAbility)
{

}

Kirby::KirbyAbilityStar::~KirbyAbilityStar()
{

}



void Kirby::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Normal_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	ResourcesManager::GetInst().SpriteFileLoad("Normal_RIght_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	MainRenderer->CreateAnimation("Normal_Left_Idle", "Normal_Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Normal_Right_Idle", "Normal_RIght_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Normal_Left_Walk", "Normal_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Walk", "Normal_RIght_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Left_Run", "Normal_Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Normal_Right_Run", "Normal_RIght_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Normal_Left_Turn", "Normal_Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Normal_Right_Turn", "Normal_RIght_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Normal_Left_Jump", "Normal_Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Jump", "Normal_RIght_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_AerialMotion", "Normal_Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Normal_Right_AerialMotion", "Normal_RIght_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Normal_Left_Fall", "Normal_Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Fall", "Normal_RIght_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_AccelerateDown", "Normal_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_AccelerateDown", "Normal_RIght_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Bounce", "Normal_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Bounce", "Normal_RIght_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Landing", "Normal_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Landing", "Normal_RIght_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_LowerPosture", "Normal_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_LowerPosture", "Normal_RIght_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_LowerAttack", "Normal_Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_LowerAttack", "Normal_RIght_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_HittheWall", "Normal_Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_HittheWall", "Normal_RIght_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_HittheCeiling", "Normal_Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_HittheCeiling", "Normal_RIght_Kirby.bmp", 91, 91, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_TakeOff", "Normal_Left_Kirby.bmp", 15, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_TakeOff", "Normal_RIght_Kirby.bmp", 15, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Fly", "Normal_Left_Kirby.bmp", 19, 20, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Fly", "Normal_RIght_Kirby.bmp", 19, 20, 0.2f, true);
	 
	MainRenderer->CreateAnimation("Normal_Left_ExhaleAttack", "Normal_Left_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Normal_Right_ExhaleAttack", "Normal_RIght_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Normal_Left_UseSpecialAbility", "Normal_Left_Kirby.bmp", 24, 26, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_UseSpecialAbility", "Normal_RIght_Kirby.bmp", 24, 26, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_ReleaseAbility", "Normal_Left_Kirby.bmp", 25, 25, 0.15f, false);
	MainRenderer->CreateAnimation("Normal_Right_ReleaseAbility", "Normal_RIght_Kirby.bmp", 25, 25, 0.15f, false);

	Contain_StateResourceLoad();

	//MainRenderer->CreateAnimation("Normal_Left_GetAbility", "Normal_Left_Kirby.bmp", 24, 26, 0.1f, false);
	//MainRenderer->CreateAnimation("Normal_Right_GetAbility", "Normal_RIght_Kirby.bmp", 24, 26, 0.1f, false);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.Half());

	Dir = ActorDir::Right;
	ChangeState(KirbyState::Idle);
	BodyState = KirbyBodyState::Little;
	Mode = KirbyMode::Normal;

	CurMode = "Normal";
	

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
	case KirbyState::Idle:					return IdleUpdate(_Delta);
	case KirbyState::Walk:					return WalkUpdate(_Delta);
	case KirbyState::Run:					return RunUpdate(_Delta);
	case KirbyState::Turn:					return TurnUpdate(_Delta);
	case KirbyState::Jump:					return JumpUpdate(_Delta);
	case KirbyState::AerialMotion:			return AerialMotionUpdate(_Delta);
	case KirbyState::Fall:					return FallUpdate(_Delta);
	case KirbyState::AccelerateDown:		return AccelerateDownUpdate(_Delta);
	case KirbyState::Bounce:				return BounceUpdate(_Delta);
	case KirbyState::Landing:				return LandingUpdate(_Delta);
	case KirbyState::LowerPosture:			return LowerPostureUpdate(_Delta);
	case KirbyState::LowerAttack:			return LowerAttackUpdate(_Delta);
	case KirbyState::HittheWall:			return HittheWallUpdate(_Delta);
	case KirbyState::HittheCeiling:			return HittheCeilingUpdate(_Delta);
	case KirbyState::TakeOff:				return TakeOffUpdate(_Delta);
	case KirbyState::Fly:					return FlyUpdate(_Delta);
	case KirbyState::ExhaleAttack:			return ExhaleAttackUpdate(_Delta);
	case KirbyState::UseSpecialAbility:		return UseSpecialAbilityUpdate(_Delta);
	case KirbyState::ReleaseAbility:		return ReleaseAbilityUpdate(_Delta);
	case KirbyState::Contain_Idle:			return Contain_IdleUpdate(_Delta);
	case KirbyState::Contain_Walk:			return Contain_WalkUpdate(_Delta);
	case KirbyState::Contain_Run:			return Contain_RunUpdate(_Delta);
	case KirbyState::Contain_Turn:			return Contain_TurnUpdate(_Delta);
	case KirbyState::Contain_Jump:			return Contain_JumpUpdate(_Delta);
	case KirbyState::Contain_Fall:			return Contain_FallUpdate(_Delta);
	case KirbyState::Contain_Gulp:			return Contain_GulpUpdate(_Delta);
	case KirbyState::Contain_Disgorge:		return Contain_DisgorgeUpdate(_Delta);
	case KirbyState::GetAbility:			return GetAbilityUpdate(_Delta);
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
		case KirbyState::Idle:					IdleStart();					break;
		case KirbyState::Walk:					WalkStart();					break;
		case KirbyState::Run:					RunStart();						break;
		case KirbyState::Turn:					TurnStart();					break;
		case KirbyState::Jump:					JumpStart();					break;
		case KirbyState::AerialMotion:			AerialMotionStart();			break;
		case KirbyState::Fall:					FallStart();					break;
		case KirbyState::AccelerateDown:		AccelerateDownStart();			break;
		case KirbyState::Bounce:				BounceStart();					break;
		case KirbyState::Landing:				LandingStart();					break;
		case KirbyState::LowerPosture:			LowerPostureStart();			break;
		case KirbyState::LowerAttack:			LowerAttackStart();				break;
		case KirbyState::HittheWall:			HittheWallStart();				break;
		case KirbyState::HittheCeiling:			HittheCeilingStart();			break;
		case KirbyState::TakeOff:				TakeOffStart();					break;
		case KirbyState::Fly:					FlyStart();						break;
		case KirbyState::ExhaleAttack:			ExhaleAttackStart();			break;
		case KirbyState::UseSpecialAbility:		UseSpecialAbilityStart();		break;
		case KirbyState::ReleaseAbility:		ReleaseAbilityStart();			break;
		case KirbyState::Contain_Idle:			Contain_IdleStart();			break;
		case KirbyState::Contain_Walk:			Contain_WalkStart();			break;
		case KirbyState::Contain_Run:			Contain_RunStart();				break;
		case KirbyState::Contain_Turn:			Contain_TurnStart();			break;
		case KirbyState::Contain_Jump:			Contain_JumpStart();			break;
		case KirbyState::Contain_Fall:			Contain_FallStart();			break;
		case KirbyState::Contain_Gulp:			Contain_GulpStart();			break;
		case KirbyState::Contain_Disgorge:		Contain_DisgorgeStart();		break;
		case KirbyState::GetAbility:			GetAbilityStart();				break;
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
	std::string ModeName = "";

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

	switch (Mode)
	{
	case KirbyMode::Normal:
		ModeName = "Normal_";
		break;
	case KirbyMode::Spark:
		ModeName = "Spark_";
		break;
	case KirbyMode::Max:
		break;
	default:
		break;
	}

	ModeName += AnimationName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(ModeName);
}


// 발끝 중앙 기준
float4 Kirby::GetKirbyScale()
{
	if (BodyState == KirbyBodyState::Little)
	{
		return float4{ 24.0f, 39.0f };
	}

	if (BodyState == KirbyBodyState::Fat)
	{
		return float4{ 24.0f, 42.0f };
	}

	if (BodyState == KirbyBodyState::Lower)
	{
		return float4{ 24.0f, 21.0f };
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

void Kirby::DecelerationUpdate(float _Delta, float _Speed)
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

// 커비의 위치 동기화
void Kirby::MoveUpdate(float _Delta)
{
	if (State == KirbyState::Fly || State == KirbyState::TakeOff || State == KirbyState::ExhaleAttack)
	{
		if (CurrentSpeed <= -FLYMAXSPEED * _Delta)
		{
			CurrentSpeed = -FLYMAXSPEED * _Delta;
		}

		if (CurrentSpeed >= FLYMAXSPEED * _Delta)
		{
			CurrentSpeed = FLYMAXSPEED * _Delta;
		}
	}
	else if (State == KirbyState::Run || State == KirbyState::Contain_Run)
	{// 수정예정
		if (CurrentSpeed <= -RUNMAXSPEED * _Delta)
		{
			CurrentSpeed = -RUNMAXSPEED * _Delta;
		}

		if (CurrentSpeed >= RUNMAXSPEED * _Delta)
		{
			CurrentSpeed = RUNMAXSPEED * _Delta;
		}
	}
	else if ((CurrentSpeed > WALKMAXSPEED * _Delta || CurrentSpeed < -WALKMAXSPEED * _Delta))
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