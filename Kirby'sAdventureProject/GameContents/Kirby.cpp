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
	MainRenderer = CreateRenderer(RenderOrder::Play);

	Normal_StateResourceLoad();
	Contain_StateResourceLoad();


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	{// 커비등장위치 Level로 이동 예정
		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		SetPos(WinScale.Half());
	}

	Dir = ActorDir::Right;
	BodyState = KirbyBodyState::Little;
	Mode = KirbyMode::Normal;
	CurMode = "Normal";


	ChangeState(KirbyState::Idle);
	SetCheckPoint(GetKirbyScale());

	LittleCollision = CreateCollision(CollisionOrder::PlayerBody);
	LittleCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.Half().Y });
	LittleCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	LittleCollision->SetCollisionType(CollisionType::Rect);
	LittleCollision->On();

	LowerCollision = CreateCollision(CollisionOrder::PlayerBody);
	LowerCollision->SetCollisionPos(float4{ 0.0f , -LOWERTYPECOLLISIONSCALE.Half().Y });
	LowerCollision->SetCollisionScale(LOWERTYPECOLLISIONSCALE);
	LowerCollision->SetCollisionType(CollisionType::Rect);
	LowerCollision->Off();

	FatCollision = CreateCollision(CollisionOrder::PlayerBody);
	FatCollision->SetCollisionPos(float4{ 0.0f , -FATTYPECOLLISIONSCALE.Half().Y });
	FatCollision->SetCollisionScale(FATTYPECOLLISIONSCALE);
	FatCollision->SetCollisionType(CollisionType::Rect);
	FatCollision->Off();


	LowerAttackCollision = CreateCollision(CollisionOrder::PlayerAbility);
	LowerAttackCollision->SetCollisionScale(LOWERATTACKCOLLISIONSCALE);
	LowerAttackCollision->SetCollisionType(CollisionType::Rect);
	LowerAttackCollision->Off();
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


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

	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != KirbyMode::Normal)
	{
		DropAbility();
	}

	if (true == GameEngineInput::IsDown('Y'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	{
		if (true == GameEngineInput::IsDown('L'))
		{
			Grunt::AllMonsterDeath();
		}
	}

	StateUpdate(_Delta);

	CameraFocus();
}

void Kirby::StateUpdate(float _Delta)
{
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
	case KirbyState::GetAbility:			return GetAbilityUpdate(_Delta);
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
	default:
		break;
	}
}

void Kirby::ChangeState(KirbyState _State)
{
	if (_State != State)
	{
		SetCheckPoint(GetKirbyScale());

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
		case KirbyState::GetAbility:			GetAbilityStart();				break;
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
		default:
			break;
		}
	}

	State = _State;
}


void Kirby::ChangeAnimationState(const std::string& _StateName, int _StartFrame/* = 0*/)
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

	MainRenderer->ChangeAnimation(ModeName, _StartFrame);
}


// 판정 함수
/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

// 커비 방향체크
void Kirby::KirbyDirCheck()
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

// 커비 충돌 크기 및 상태 변경
void Kirby::ChangeKirbyBodyState(KirbyBodyState _BodyState)
{

	if (BodyState == _BodyState)
	{
		return;
	}

	BodyState = _BodyState;

	if (KirbyBodyState::Little == _BodyState)
	{
		LittleCollision->On();
		LowerCollision->Off();
		FatCollision->Off();
	}
	else if (KirbyBodyState::Lower == _BodyState)
	{
		LittleCollision->Off();
		LowerCollision->On();
		FatCollision->Off();
	}
	else if (KirbyBodyState::Fat == _BodyState)
	{
		LittleCollision->Off();
		LowerCollision->Off();
		FatCollision->On();
	}
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


// 이동 함수
/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


// 커비 X축 이동 로직
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

// 커비 고유 감속도
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
void Kirby::HorizontalUpdate(float _Delta)
{
	if (State == KirbyState::Fly || State == KirbyState::TakeOff || State == KirbyState::ExhaleAttack)
	{
		if (CurrentSpeed <= -FLYMAXSPEED)
		{
			CurrentSpeed = -FLYMAXSPEED;
		}

		if (CurrentSpeed >= FLYMAXSPEED)
		{
			CurrentSpeed = FLYMAXSPEED;
		}
	}
	else if (State == KirbyState::Run || State == KirbyState::Contain_Run || State == KirbyState::LowerAttack)
	{
		if (CurrentSpeed <= -RUNMAXSPEED)
		{
			CurrentSpeed = -RUNMAXSPEED;
		}

		if (CurrentSpeed >= RUNMAXSPEED)
		{
			CurrentSpeed = RUNMAXSPEED;
		}
	}
	else if ((CurrentSpeed > WALKMAXSPEED || CurrentSpeed < -WALKMAXSPEED))
	{
		if (CurrentSpeed <= -WALKMAXSPEED)
		{
			CurrentSpeed = -WALKMAXSPEED;
		}

		if (CurrentSpeed >= WALKMAXSPEED)
		{
			CurrentSpeed = WALKMAXSPEED;
		}
	}

	AddPos({ CurrentSpeed * _Delta, 0.0f});
}


// 레벨 함수
/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

// 몹의 패턴에서 쓰일 커비 객체
void Kirby::LevelStart()
{
	MainKirby = this;
}


void Kirby::Render(float _Detla)
{
	ActorCollisionDetectionPointRender();
}