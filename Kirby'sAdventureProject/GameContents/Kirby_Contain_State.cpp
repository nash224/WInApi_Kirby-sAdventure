#include "Kirby.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "VegetableValleyPlayLevel.h"
#include "PlayUI.h"
#include "FadeObject.h"
#include "DustEffect.h"
#include "HitObjectEffect.h"
#include "SmallStarFireEffect.h"
#include "LargeStarFireEffect.h"
#include "GetAbilityEffect.h"



void Kirby::Contain_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Contain_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 2);
	GlobalContents::SpriteFileLoad("Contain_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 2);

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	MainRenderer->CreateAnimation("Normal_Left_Contain_Idle", "Contain_Left_Kirby.bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Idle", "Contain_Right_Kirby.bmp", 0, 0, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Walk", "Contain_Left_Kirby.bmp", 1, 4, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Walk", "Contain_Right_Kirby.bmp", 1, 4, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Run", "Contain_Left_Kirby.bmp", 1, 4, 0.1f, true);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Run", "Contain_Right_Kirby.bmp", 1, 4, 0.1f, true);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Turn", "Contain_Left_Kirby.bmp", 1, 1, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Turn", "Contain_Right_Kirby.bmp", 1, 1, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Jump", "Contain_Left_Kirby.bmp", 1, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Jump", "Contain_Right_Kirby.bmp", 1, 2, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Fall", "Contain_Left_Kirby.bmp", 2, 2, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Fall", "Contain_Right_Kirby.bmp", 2, 2, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Gulp", "Contain_Left_Kirby.bmp", 9, 11, 0.15f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Gulp", "Contain_Right_Kirby.bmp", 9, 11, 0.15f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Disgorge", "Contain_Left_Kirby.bmp", 5, 8, 0.08f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Disgorge", "Contain_Right_Kirby.bmp", 5, 8, 0.08f, false);


	MainRenderer->FindAnimation("Normal_Left_Contain_Walk")->Inters = { 0.2f , 0.3f , 0.2f , 0.3f };
	MainRenderer->FindAnimation("Normal_Right_Contain_Walk")->Inters = { 0.2f , 0.3f , 0.2f , 0.3f };

	MainRenderer->FindAnimation("Normal_Left_Contain_Run")->Inters = { 0.12f , 0.2f , 0.12f , 0.2f };
	MainRenderer->FindAnimation("Normal_Right_Contain_Run")->Inters = { 0.12f , 0.2f , 0.12f , 0.2f };

}

void Kirby::Contain_IdleStart()
{
	StateTime = 0.0f;
	KeepDamagedState = KirbyState::Contain_Idle;
	ChangeKirbyBodyState(KirbyBodyState::Fat);

	ChangeAnimationState("Contain_Idle");
}

void Kirby::Contain_IdleUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Contain_Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Contain_Gulp);
		return;
	}
	if (true == (GameEngineInput::IsDown('Z')))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}
	if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Contain_Jump);
		return;
	}

	if (true == CheckLeftWall() && GameEngineInput::IsPress('A') && CurrentSpeed == 0.0f)
	{
		return;
	}
	if (true == CheckRightWall() && GameEngineInput::IsPress('D') && CurrentSpeed == 0.0f)
	{
		return;
	}

	if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Walk);
		return;
	}



	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::Contain_WalkStart()
{
	StateTime = 0.0f;
	KirbyDirCheck();
	ChangeAnimationState("Contain_Walk");
}

void Kirby::Contain_WalkUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Contain_Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Contain_Gulp);
		return;
	}

	if (CurrentSpeed < WalkMaxSpeed * 0.2f && true == GameEngineInput::IsDown('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Run);
		return;
	}

	if (CurrentSpeed > WalkMaxSpeed * 0.2f && true == GameEngineInput::IsDown('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Run);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Contain_Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (CurrentSpeed == 0.0f &&
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
		(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������ ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		CurrentSpeed = 0.0f;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}
	if (true == CheckRightWallBasedSpeed())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������ ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		CurrentSpeed = 0.0f;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}



	MoveHorizontal(WalkSpeed, _Delta);

	




	BlockedByGround();
	BlockedByWall();
	BlockedByAll();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
	


	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::Contain_RunStart()
{
	StateTime = 0.0f;

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	// ���� ����Ʈ
	DustEffect* DustEffectPtr = CurLevelPtr->CreateActor<DustEffect>(UpdateOrder::Ability);
	if (nullptr == DustEffectPtr)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	DustEffectPtr->init(GetPos(), GetKirbyScale(), -GetDirUnitVector());


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_RunSound.wav");


	ChangeAnimationState("Contain_Run");
}

void Kirby::Contain_RunUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Contain_Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::Contain_Gulp);
		return;
	}
	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Contain_Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Turn);
		return;
	}

	if (CurrentSpeed == 0.0f &&
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
			(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������ ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);
		CurrentSpeed = 0.0f;

		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == CheckRightWallBasedSpeed())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������ ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);
		CurrentSpeed = 0.0f;

		ChangeState(KirbyState::Contain_Idle);
		return;
	}



	MoveHorizontal(RunSpeed, _Delta);



	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::Contain_TurnStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	if (CurrentSpeed > 0.0f)
	{
		Dir = ActorDir::Right;
	}
	if (CurrentSpeed < 0.0f)
	{
		Dir = ActorDir::Left;
	}

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	// ���� ����Ʈ
	DustEffect* DustEffectPtr = CurLevelPtr->CreateActor<DustEffect>(UpdateOrder::Ability);
	if (nullptr == DustEffectPtr)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
	}

	DustEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_TurnSound.wav");

	ChangeAnimationState("Contain_Turn");
}

void Kirby::Contain_TurnUpdate(float _Delta)
{
	if (CurrentSpeed == 0.0f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Contain_Fall);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		// �� ȿ��
		CurrentSpeed = 0.0f;
	}
	if (true == CheckLeftWallBasedSpeed())
	{
		// �� ȿ��
		CurrentSpeed = 0.0f;
	}



	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	ActorUtils::DecelerationUpdate(_Delta, BreakSpeed);
	HorizontalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::Contain_JumpStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	IsChangeState = false;
	CurrentJumpDistance = 0.0f;
	KirbyDirCheck();
	GravityReset();


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_JumpSound.wav");


	ChangeAnimationState("Contain_Jump");
}

void Kirby::Contain_JumpUpdate(float _Delta)
{

	StateTime += _Delta;

	if (true == GameEngineInput::IsFree('X'))
	{
		IsChangeState = true;
	}


	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (IsChangeState = true && 0.0f < GetGravityVector().Y)
	{
		ChangeState(KirbyState::Contain_Fall);
		return;
	}

	if (true == CeilingCheck())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������ ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		GravityReset();
	}

	// ���� ���� �Ÿ� ����
	if (true == GameEngineInput::IsUp('X'))
	{
		AbleJump = false;
	}

	float JumpPower = 100.0f / JumpTime;
	CurrentJumpDistance += JumpPower * _Delta;

	if (true == GameEngineInput::IsUp('X') || CurrentJumpDistance > 100.0f)
	{
		AbleJump = false;
	}

	if (true == GameEngineInput::IsPress('X') && CurrentJumpDistance < 100.0f && true == AbleJump)
	{
		SetGravityVector(float4::UP * JumpPower);
	}



	MoveHorizontal(WalkSpeed, _Delta);



	BlockedByCeiling();
	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	ChangeAnimationState("Contain_Jump");

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::Contain_FallStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Contain_Fall");
}

void Kirby::Contain_FallUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::Contain_Disgorge);
		return;
	}

	if (true == GetGroundState() && CurrentSpeed != 0.0f)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������ ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}
		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		ChangeState(KirbyState::Contain_Walk);
		return;
	}

	if (true == GetGroundState() && CurrentSpeed == 0.0f)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������ ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}
		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		// ��ȿ��
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWallBasedSpeed())
	{
		// ��ȿ��
		CurrentSpeed = 0.0f;
	}


	MoveHorizontal(WalkSpeed, _Delta);


	ChangeAnimationState("Contain_Fall");




	BlockedByGround();
	BlockedByWall();
	BlockedByAll();

	
	
	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();


	// �߶� Miss
	if (GetPos().Y > CurrentBackGroundScale.Y - CHECKGAP)
	{
		ChangeState(KirbyState::Miss);
		return;
	}
}


void Kirby::Contain_GulpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	KeepDamagedState = KirbyState::Idle;
	ChangeKirbyBodyState(KirbyBodyState::Little);


	// �Ŀ��� �ϳ��� ������
	if (Star.SwallowedPowerEnemyNumber > 0)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}


		// ��� ��ȯ ����Ʈ
		GetAbilityEffectPtr = CurLevelPtr->CreateActor<GetAbilityEffect>(UpdateOrder::Other);
		if (nullptr == GetAbilityEffectPtr)
		{
			MsgBoxAssert("���Ͱ� NULL �Դϴ�");
			return;
		}

		GetAbilityEffectPtr->init(GetPos(), GetKirbyScale());


		// �ɷ��� ��� ���߿� ��� �����ϸ� ������ ���� �߰� 
		GettingAbility = true;


		// Fade ����
		// Fade �������� ������ On���� => GetAbility ���Ͽ��� ����
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}


		FadeObject* LevelFade = CurLevelPtr->CreateActor<FadeObject>(UpdateOrder::UI);
		if (nullptr == LevelFade)
		{
			MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
			return;
		}

		LevelFade->RequestFadeScreen(FadeAlphaValue);

		
		// �ð� ����
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Other, 1.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::UI, 1.0f);


		// ���� ���
		GameEngineSound::SoundPlay("GetAbility.wav");
	}

	ChangeAnimationState("Contain_Gulp");
}

void Kirby::Contain_GulpUpdate(float _Delta)
{
	StateTime += _Delta;
	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
		Star.SwallowedEnemyNumber = 0;
	}

	if (true == IsChangeState && AbilityStar::Max == CurrentAbilityStar && true == GameEngineInput::IsPress('S'))
	{
		IsGulpEnemy = true;
		ChangeState(KirbyState::LowerPosture);
		return;
	}

	if (true == IsChangeState && AbilityStar::Max == CurrentAbilityStar && false == GameEngineInput::IsPress('S'))
	{
		IsGulpEnemy = true;
		if (CurrentSpeed == 0.0f)
		{
			ChangeState(KirbyState::Idle);
			return;
		}
		if (CurrentSpeed != 0.0f)
		{
			ChangeState(KirbyState::Walk);
			return;
		}
	}

	if (true == IsChangeState && AbilityStar::Max != CurrentAbilityStar && AbilityStar::Normal != CurrentAbilityStar)
	{
		ChangeState(KirbyState::GetAbility);
		return;
	}


	if (true == CheckLeftWallBasedSpeed())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}


		// ���� �� ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWallBasedSpeed())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ���� �� ����Ʈ
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		CurrentSpeed = 0.0f;
	}


	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	if (Star.SwallowedPowerEnemyNumber == 0)
	{
		DecelerationUpdate(_Delta);
		HorizontalUpdate(_Delta);
	}



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::Contain_DisgorgeStart()
{
	StateTime = 0.0f;
	KeepDamagedState = KirbyState::Idle;
	ChangeKirbyBodyState(KirbyBodyState::Little);

	// �� ��ȯ
	StarAttack();


	Star.SwallowedEnemyNumber = 0;
	Star.SwallowedPowerEnemyNumber = 0;
	CurrentAbilityStar = AbilityStar::Max;

	ChangeAnimationState("Contain_Disgorge");
}

void Kirby::Contain_DisgorgeUpdate(float _Delta)
{
	IsChangeState = MainRenderer->IsAnimationEnd();

	if (true == IsChangeState && false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == IsChangeState && true == GetGroundState())
	{
		ChangeState(KirbyState::Idle);
		return;
	}


	MoveHorizontal(WalkSpeed, _Delta);



	BlockedByGround();
	BlockedByWall();
	BlockedByCeiling();
	BlockedByAll();



	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}



	// ������ ���� ����
	CheckKirbyCollision();


	// �߶� Miss
	if (GetPos().Y > CurrentBackGroundScale.Y - CHECKGAP)
	{
		ChangeState(KirbyState::Miss);
		return;
	}
}


///////////////////////////////////

void Kirby::StarAttack()
{
	float4 UnitDir = GetDirUnitVector();

	if (Star.SwallowedEnemyNumber >= 2)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ū��
		LargeStarFireEffect* LargeStarEffect = CurLevelPtr->CreateActor<LargeStarFireEffect>(UpdateOrder::Ability);
		if (nullptr == LargeStarEffect)
		{
			MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
			return;
		}

		LargeStarEffect->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
		LargeStarEffect->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);


		// ���� ���
		GameEngineSound::SoundPlay("Kirby_LargeStarAttack.wav");
	}
	else if (1 == Star.SwallowedEnemyNumber)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ������
		SmallStarFireEffect* StarStarEffect = CurLevelPtr->CreateActor<SmallStarFireEffect>(UpdateOrder::Ability);
		if (nullptr == StarStarEffect)
		{
			MsgBoxAssert("���Ͱ� NULL �Դϴ�.");
			return;
		}

		StarStarEffect->init(CurrentLevelBitMapFileName, GetPos(), GetKirbyScale(), GetDirUnitVector());
		StarStarEffect->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect, float4{ 12.0f , 12.0f });


		// ���� ���
		GameEngineSound::SoundPlay("Kirby_StarAttackSound.wav");
	}
} 



void Kirby::GetAbilityStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	if (1 == Star.SwallowedPowerEnemyNumber)
	{
		Mode = CurrentAbilityStar;
	}
	else if (Star.SwallowedPowerEnemyNumber > 1)
	{
		// ���� ���� ��ü�� ����
		Mode = CurrentAbilityStar;
	}
	else
	{
		MsgBoxAssert("��Ų �Ŀ����Ͱ� ���µ� �ɷ��� �������� �߽��ϴ�.");
		return;
	}

	// �ѹ��� ��� �ɷ��� ���
	TriggerOneTimeAbility();


	// Star����ü �� �� �ʱ�ȭ
	CurrentAbilityStar = AbilityStar::Max;

	Star.SwallowedEnemyNumber = 0;
	Star.SwallowedPowerEnemyNumber = 0;


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	// Sword�� ��������Ʈ ũ�Ⱑ �ٸ�
	if (AbilityStar::Sword == Mode)
	{
		MainRenderer->SetRenderScaleToTexture();
	}


	ChangeAnimationState("GetAbility"); 
}


void Kirby::TriggerOneTimeAbility()
{
	switch (Mode)
	{
	case AbilityStar::Spark:
		OneTimeSpark();
		break;
	case AbilityStar::Laser:
		OneTimeLaser();
		break;
	case AbilityStar::Beam:
		OneTimeBeam();
		break;
	case AbilityStar::Fire:
		break;
	case AbilityStar::Thorn:
		OneTimeThorn();
		break;
	case AbilityStar::Sword:
		break;
	case AbilityStar::Ice:
		break;
	default:
		break;
	}
}



void Kirby::GetAbilityUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > GetABilityStateEndTime)
	{
		if (nullptr == ThornEffectCollision)
		{
			MsgBoxAssert("�浹ü�� Null �Դϴ�.");
			return;
		}

		if (nullptr == SparkEffectCollision)
		{
			MsgBoxAssert("�浹ü�� Null �Դϴ�.");
			return;
		}

		// �ð��ٵǸ� Ư�� �ɷ� Off
		ThornEffectCollision->Off();
		SparkEffectCollision->Off();
		IsChangeState = true;
	}



	// �������� �ɷ¸� ���� ���ִ� �Լ�
	TriggerMultiTimeAbility(_Delta);


	if (true == IsChangeState)
	{
		// Fade ����
		FadeObject::IsFadeScreenRelease = true;

		// �ð� Delta Reset
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);


		GettingAbility = false;
		

		// �ٴ��� �ְ� �ӵ��� 0�̸� Idle
		if (true == GetGroundState() && 0 == CurrentSpeed)
		{
			ChangeState(KirbyState::Idle);
			return;
		}

		// �ٴ��� �ְ� �ӵ��� ������ Walk
		if (true == GetGroundState() && 0 != CurrentSpeed)
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		// ü�� �����̸� Fall
		if (false == GetGroundState())
		{
			ChangeState(KirbyState::Fall);
			return;
		}
	}




	// �� ���
	BlockedByGround();
	BlockedByWall();
}



void Kirby::TriggerMultiTimeAbility(float _Delta)
{
	switch (Mode)
	{
	case AbilityStar::Spark:
		TriggerSparkAbilityAfterProcess(_Delta);
		break;
	case AbilityStar::Laser:
		break;
	case AbilityStar::Beam:
		break;
	case AbilityStar::Fire:
		TriggerFireAbilityAfterProcess(_Delta);
		break;
	case AbilityStar::Thorn:
		break;
	case AbilityStar::Sword:
		break;
	case AbilityStar::Ice:
		TriggerIceAbilityAfterProcess(_Delta);
		break;
	default:
		break;
	}
}





// Ŀ�� �Կ� ���� ������ ������
void Kirby::Contain_DamagedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	// ������ ��û
	// ������û
	++VegetableValleyPlayLevel::Camera_ShakeCount;
	

	// UI�� ��û
	// ����
	if (nullptr == UIManagerPtr)
	{
		MsgBoxAssert("UI�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	if ("PlayUI" == UIManagerPtr->GetName())
	{
		PlayUI::PlayUI_Score += 50;
	}

	// ������ ü�°���
	if (m_KirbyHp > 0)
	{
		--m_KirbyHp;
	}


	// �鿪 On
	ImmuneState = true;

	// Ŀ�� ���� �浹ü Off
	KirbyBodyCollisonOff();



	// �߷� �ʱ�ȭ
	GravityReset();

	// ƨ�ܳ���
	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = BouncingOff_XPower;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = -BouncingOff_XPower;
	}

	SetGravityVector(float4{ 0.0f , BouncingOff_YPower });




	if (Mode != AbilityStar::Normal && Mode != AbilityStar::Max)
	{
		KeepMode = Mode;
		Mode = AbilityStar::Normal;

		ChangeAnimationState("Contain_Damaged");

		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
			return;
		}

		MainRenderer->SetRenderScaleToTexture();
		DropAbility();
	}
	else
	{
		ChangeAnimationState("Contain_Damaged");
	}
}


void Kirby::Contain_DamagedUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > Kirby_DamagedState_time)
	{
		IsChangeState = true;
	}

	
	if (true == IsChangeState)
	{
		if (KirbyState::Fly == KeepDamagedState)
		{
			ChangeState(KirbyState::Fly);
			return;
		}
		else if (KirbyState::Contain_Idle == KeepDamagedState)
		{
			ChangeState(KirbyState::Contain_Fall);
			return;
		}
	}



	// ���� ����� ����
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();



	// ü�������� �� �߷� ����
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}


	// ����
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);


	// �߶� Miss
	if (GetPos().Y > CurrentBackGroundScale.Y - CHECKGAP)
	{
		ChangeState(KirbyState::Miss);
		return;
	}
}