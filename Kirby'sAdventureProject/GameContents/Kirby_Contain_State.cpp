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



	// 데미지 상태 패턴
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
	


	// 데미지 상태 패턴
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



	// 데미지 상태 패턴
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
		// 별 효과
		CurrentSpeed = 0.0f;
	}
	if (true == CheckLeftWallBasedSpeed())
	{
		// 별 효과
		CurrentSpeed = 0.0f;
	}





	BlockedByGround();
	BlockedByWall();

	ActorUtils::DecelerationUpdate(_Delta, BRAKESPEED);
	HorizontalUpdate(_Delta);



	// 데미지 상태 패턴
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
		// 별 효과
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



	// 데미지 상태 패턴
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
		// 별효과
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWallBasedSpeed())
	{
		// 별효과
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



	// 데미지 상태 패턴
	CheckKirbyCollision();
}


void Kirby::Contain_GulpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	KeepDamagedState = KirbyState::Idle;
	ChangeKirbyBodyState(KirbyBodyState::Little);


	// 파워몹 하나라도 먹으면
	if (Star.SwallowedPowerEnemyNumber > 0)
	{
		GetAbilityEffectPtr = GetLevel()->CreateActor<GetAbilityEffect>(UpdateOrder::Other);
		if (nullptr == GetAbilityEffectPtr)
		{
			MsgBoxAssert("액터가 NULL 입니다");
			return;
		}

		GetAbilityEffectPtr->init(GetPos(), GetKirbyScale());


		// 능력을 얻는 도중에 모드 해제하면 터져서 변수 추가 
		GettingAbility = true;


		// Fade 설정
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}


		FadeObject* LevelFade = CurLevelPtr->CreateActor<FadeObject>(UpdateOrder::UI);
		if (nullptr == LevelFade)
		{
			MsgBoxAssert("생성한 액터가 Null 입니다.");
			return;
		}

		LevelFade->RequestFadeScreen(FadeAlphaValue);

		
		// 시간 설정
		GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Other, 1.0f);
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::UI, 1.0f);


		// 사운드 재생
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
			MsgBoxAssert("액터가 NULL 입니다.");
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
			MsgBoxAssert("액터가 NULL 입니다.");
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



	// 데미지 상태 패턴
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



	// 데미지 상태 패턴
	CheckKirbyCollision();
}


///////////////////////////////////

void Kirby::StarAttack()
{
	float4 UnitDir = GetDirUnitVector();

	if (Star.SwallowedEnemyNumber >= 2)
	{
		// 큰별
		LargeStarFireEffect* LargeStarEffect = GetLevel()->CreateActor<LargeStarFireEffect>(UpdateOrder::Ability);
		if (nullptr == LargeStarEffect)
		{
			MsgBoxAssert("액터가 NULL 입니다.");
			return;
		}

		LargeStarEffect->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
		LargeStarEffect->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);


		// 사운드 재생
		GameEngineSound::SoundPlay("Kirby_LargeStarAttack.wav");
	}
	else if (1 == Star.SwallowedEnemyNumber)
	{
		// 작은별
		SmallStarFireEffect* StarStarEffect = GetLevel()->CreateActor<SmallStarFireEffect>(UpdateOrder::Ability);
		if (nullptr == StarStarEffect)
		{
			MsgBoxAssert("액터가 NULL 입니다.");
			return;
		}

		StarStarEffect->init(CurrentLevelBitMapFileName, GetPos(), GetKirbyScale(), GetDirUnitVector());
		StarStarEffect->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect, float4{ 12.0f , 12.0f });


		// 사운드 재생
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
		// 랜덤 모드로 대체될 예정
		Mode = CurrentAbilityStar;
	}
	else
	{
		MsgBoxAssert("삼킨 파워몬스터가 없는데 능력을 얻을려고 했습니다.");
		return;
	}


	TriggerOneTimeAbility();


	// Star구조체 및 별 초기화
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
			MsgBoxAssert("충돌체가 Null 입니다.");
			return;
		}

		if (nullptr == SparkEffectCollision)
		{
			MsgBoxAssert("충돌체가 Null 입니다.");
			return;
		}

		// 시간다되면 특수 능력 Off
		ThornEffectCollision->Off();
		SparkEffectCollision->Off();
		IsChangeState = true;
	}



	// 지속적인 능력만 따로 해주는 함수
	TriggerMultiTimeAbility(_Delta);


	if (true == IsChangeState)
	{
		// Fade 해제
		IsFadeScreenRelease = true;

		// 시간 Delta Reset
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);


		GettingAbility = false;
		

		// 바닥이 있고 속도가 0이면 Idle
		if (true == GetGroundState() && 0 == CurrentSpeed)
		{
			ChangeState(KirbyState::Idle);
			return;
		}

		// 바닥이 있고 속도가 있으면 Walk
		if (true == GetGroundState() && 0 != CurrentSpeed)
		{
			ChangeState(KirbyState::Walk);
			return;
		}

		// 체공 상태이면 Fall
		if (false == GetGroundState())
		{
			ChangeState(KirbyState::Fall);
			return;
		}
	}




	// 맵 블락
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();

}



// 커비 입에 뭔가 있을때 데미지
void Kirby::Contain_DamagedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	// 맞으면 체력감소
	if (m_KirbyHp > 0)
	{
		--m_KirbyHp;
	}


	// 면역 On
	ImmuneState = true;

	// 커비 몸통 충돌체 Off
	KirbyBodyCollisonOff();



	// 피해를 입으면 기본 상태로
	if (AbilityStar::Normal != Mode)
	{
		Mode = AbilityStar::Normal;
	}

	// 중력 초기화
	GravityReset();

	// 튕겨나감
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



	// 맵을 벗어나지 못함
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();



	// 체공상태일 때 중력 적용
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}


	// 감속
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

}