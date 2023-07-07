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
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
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
	


	// 데미지 상태 패턴
	CheckKirbyCollision();
}


void Kirby::Contain_RunStart()
{
	StateTime = 0.0f;

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	// 먼지 이펙트
	DustEffect* DustEffectPtr = CurLevelPtr->CreateActor<DustEffect>(UpdateOrder::Ability);
	if (nullptr == DustEffectPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	DustEffectPtr->init(GetPos(), GetKirbyScale(), -GetDirUnitVector());


	// 사운드 재생
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
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

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	// 먼지 이펙트
	DustEffect* DustEffectPtr = CurLevelPtr->CreateActor<DustEffect>(UpdateOrder::Ability);
	if (nullptr == DustEffectPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
	}

	DustEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());


	// 사운드 재생
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
	BlockedByAll();


	ActorUtils::DecelerationUpdate(_Delta, BreakSpeed);
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


	// 사운드 재생
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		HitObjectEffectPtr->init(GetPos(), float4::ZERO);

		GravityReset();
	}

	// 점프 가능 거리 로직
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
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
		if (nullptr == HitObjectEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}
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



	// 데미지 상태 패턴
	CheckKirbyCollision();


	// 추락 Miss
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


	// 파워몹 하나라도 먹으면
	if (Star.SwallowedPowerEnemyNumber > 0)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}


		// 모드 변환 이펙트
		GetAbilityEffectPtr = CurLevelPtr->CreateActor<GetAbilityEffect>(UpdateOrder::Other);
		if (nullptr == GetAbilityEffectPtr)
		{
			MsgBoxAssert("액터가 NULL 입니다");
			return;
		}

		GetAbilityEffectPtr->init(GetPos(), GetKirbyScale());


		// 능력을 얻는 도중에 모드 해제하면 터져서 변수 추가 
		GettingAbility = true;


		// Fade 설정
		// Fade 해제해줄 때까지 On상태 => GetAbility 패턴에서 해제
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}


		// 작은 별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
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
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은 별 이펙트
		HitObjectEffect* HitObjectEffectPtr = CurLevelPtr->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
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
	BlockedByAll();


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

	// 별 소환
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



	// 데미지 상태 패턴
	CheckKirbyCollision();


	// 추락 Miss
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
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 큰별
		LargeStarFireEffect* LargeStarEffect = CurLevelPtr->CreateActor<LargeStarFireEffect>(UpdateOrder::Ability);
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
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		// 작은별
		SmallStarFireEffect* StarStarEffect = CurLevelPtr->CreateActor<SmallStarFireEffect>(UpdateOrder::Ability);
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

	// 한번만 쏘는 능력일 경우
	TriggerOneTimeAbility();


	// Star구조체 및 별 초기화
	CurrentAbilityStar = AbilityStar::Max;

	Star.SwallowedEnemyNumber = 0;
	Star.SwallowedPowerEnemyNumber = 0;


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	// Sword만 스프라이트 크기가 다름
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
		FadeObject::IsFadeScreenRelease = true;

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





// 커비 입에 뭔가 있을때 데미지
void Kirby::Contain_DamagedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	// 레벨에 요청
	// 지진요청
	++VegetableValleyPlayLevel::Camera_ShakeCount;
	

	// UI에 요청
	// 점수
	if (nullptr == UIManagerPtr)
	{
		MsgBoxAssert("UI를 불러오지 못했습니다.");
		return;
	}

	if ("PlayUI" == UIManagerPtr->GetName())
	{
		PlayUI::PlayUI_Score += 50;
	}

	// 맞으면 체력감소
	if (m_KirbyHp > 0)
	{
		--m_KirbyHp;
	}


	// 면역 On
	ImmuneState = true;

	// 커비 몸통 충돌체 Off
	KirbyBodyCollisonOff();



	// 중력 초기화
	GravityReset();

	// 튕겨나감
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
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
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



	// 맵을 벗어나지 못함
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();



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


	// 추락 Miss
	if (GetPos().Y > CurrentBackGroundScale.Y - CHECKGAP)
	{
		ChangeState(KirbyState::Miss);
		return;
	}
}