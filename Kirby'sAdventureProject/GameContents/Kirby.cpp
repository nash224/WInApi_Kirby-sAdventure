#include "Kirby.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "PlayUI.h"



Kirby* Kirby::MainKirby = nullptr;
bool Kirby::IsKirbyOpenDoorToLevel = false;
bool Kirby::IsKirbyCloseDoorToLevel = false;


Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}



void Kirby::Start()
{
	MainKirby = this;
	if (nullptr == MainKirby)
	{
		MsgBoxAssert("커비를 등록하지 못했습니다.");
		return;
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	Normal_StateResourceLoad();
	Spark_StateResourceLoad();
	Laser_StateResourceLoad();
	Beam_StateResourceLoad();
	Fire_StateResourceLoad();
	Thorn_StateResourceLoad();
	Sword_StateResourceLoad();
	Ice_StateResourceLoad();
	Contain_StateResourceLoad();
	MoveLevel_StateResourceLoad();

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Dir = ActorDir::Right;
	BodyState = KirbyBodyState::Little;
	Mode = AbilityStar::Normal;
	CurMode = "Normal";
	m_KirbyHp = 6;



	ChangeState(KirbyState::Idle);

	Collision_Load();
}



void Kirby::Collision_Load()
{
	LittleCollision = CreateCollision(CollisionOrder::PlayerBody);
	if (nullptr == LittleCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	LittleCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.Half().Y });
	LittleCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	LittleCollision->SetCollisionType(CollisionType::Rect);
	LittleCollision->On();



	LowerCollision = CreateCollision(CollisionOrder::PlayerBody);
	if (nullptr == LowerCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	LowerCollision->SetCollisionPos(float4{ 0.0f , -LOWERTYPECOLLISIONSCALE.Half().Y });
	LowerCollision->SetCollisionScale(LOWERTYPECOLLISIONSCALE);
	LowerCollision->SetCollisionType(CollisionType::Rect);
	LowerCollision->Off();



	FatCollision = CreateCollision(CollisionOrder::PlayerBody);
	if (nullptr == FatCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	FatCollision->SetCollisionPos(float4{ 0.0f , -FATTYPECOLLISIONSCALE.Half().Y });
	FatCollision->SetCollisionScale(FATTYPECOLLISIONSCALE);
	FatCollision->SetCollisionType(CollisionType::Rect);
	FatCollision->Off();



	LowerAttackCollision = CreateCollision(CollisionOrder::PlayerAbility);
	if (nullptr == LowerAttackCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	LowerAttackCollision->SetCollisionScale(LOWERATTACKCOLLISIONSCALE);
	LowerAttackCollision->SetCollisionType(CollisionType::Rect);
	LowerAttackCollision->Off();



	ImmuneCollision = CreateCollision(CollisionOrder::PlayerBody);
	if (nullptr == ImmuneCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	ImmuneCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.Half().Y });
	ImmuneCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	ImmuneCollision->SetCollisionType(CollisionType::Rect);
	ImmuneCollision->Off();


	InhaleEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == InhaleEffectCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	InhaleEffectCollision->SetCollisionScale(INHALEEFFECTCOLLISIONSCALE);
	InhaleEffectCollision->SetCollisionType(CollisionType::Rect);
	InhaleEffectCollision->Off();




	SparkEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == SparkEffectCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}


	SparkEffectCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.Half().Y });
	SparkEffectCollision->SetCollisionScale(SPARKEFFECTCOLLISIONSCALE);
	SparkEffectCollision->SetCollisionType(CollisionType::Rect);
	SparkEffectCollision->Off();




	SwordEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == SwordEffectCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	SwordEffectCollision->SetCollisionScale(SWORDEFFECTCOLLISIONSCALE);
	SwordEffectCollision->SetCollisionType(CollisionType::Rect);
	SwordEffectCollision->Off();



	AerialSwordEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == AerialSwordEffectCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}

	AerialSwordEffectCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.Half().Y });
	AerialSwordEffectCollision->SetCollisionScale(AERIALSWORDEFFECTCOLLISIONSCALE);
	AerialSwordEffectCollision->SetCollisionType(CollisionType::Rect);
	AerialSwordEffectCollision->Off();




	ThornEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == ThornEffectCollision)
	{
		MsgBoxAssert("액터가 NULL 입니다.");
		return;
	}


	ThornEffectCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.Half().Y });
	ThornEffectCollision->SetCollisionScale(SPARKEFFECTCOLLISIONSCALE);
	ThornEffectCollision->SetCollisionType(CollisionType::Rect);
	ThornEffectCollision->Off();

}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


// 레벨에서 ActorUpdate()->Update
void Kirby::Update(float _Delta)
{
	KirbysDebugShortcut(_Delta);


	// 면역 함수
	ImmuneFunc(_Delta);

	// 커비 UI 초상화 'NotThing' 띄우는 변수
	if (true == IsGulpEnemy)
	{
		IsGulpEnemy = false;

		// 사운드 재생
		GameEngineSound::SoundPlay("NothingSound.wav");
	}



	PrevKirbyMovePos = GetPos();

	StateUpdate(_Delta);

	// 이동한 거리
	KirbyMovePos = GetPos() - PrevKirbyMovePos;

}


// 상태 업데이트
void Kirby::StateUpdate(float _Delta)
{
	GroundCheck();

	switch (State)
	{
	case KirbyState::Idle:							return IdleUpdate(_Delta);
	case KirbyState::Walk:							return WalkUpdate(_Delta);
	case KirbyState::Run:							return RunUpdate(_Delta);
	case KirbyState::Turn:							return TurnUpdate(_Delta);
	case KirbyState::Jump:							return JumpUpdate(_Delta);
	case KirbyState::AerialMotion:					return AerialMotionUpdate(_Delta);
	case KirbyState::Fall:							return FallUpdate(_Delta);
	case KirbyState::AccelerateDown:				return AccelerateDownUpdate(_Delta);
	case KirbyState::Bounce:						return BounceUpdate(_Delta);
	case KirbyState::Landing:						return LandingUpdate(_Delta);
	case KirbyState::LowerPosture:					return LowerPostureUpdate(_Delta);
	case KirbyState::LowerAttack:					return LowerAttackUpdate(_Delta);
	case KirbyState::HittheWall:					return HittheWallUpdate(_Delta);
	case KirbyState::HittheCeiling:					return HittheCeilingUpdate(_Delta);
	case KirbyState::TakeOff:						return TakeOffUpdate(_Delta);
	case KirbyState::Fly:							return FlyUpdate(_Delta);
	case KirbyState::ExhaleAttack:					return ExhaleAttackUpdate(_Delta);
	case KirbyState::UseSpecialAbility:				return UseSpecialAbilityUpdate(_Delta);
	case KirbyState::AerialUseSpecialAbility:		return AerialUseSpecialAbilityUpdate(_Delta);
	case KirbyState::ReleaseSpecialAbility:			return ReleaseSpecialAbilityUpdate(_Delta);
	case KirbyState::GetAbility:					return GetAbilityUpdate(_Delta);
	case KirbyState::Damaged:						return DamagedUpdate(_Delta);
	case KirbyState::Enter:							return EnterUpdate(_Delta);
	case KirbyState::OpenDoorAndRaiseFlag:			return OpenDoorAndRaiseFlagUpdate(_Delta);
	case KirbyState::OpenDoorAndRaiseFlagAfter:		return OpenDoorAndRaiseFlagAfterUpdate(_Delta);
	case KirbyState::StageClearWalk:				return StageClearWalkUpdate(_Delta);
	case KirbyState::StageClear:					return StageClearUpdate(_Delta);
	case KirbyState::Performance:					return PerformanceUpdate(_Delta);
	case KirbyState::Miss:							return MissUpdate(_Delta);
	case KirbyState::MissRaiseUp:					return MissRaiseUpUpdate(_Delta);
	case KirbyState::Contain_Idle:					return Contain_IdleUpdate(_Delta);
	case KirbyState::Contain_Walk:					return Contain_WalkUpdate(_Delta);
	case KirbyState::Contain_Run:					return Contain_RunUpdate(_Delta);
	case KirbyState::Contain_Turn:					return Contain_TurnUpdate(_Delta);
	case KirbyState::Contain_Jump:					return Contain_JumpUpdate(_Delta);
	case KirbyState::Contain_Fall:					return Contain_FallUpdate(_Delta);
	case KirbyState::Contain_Gulp:					return Contain_GulpUpdate(_Delta);
	case KirbyState::Contain_Disgorge:				return Contain_DisgorgeUpdate(_Delta);
	case KirbyState::Contain_Damaged:				return Contain_DamagedUpdate(_Delta);
	default:
		break;
	}
}


// 상태 변환
void Kirby::ChangeState(KirbyState _State)
{
	if (_State != State)
	{
		SetCheckPoint(GetKirbyScale());

		switch (_State)
		{
		case KirbyState::Idle:						IdleStart();						break;
		case KirbyState::Walk:						WalkStart();						break;
		case KirbyState::Run:						RunStart();							break;
		case KirbyState::Turn:						TurnStart();						break;
		case KirbyState::Jump:						JumpStart();						break;
		case KirbyState::AerialMotion:				AerialMotionStart();				break;
		case KirbyState::Fall:						FallStart();						break;
		case KirbyState::AccelerateDown:			AccelerateDownStart();				break;
		case KirbyState::Bounce:					BounceStart();						break;
		case KirbyState::Landing:					LandingStart();						break;
		case KirbyState::LowerPosture:				LowerPostureStart();				break;
		case KirbyState::LowerAttack:				LowerAttackStart();					break;
		case KirbyState::HittheWall:				HittheWallStart();					break;
		case KirbyState::HittheCeiling:				HittheCeilingStart();				break;
		case KirbyState::TakeOff:					TakeOffStart();						break;
		case KirbyState::Fly:						FlyStart();							break;
		case KirbyState::ExhaleAttack:				ExhaleAttackStart();				break;
		case KirbyState::UseSpecialAbility:			UseSpecialAbilityStart();			break;
		case KirbyState::AerialUseSpecialAbility:	AerialUseSpecialAbilityStart();		break;
		case KirbyState::ReleaseSpecialAbility:		ReleaseSpecialAbilityStart();		break;
		case KirbyState::GetAbility:				GetAbilityStart();					break;
		case KirbyState::Damaged:					DamagedStart();						break;
		case KirbyState::Enter:						EnterStart();						break;
		case KirbyState::OpenDoorAndRaiseFlag:		OpenDoorAndRaiseFlagStart();		break;
		case KirbyState::OpenDoorAndRaiseFlagAfter:	OpenDoorAndRaiseFlagAfterStart();	break;
		case KirbyState::StageClearWalk:			StageClearWalkStart();				break;
		case KirbyState::StageClear:				StageClearStart();					break;
		case KirbyState::Performance:				PerformanceStart();					break;
		case KirbyState::Miss:						MissStart();						break;
		case KirbyState::MissRaiseUp:				MissRaiseUpStart();					break;
		case KirbyState::Contain_Idle:				Contain_IdleStart();				break;
		case KirbyState::Contain_Walk:				Contain_WalkStart();				break;
		case KirbyState::Contain_Run:				Contain_RunStart();					break;
		case KirbyState::Contain_Turn:				Contain_TurnStart();				break;
		case KirbyState::Contain_Jump:				Contain_JumpStart();				break;
		case KirbyState::Contain_Fall:				Contain_FallStart();				break;
		case KirbyState::Contain_Gulp:				Contain_GulpStart();				break;
		case KirbyState::Contain_Disgorge:			Contain_DisgorgeStart();			break;
		case KirbyState::Contain_Damaged:			Contain_DamagedStart();				break;
		default:
			break;
		}
	}

	State = _State;
}


// 애니메이션 변경 및 변수 동기화
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
	case AbilityStar::Ice:
		ModeName = "Ice_";
		break;
	default:
		break;
	}

	ModeName += AnimationName;

	CurState = _StateName;

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	MainRenderer->ChangeAnimation(ModeName, _StartFrame);
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
// 비트맵

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


// 커비 충돌 크기 및 상태 변경
void Kirby::ChangeKirbyBodyState(KirbyBodyState _BodyState)
{
	if (BodyState == _BodyState)
	{
		return;
	}

	BodyState = _BodyState;

	if (true == Cheat_NoneBodyCollision)
	{
		return;
	}

	if (nullptr == LittleCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다.");
		return;
	}

	if (nullptr == LowerCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다.");
		return;
	}

	if (nullptr == FatCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다.");
		return;
	}


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


// 문이 있는가?
bool Kirby::IsEnterPixel()
{
	unsigned int CeilingLeftColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint);
	unsigned int CeilingRightColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint);
	unsigned int GroundLeftColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint);
	unsigned int GroundRightColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint);
	if (CeilingLeftColor == RGB(0, 255, 0) || CeilingRightColor == RGB(0, 255, 0) ||
		GroundLeftColor == RGB(0, 255, 0) || GroundRightColor == RGB(0, 255, 0))
	{
		return true;
	}

	return false;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
// 이동 


// ActorUtils override : 중력 동기화
void Kirby::VerticalUpdate(float _Delta)
{
	AddPos(GetGravityVector() * _Delta);
}


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

// ActorUtils override : 커비 고유 감속도
void Kirby::DecelerationUpdate(float _Delta)
{
	if ((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) || (GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D')))
	{
		if (CurrentSpeed < 0.0f)
		{
			CurrentSpeed += DecelerationSpeed * _Delta;

			if (CurrentSpeed > 0.0f)
			{
				CurrentSpeed = 0.0f;
			}
		}
		else if (CurrentSpeed > 0.0f)
		{
			CurrentSpeed -= DecelerationSpeed * _Delta;

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
		if (CurrentSpeed <= -FlyMaxSpeed)
		{
			CurrentSpeed = -FlyMaxSpeed;
		}

		if (CurrentSpeed >= FlyMaxSpeed)
		{
			CurrentSpeed = FlyMaxSpeed;
		}
	}
	else if (State == KirbyState::Run || State == KirbyState::Contain_Run || State == KirbyState::LowerAttack)
	{
		if (CurrentSpeed <= -RunMaxSpeed)
		{
			CurrentSpeed = -RunMaxSpeed;
		}

		if (CurrentSpeed >= RunMaxSpeed)
		{
			CurrentSpeed = RunMaxSpeed;
		}
	}
	else if ((CurrentSpeed > WalkMaxSpeed || CurrentSpeed < -WalkMaxSpeed))
	{
		if (CurrentSpeed <= -WalkMaxSpeed)
		{
			CurrentSpeed = -WalkMaxSpeed;
		}

		if (CurrentSpeed >= WalkMaxSpeed)
		{
			CurrentSpeed = WalkMaxSpeed;
		}
	}

	AddPos({ CurrentSpeed * _Delta, 0.0f });
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
// 충돌


// 몸통 충돌체 Getter
GameEngineCollision* Kirby::GetKirbyCollison()
{
	static GameEngineCollision* ReturnValue;

	if (BodyState == KirbyBodyState::Little)
	{
		if (nullptr == LittleCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return ReturnValue;
		}

		return LittleCollision;
	}

	if (BodyState == KirbyBodyState::Fat)
	{
		if (nullptr == FatCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return ReturnValue;
		}

		return FatCollision;
	}

	if (BodyState == KirbyBodyState::Lower)
	{
		if (nullptr == LowerCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return ReturnValue;
		}

		return LowerCollision;
	}

	MsgBoxAssert("커비 충돌체 리턴에 실패했습니다.");
	return BodyCollision;
}



// 몸통 충돌체 On
void Kirby::KirbyBodyCollisonOn()
{
	if (BodyState == KirbyBodyState::Little)
	{
		if (nullptr == LittleCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return;
		}

		LittleCollision->On();
	}

	if (BodyState == KirbyBodyState::Fat)
	{
		if (nullptr == FatCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return;
		}

		FatCollision->On();
	}

	if (BodyState == KirbyBodyState::Lower)
	{
		if (nullptr == LowerCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return;
		}

		LowerCollision->On();
	}

	if (nullptr == ImmuneCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다");
		return;
	}

	ImmuneCollision->Off();
}


// 몸통 충돌체 Off
void Kirby::KirbyBodyCollisonOff()
{
	if (nullptr == LittleCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다");
		return;
	}

	if (nullptr == FatCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다");
		return;
	}

	if (nullptr == LowerCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다");
		return;
	}

	LittleCollision->Off();
	FatCollision->Off();
	LowerCollision->Off();

	if (false == Cheat_NoneBodyCollision)
	{
		if (nullptr == ImmuneCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다");
			return;
		}

		ImmuneCollision->On();
	}
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Kirby::LevelStart()
{
	MainKirby = this;

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	if ("BonusGame" == CurLevel->GetName())
	{
		return;
	}


	VegetableValleyPlayLevel* CurrentLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevel);
	if (nullptr == CurrentLevelPtr)
	{
		MsgBoxAssert("다운 캐스팅을 하지 못했습니다.");
		return;
	}

	CurrentLevelEnemiesCount = CurrentLevelPtr->GetLevelEnemyCount();
	CurrentBackGroundScale = CurrentLevelPtr->GetLevelBackgroundScale();
	CurrentLevelBitMapFileName = CurrentLevelPtr->GetLevelBitMapFileName();

	UIManagerPtr = CurrentLevelPtr->GetUIManager();
	if (nullptr == UIManagerPtr)
	{
		MsgBoxAssert("레벨 UI 를 불러오지 못했습니다.");
		return;
	}

	CurrentUIScale = UIManagerPtr->UIScale;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void Kirby::Render(float _Detla)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("백버퍼를 불러오지 못했습니다.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();



	KirbyDebugRender(dc);
	ThisDebugRender(dc);
	KeyDownRender(dc);

	ActorCollisionDetectionPointRender();
}


// 면역 상태
void Kirby::ImmuneFunc(float _Delta)
{
	if (true == ImmuneState)
	{
		ImmuneTime += _Delta;
	}


	if (ImmuneTime > ImmuneDuration)
	{
		ImmuneTime = 0.0f;
		ImmuneState = false;
		IsHitted = false;

		KirbyBodyCollisonOn();
	}
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Kirby::LevelEnd()
{
	// TimeSet
	GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
}
