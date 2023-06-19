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
#include "VegetableValleyPlayLevel.h"
#include "PlayUI.h"

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
	Spark_StateResourceLoad();
	Laser_StateResourceLoad();
	Beam_StateResourceLoad();
	Fire_StateResourceLoad();
	Thorn_StateResourceLoad();
	Contain_StateResourceLoad();

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	{// 커비등장위치 Level로 이동 예정
		float4 WinScale = GameEngineWindow::MainWindow.GetScale();
		SetPos(WinScale.Half());
	}

	Dir = ActorDir::Right;
	BodyState = KirbyBodyState::Little;
	Mode = AbilityStar::Normal;
	CurMode = "Normal";
	m_KirbyHp = 6;



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


	ImmuneCollision = CreateCollision(CollisionOrder::PlayerBody);
	ImmuneCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.Half().Y });
	ImmuneCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	ImmuneCollision->SetCollisionType(CollisionType::Rect);
	ImmuneCollision->Off();


	InhaleEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	InhaleEffectCollision->SetCollisionScale(INHALEEFFECTCOLLISIONSCALE);
	InhaleEffectCollision->SetCollisionType(CollisionType::Rect);
	InhaleEffectCollision->Off();

	
	SparkEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	SparkEffectCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.Half().Y });
	SparkEffectCollision->SetCollisionScale(SPARKEFFECTCOLLISIONSCALE);
	SparkEffectCollision->SetCollisionType(CollisionType::Rect);
	SparkEffectCollision->Off();


	ThornEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	ThornEffectCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.Half().Y });
	ThornEffectCollision->SetCollisionScale(SPARKEFFECTCOLLISIONSCALE);
	ThornEffectCollision->SetCollisionType(CollisionType::Rect);
	ThornEffectCollision->Off();
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void Kirby::Update(float _Delta)
{
	if (true == ImmuneState)
	{
		ImmuneTime += _Delta;
	}

	if (ImmuneTime > KIRBYIMMUNEDURATION)
	{
		ImmuneTime = 0.0f;
		ImmuneState = false;
		IsHitted = false;

		KirbyBodyCollisonOn();
	}

	if (true == IsGulpEnemy)
	{
		IsGulpEnemy = false;
	}



	if (true == GameEngineInput::IsDown('Y'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	PrevKirbyMovePos = GetPos();

	StateUpdate(_Delta);

	KirbyMovePos = GetPos() - PrevKirbyMovePos;



	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max)
	{
		DropAbility();
	}


	// 카메라
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
	case KirbyState::UseSpecialAbility:		return UseSpecialAbilityUpdate(_Delta);
	case KirbyState::ReleaseSpecialAbility:	return ReleaseSpecialAbilityUpdate(_Delta);
	case KirbyState::GetAbility:			return GetAbilityUpdate(_Delta);
	case KirbyState::Damaged:				return DamagedUpdate(_Delta);
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
		case KirbyState::UseSpecialAbility:		UseSpecialAbilityStart();		break;
		case KirbyState::ReleaseSpecialAbility:	ReleaseSpecialAbilityStart();	break;
		case KirbyState::GetAbility:			GetAbilityStart();				break;
		case KirbyState::Damaged:				DamagedStart();					break;
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
	case AbilityStar::Normal:
		ModeName = "Normal_";
		break;
	case AbilityStar::Spark:
		ModeName = "Spark_";
		break;
	case AbilityStar::Laser:
		ModeName = "Laser_";
		break;
	case AbilityStar::Beam:
		ModeName = "Beam_";
		break;
	case AbilityStar::Fire:
		ModeName = "Fire_";
		break;
	case AbilityStar::Thorn:
		ModeName = "Thorn_";
		break;
	case AbilityStar::Sword:
		ModeName = "Sword_";
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


GameEngineCollision* Kirby::GetKirbyCollison()
{
	if (BodyState == KirbyBodyState::Little)
	{
		return LittleCollision;
	}

	if (BodyState == KirbyBodyState::Fat)
	{
		return FatCollision;
	}

	if (BodyState == KirbyBodyState::Lower)
	{
		return LowerCollision;
	}

	MsgBoxAssert("커비 충돌체 리턴에 실패했습니다.");
	return BodyCollision;
}



void Kirby::KirbyBodyCollisonOn()
{
	if (BodyState == KirbyBodyState::Little)
	{
		LittleCollision->On();
	}

	if (BodyState == KirbyBodyState::Fat)
	{
		FatCollision->On();
	}

	if (BodyState == KirbyBodyState::Lower)
	{
		LowerCollision->On();
	}

	ImmuneCollision->Off();
}


void Kirby::KirbyBodyCollisonOff()
{
	LittleCollision->Off();
	FatCollision->Off();
	LowerCollision->Off();
	ImmuneCollision->On();
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


void Kirby::VerticalUpdate(float _Delta)
{
	AddPos(GetGravityVector() * _Delta);
}


// 레벨 함수
/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

/*
* 1. 밖으로 나가지 못해야한다.
* 
* 
*/
void Kirby::CameraFocus()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	CameraFrontCheckPos = CameraPos;
	CameraBackCheckPos = float4{ CameraPos.X + WinScale.X , CameraPos.Y + WinScale.Y - CurrentUIScale.Y };

	float4 CameraMovePos = KirbyMovePos;

	// 커비가 오른쪽 방향일 때, 화면의 중앙을 넘어가면 움직임
	if (GetPos().X < CameraFrontCheckPos.X + WinScale.Half().X && KirbyMovePos.X > 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// 커비가 왼쪽 방향일 때, 화면의 1/4 지점을 넘어가면 움직임
	if (GetPos().X > CameraFrontCheckPos.X + WinScale.Half().Half().X && KirbyMovePos.X < 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// 커비가 윗쪽 방향일 때, 화면의 1/4 지점을 넘어가면 움직임
	if (GetPos().Y > CameraFrontCheckPos.Y + (WinScale - CurrentUIScale).Half().Half().Y && KirbyMovePos.Y < 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}

	// 커비가 아랫쪽 방향일 때, UI화면을 뺀 윈도우화면의 3/4 지점을 넘어가면 움직임
	if (GetPos().Y < CameraBackCheckPos.Y - (WinScale - CurrentUIScale).Half().Half().Y && KirbyMovePos.Y > 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}



	// 왼쪽 위로 나가지 못하게 막음
	if (CameraPos.X + KirbyMovePos.X < 0.0f || CameraBackCheckPos.X + KirbyMovePos.X > CurrentBackGroundScale.X)
	{
		CameraMovePos.X = 0.0f;
	}

	// 오른쪽 아래로 나가지 못하게 막음
	if (CameraPos.Y + KirbyMovePos.Y < 0.0f || CameraBackCheckPos.Y + KirbyMovePos.Y > CurrentBackGroundScale.Y)
	{
		CameraMovePos.Y = 0.0f;
	}


	GetLevel()->GetMainCamera()->AddPos(CameraMovePos);
}



// 몹의 패턴에서 쓰일 커비 객체
void Kirby::LevelStart()
{
	MainKirby = this;
	VegetableValleyPlayLevel* CurrentLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(GetLevel());
	CurrentLevelEnemiesCount = CurrentLevelPtr->GetLevelEnemyCount();
	CurrentBackGroundScale = CurrentLevelPtr->GetLevelBackgroundScale();
	CurrentLevelBitMapFileName = CurrentLevelPtr->GetLevelBitMapFileName();
	CurrentUIScale = PlayUI::UI->UIScale;
	
}


void Kirby::Render(float _Detla)
{
	ActorCollisionDetectionPointRender();
}