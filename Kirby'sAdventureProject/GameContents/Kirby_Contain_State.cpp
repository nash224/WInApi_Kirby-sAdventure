#include "Kirby.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>


#include "GlobalContents.h"
#include "VegetableValleyPlayLevel.h"
#include "DustEffect.h"
#include "HitObjectEffect.h"
#include "SmallStarFireEffect.h"
#include "LargeStarFireEffect.h"
#include "GetAbilityEffect.h"
#include "FadeObject.h"



void Kirby::Contain_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Contain_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 2);
	GlobalContents::SpriteFileLoad("Contain_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 2);

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

	if (CurrentSpeed < WALKMAXSPEED * 0.2f && true == GameEngineInput::IsDown('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Contain_Run);
		return;
	}

	if (CurrentSpeed > WALKMAXSPEED * 0.2f && true == GameEngineInput::IsDown('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
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
		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		CurrentSpeed = 0.0f;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}
	if (true == CheckRightWallBasedSpeed())
	{
		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		CurrentSpeed = 0.0f;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}



	MoveHorizontal(WALKSPEED, _Delta);

	




	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
	


	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::Contain_RunStart()
{
	StateTime = 0.0f;

	DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>(UpdateOrder::Ability);
	DustEffectPtr->init(GetPos(), GetKirbyScale(), -GetDirUnitVector());
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
		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		HitObjectEffectPtr->init(GetPos(), float4::ZERO);
		CurrentSpeed = 0.0f;

		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	if (true == CheckRightWallBasedSpeed())
	{
		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		HitObjectEffectPtr->init(GetPos(), float4::ZERO);
		CurrentSpeed = 0.0f;

		ChangeState(KirbyState::Contain_Idle);
		return;
	}



	MoveHorizontal(RUNSPEED, _Delta);






	BlockedByGround();
	BlockedByWall();

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

	DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>(UpdateOrder::Ability);
	DustEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());

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

	ActorUtils::DecelerationUpdate(_Delta, BRAKESPEED);
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
		// �� ȿ��
		GravityReset();
	}

	if (true == GameEngineInput::IsUp('X'))
	{
		AbleJump = false;
	}

	float JumpPower = JUMPMAXDISTANCE / JUMPTIME;
	CurrentJumpDistance += JumpPower * _Delta;

	if (true == GameEngineInput::IsUp('X') || CurrentJumpDistance > JUMPMAXDISTANCE)
	{
		AbleJump = false;
	}

	if (true == GameEngineInput::IsPress('X') && CurrentJumpDistance < JUMPMAXDISTANCE && true == AbleJump)
	{
		SetGravityVector(float4::UP * JumpPower);
	}



	MoveHorizontal(WALKSPEED, _Delta);








	BlockedByCeiling();
	BlockedByGround();
	BlockedByWall();


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

		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		ChangeState(KirbyState::Contain_Walk);
		return;
	}

	if (true == GetGroundState() && CurrentSpeed == 0.0f)
	{

		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
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


	MoveHorizontal(WALKSPEED, _Delta);


	ChangeAnimationState("Contain_Fall");





	BlockedByGround();
	BlockedByWall();

	
	
	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
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
		GetAbilityEffectPtr = GetLevel()->CreateActor<GetAbilityEffect>(UpdateOrder::Other);
		if (nullptr == GetAbilityEffectPtr)
		{
			MsgBoxAssert("���Ͱ� NULL �Դϴ�");
			return;
		}

		GetAbilityEffectPtr->init(GetPos(), GetKirbyScale());


		// �ɷ��� ��� ���߿� ��� �����ϸ� ������ ���� �߰� 
		GettingAbility = true;


		// Fade ����
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
	if (true == MainRenderer->IsAnimationEnd() && StateTime > ContainGulpChangeStateTime)
	{
		IsChangeState = true;
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
		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
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
		HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
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


	MoveHorizontal(WALKSPEED, _Delta);




	BlockedByGround();
	BlockedByWall();



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
}


///////////////////////////////////

void Kirby::StarAttack()
{
	float4 UnitDir = GetDirUnitVector();

	if (Star.SwallowedEnemyNumber >= 2)
	{
		// ū��
		LargeStarFireEffect* LargeStarEffect = GetLevel()->CreateActor<LargeStarFireEffect>(UpdateOrder::Ability);
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
		// ������
		SmallStarFireEffect* StarStarEffect = GetLevel()->CreateActor<SmallStarFireEffect>(UpdateOrder::Ability);
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


	TriggerOneTimeAbility();


	// Star����ü �� �� �ʱ�ȭ
	CurrentAbilityStar = AbilityStar::Max;

	Star.SwallowedEnemyNumber = 0;
	Star.SwallowedPowerEnemyNumber = 0;



	ChangeAnimationState("GetAbility"); 
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
		IsFadeScreenRelease = true;

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
	BlockedByCeiling();
	BlockedByWall();

}



// Ŀ�� �Կ� ���� ������ ������
void Kirby::Contain_DamagedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	// ������ ü�°���
	if (m_KirbyHp > 0)
	{
		--m_KirbyHp;
	}


	// �鿪 On
	ImmuneState = true;

	// Ŀ�� ���� �浹ü Off
	KirbyBodyCollisonOff();



	// ���ظ� ������ �⺻ ���·�
	if (AbilityStar::Normal != Mode)
	{
		Mode = AbilityStar::Normal;
	}

	// �߷� �ʱ�ȭ
	GravityReset();

	// ƨ�ܳ���
	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = BOUNCINGOFF_XPOWER;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = -BOUNCINGOFF_XPOWER;
	}

	SetGravityVector(float4{ 0.0f , BOUNCINGOFF_YPOWER });


	ChangeAnimationState("Contain_Damaged");
}


void Kirby::Contain_DamagedUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > KIRBY_DAMAGED_STATETIME)
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
		else
		{
			int a = 0;
		}
	}



	// ���� ����� ����
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();



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

}