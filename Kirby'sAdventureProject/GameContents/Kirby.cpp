#include "Kirby.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

#include "VegetableValleyPlayLevel.h"
#include "PlayUI.h"

#include <Windows.h>


Kirby* Kirby::MainKirby = nullptr;
float Kirby::SoundVol = 0.0f;


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
		MsgBoxAssert("Ŀ�� ������� ���߽��ϴ�.");
		return;
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	Normal_StateResourceLoad();
	Spark_StateResourceLoad();
	Laser_StateResourceLoad();
	Beam_StateResourceLoad();
	Fire_StateResourceLoad();
	Thorn_StateResourceLoad();
	Contain_StateResourceLoad();
	MoveLevel_StateResourceLoad();

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	{// Ŀ�������ġ Level�� �̵� ����
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
	if (nullptr == LittleCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}

	LittleCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.Half().Y });
	LittleCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	LittleCollision->SetCollisionType(CollisionType::Rect);
	LittleCollision->On();



	LowerCollision = CreateCollision(CollisionOrder::PlayerBody);
	if (nullptr == LowerCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}

	LowerCollision->SetCollisionPos(float4{ 0.0f , -LOWERTYPECOLLISIONSCALE.Half().Y });
	LowerCollision->SetCollisionScale(LOWERTYPECOLLISIONSCALE);
	LowerCollision->SetCollisionType(CollisionType::Rect);
	LowerCollision->Off();



	FatCollision = CreateCollision(CollisionOrder::PlayerBody);
	if (nullptr == FatCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}

	FatCollision->SetCollisionPos(float4{ 0.0f , -FATTYPECOLLISIONSCALE.Half().Y });
	FatCollision->SetCollisionScale(FATTYPECOLLISIONSCALE);
	FatCollision->SetCollisionType(CollisionType::Rect);
	FatCollision->Off();



	LowerAttackCollision = CreateCollision(CollisionOrder::PlayerAbility);
	if (nullptr == LowerAttackCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}

	LowerAttackCollision->SetCollisionScale(LOWERATTACKCOLLISIONSCALE);
	LowerAttackCollision->SetCollisionType(CollisionType::Rect);
	LowerAttackCollision->Off();



	ImmuneCollision = CreateCollision(CollisionOrder::PlayerBody);
	if (nullptr == ImmuneCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}

	ImmuneCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.Half().Y });
	ImmuneCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	ImmuneCollision->SetCollisionType(CollisionType::Rect);
	ImmuneCollision->Off();


	InhaleEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == InhaleEffectCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}

	InhaleEffectCollision->SetCollisionScale(INHALEEFFECTCOLLISIONSCALE);
	InhaleEffectCollision->SetCollisionType(CollisionType::Rect);
	InhaleEffectCollision->Off();



	
	SparkEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == SparkEffectCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}


	SparkEffectCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.Half().Y });
	SparkEffectCollision->SetCollisionScale(SPARKEFFECTCOLLISIONSCALE);
	SparkEffectCollision->SetCollisionType(CollisionType::Rect);
	SparkEffectCollision->Off();



	ThornEffectCollision = CreateCollision(CollisionOrder::KirbyInhaleAbility);
	if (nullptr == ThornEffectCollision)
	{
		MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
		return;
	}


	ThornEffectCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.Half().Y });
	ThornEffectCollision->SetCollisionScale(SPARKEFFECTCOLLISIONSCALE);
	ThornEffectCollision->SetCollisionType(CollisionType::Rect);
	ThornEffectCollision->Off();



	// ����
	SoundVol = GameEngineSound::GetGlobalVolume();
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


// �������� ActorUpdate()->Update
void Kirby::Update(float _Delta)
{
	// �鿪 �Լ�
	ImmuneFunc(_Delta);

	// Ŀ�� UI �ʻ�ȭ 'NotThing' ���� ����
	if (true == IsGulpEnemy)
	{
		IsGulpEnemy = false;
	}

	KirbysDebugShortcut(_Delta);


	PrevKirbyMovePos = GetPos();

	StateUpdate(_Delta);

	// �̵��� �Ÿ�
	KirbyMovePos = GetPos() - PrevKirbyMovePos;


	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max)
	{
		DropAbility();
	}


	// ī�޶�
	CameraFocus();
}





void Kirby::KirbysDebugShortcut(float _Delta)
{
	// ����� ������ ��ȯŰ
	if (true == GameEngineInput::IsDown('Y'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}



	if (true == GameEngineInput::IsDown('J'))
	{
		ChangeState(KirbyState::StageClear);
		return;
	}


	SoundVolPressKeyTime += _Delta;

	if (SoundVolPressKeyTime > SoundVol_KeyDownCycle)
	{
		if (true == GameEngineInput::IsPress(VK_OEM_6))
		{
			float SoundVolumeReturnValue = GameEngineSound::GetGlobalVolume();

			if (SoundVolumeReturnValue < MAX_VOLUME_AMOUNT)
			{
				SoundVol = SoundVolumeReturnValue + SoundVol_OneTime_AmountOfChange;
			}

			GameEngineSound::SetGlobalVolume(SoundVol);

			SoundVolPressKeyTime = 0.0f;
		}
		else if (true == GameEngineInput::IsPress(VK_OEM_4))
		{
			float SoundVolumeReturnValue = GameEngineSound::GetGlobalVolume();

			if (SoundVolumeReturnValue > 0.0f)
			{
				SoundVol = SoundVolumeReturnValue - SoundVol_OneTime_AmountOfChange;

				if (SoundVol < 0.0f)
				{
					SoundVol = 0.0f;
				}
			}

			GameEngineSound::SetGlobalVolume(SoundVol);

			SoundVolPressKeyTime = 0.0f;
		}
	}


}



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
	case KirbyState::ReleaseSpecialAbility:			return ReleaseSpecialAbilityUpdate(_Delta);
	case KirbyState::GetAbility:					return GetAbilityUpdate(_Delta);
	case KirbyState::Damaged:						return DamagedUpdate(_Delta);
	case KirbyState::Enter:							return EnterUpdate(_Delta);
	case KirbyState::OpenDoorAndRaiseFlag:			return OpenDoorAndRaiseFlagUpdate(_Delta);
	case KirbyState::OpenDoorAndRaiseFlagAfter:		return OpenDoorAndRaiseFlagAfterUpdate(_Delta);
	case KirbyState::StageClearWalk:				return StageClearWalkUpdate(_Delta);
	case KirbyState::StageClear:					return StageClearUpdate(_Delta);
	case KirbyState::Performance:					return PerformanceUpdate(_Delta);
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
		case KirbyState::ReleaseSpecialAbility:		ReleaseSpecialAbilityStart();		break;
		case KirbyState::GetAbility:				GetAbilityStart();					break;
		case KirbyState::Damaged:					DamagedStart();						break;
		case KirbyState::Enter:						EnterStart();						break;
		case KirbyState::OpenDoorAndRaiseFlag:		OpenDoorAndRaiseFlagStart();		break;
		case KirbyState::OpenDoorAndRaiseFlagAfter:	OpenDoorAndRaiseFlagAfterStart();	break;
		case KirbyState::StageClearWalk:			StageClearWalkStart();				break;
		case KirbyState::StageClear:				StageClearStart();					break;
		case KirbyState::Performance:				PerformanceStart();					break;
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


// ���� �Լ�
/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

// Ŀ�� ����üũ
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

// Ŀ�� �浹 ũ�� �� ���� ����
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


// �߳� �߾� ����
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

	MsgBoxAssert("Ŀ�� �浹ü ���Ͽ� �����߽��ϴ�.");
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



// �̵� �Լ�
/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


// Ŀ�� X�� �̵� ����
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

// Ŀ�� ���� ���ӵ�
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


// Ŀ���� ��ġ ����ȭ
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


// ���� �Լ�
/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

/*
* 1. ������ ������ ���ؾ��Ѵ�.
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

	// Ŀ�� ������ ������ ��, ȭ���� �߾��� �Ѿ�� ������
	if (GetPos().X < CameraFrontCheckPos.X + WinScale.Half().X && KirbyMovePos.X > 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// Ŀ�� ���� ������ ��, ȭ���� 1/4 ������ �Ѿ�� ������
	if (GetPos().X > CameraFrontCheckPos.X + WinScale.Half().Half().X && KirbyMovePos.X < 0.0f)
	{
		CameraMovePos.X = 0.0f;
	}

	// Ŀ�� ���� ������ ��, ȭ���� 1/4 ������ �Ѿ�� ������
	if (GetPos().Y > CameraFrontCheckPos.Y + (WinScale - CurrentUIScale).Half().Half().Y && KirbyMovePos.Y < 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}

	// Ŀ�� �Ʒ��� ������ ��, UIȭ���� �� ������ȭ���� 3/4 ������ �Ѿ�� ������
	if (GetPos().Y < CameraBackCheckPos.Y - (WinScale - CurrentUIScale).Half().Half().Y && KirbyMovePos.Y > 0.0f)
	{
		CameraMovePos.Y = 0.0f;
	}



	// ���� ���� ������ ���ϰ� ����
	if (CameraPos.X + KirbyMovePos.X < 0.0f || CameraBackCheckPos.X + KirbyMovePos.X > CurrentBackGroundScale.X)
	{
		CameraMovePos.X = 0.0f;
	}

	// ������ �Ʒ��� ������ ���ϰ� ����
	if (CameraPos.Y + KirbyMovePos.Y < 0.0f || CameraBackCheckPos.Y + KirbyMovePos.Y > CurrentBackGroundScale.Y)
	{
		CameraMovePos.Y = 0.0f;
	}


	GetLevel()->GetMainCamera()->AddPos(CameraMovePos);
}


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



// ���� ���Ͽ��� ���� Ŀ�� ��ü
void Kirby::LevelStart()
{
	MainKirby = this;

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	VegetableValleyPlayLevel* CurrentLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevel);
	if (nullptr == CurrentLevelPtr)
	{
		MsgBoxAssert("�ٿ� ĳ������ ���� ���߽��ϴ�.");
		return;
	}

	CurrentLevelEnemiesCount = CurrentLevelPtr->GetLevelEnemyCount();
	CurrentBackGroundScale = CurrentLevelPtr->GetLevelBackgroundScale();
	CurrentLevelBitMapFileName = CurrentLevelPtr->GetLevelBitMapFileName();

	UIManager* UIManagerPtr = CurrentLevelPtr->GetUIManager();
	if (nullptr == UIManagerPtr)
	{
		MsgBoxAssert("���� UI �� �ҷ����� ���߽��ϴ�.");
		return;
	}

	CurrentUIScale = UIManagerPtr->UIScale;

	
}


void Kirby::Render(float _Detla)
{
	ActorCollisionDetectionPointRender();
}



// �鿪 ���� �Լ�
void Kirby::ImmuneFunc(float _Delta)
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
}