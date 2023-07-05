#include "Kirby.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GlobalContents.h"



void Kirby::Sword_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Sword_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 8, 7);
	GlobalContents::SpriteFileLoad("Sword_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 8, 7);

	MainRenderer->CreateAnimation("Sword_Left_Idle", "Sword_Left_Kirby.bmp", 8, 8, 0.5f, true);
	MainRenderer->CreateAnimation("Sword_Right_Idle", "Sword_Right_Kirby.bmp", 8, 8, 0.5f, true);

	MainRenderer->CreateAnimation("Sword_Left_Walk", "Sword_Left_Kirby.bmp", 12, 9, 0.2f, true);
	MainRenderer->CreateAnimation("Sword_Right_Walk", "Sword_Right_Kirby.bmp", 12, 9, 0.2f, true);

	MainRenderer->CreateAnimation("Sword_Left_Run", "Sword_Left_Kirby.bmp", 12, 9, 0.1f, true);
	MainRenderer->CreateAnimation("Sword_Right_Run", "Sword_Right_Kirby.bmp", 12, 9, 0.1f, true);

	MainRenderer->CreateAnimation("Sword_Left_Turn", "Sword_Left_Kirby.bmp", 49, 49, 0.05f, false);
	MainRenderer->CreateAnimation("Sword_Right_Turn", "Sword_Right_Kirby.bmp", 49, 49, 0.05f, false);

	MainRenderer->CreateAnimation("Sword_Left_Jump", "Sword_Left_Kirby.bmp", 17, 17, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_Jump", "Sword_Right_Kirby.bmp", 17, 17, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_AerialMotion", "Sword_Left_Kirby.bmp", 17, 17, 0.05f, false);
	MainRenderer->CreateAnimation("Sword_Right_AerialMotion", "Sword_Right_Kirby.bmp", 17, 17, 0.05f, false);

	MainRenderer->CreateAnimation("Sword_Left_Fall", "Sword_Left_Kirby.bmp", 17, 17, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_Fall", "Sword_Right_Kirby.bmp", 17, 17, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_AccelerateDown", "Sword_Left_Kirby.bmp", 18, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_AccelerateDown", "Sword_Right_Kirby.bmp", 18, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_Bounce", "Sword_Left_Kirby.bmp", 18, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_Bounce", "Sword_Right_Kirby.bmp", 18, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_Landing", "Sword_Left_Kirby.bmp", 14, 14, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_Landing", "Sword_Right_Kirby.bmp", 14, 14, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_LowerPosture", "Sword_Left_Kirby.bmp", 14, 14, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_LowerPosture", "Sword_Right_Kirby.bmp", 14, 14, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_LowerAttack", "Sword_Left_Kirby.bmp", 15, 16, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_LowerAttack", "Sword_Right_Kirby.bmp", 15, 16, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_HittheWall", "Sword_Left_Kirby.bmp", 48, 48, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_HittheWall", "Sword_Right_Kirby.bmp", 48, 48, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_HittheCeiling", "Sword_Left_Kirby.bmp", 50, 50, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_HittheCeiling", "Sword_Right_Kirby.bmp", 50, 50, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_TakeOff", "Sword_Left_Kirby.bmp", 19, 22, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_TakeOff", "Sword_Right_Kirby.bmp", 19, 22, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_Fly", "Sword_Left_Kirby.bmp", 23, 24, 0.2f, true);
	MainRenderer->CreateAnimation("Sword_Right_Fly", "Sword_Right_Kirby.bmp", 23, 24, 0.2f, true);

	MainRenderer->CreateAnimation("Sword_Left_ExhaleAttack", "Sword_Left_Kirby.bmp", 25, 28, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Sword_Right_ExhaleAttack", "Sword_Right_Kirby.bmp", 25, 28, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Sword_Left_UseSpecialAbility", "Sword_Left_Kirby.bmp", 29, 38, 0.03f, false);
	MainRenderer->CreateAnimation("Sword_Right_UseSpecialAbility", "Sword_Right_Kirby.bmp", 29, 38, 0.03f, false);

	MainRenderer->CreateAnimation("Sword_Left_AerialUseSpecialAbility", "Sword_Left_Kirby.bmp", 40, 47, 0.03f, false);
	MainRenderer->CreateAnimation("Sword_Right_AerialUseSpecialAbility", "Sword_Right_Kirby.bmp", 40, 47, 0.03f, false);

	MainRenderer->CreateAnimation("Sword_Left_ReleaseSpecialAbility", "Sword_Left_Kirby.bmp", 39, 39, 0.03f, false);
	MainRenderer->CreateAnimation("Sword_Right_ReleaseSpecialAbility", "Sword_Right_Kirby.bmp", 39, 39, 0.03f, false);

	MainRenderer->CreateAnimation("Sword_Left_Enter", "Sword_Left_Kirby.bmp", 51, 52, 0.1f, false);
	MainRenderer->CreateAnimation("Sword_Right_Enter", "Sword_Right_Kirby.bmp", 51, 52, 0.1f, false);

	MainRenderer->CreateAnimation("Sword_Left_GetAbility", "Sword_Left_Kirby.bmp", 0, 7, 0.04f, false);
	MainRenderer->CreateAnimation("Sword_Right_GetAbility", "Sword_Right_Kirby.bmp", 0, 7, 0.04f, false);



	GlobalContents::SoundFileLoad("SwordKnight_AttackSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("SwordAieralAttack.wav", "Resources\\SoundResources\\EffectVoice");
}


void Kirby::SwordAbilityStart()
{
	if (nullptr == SwordEffectCollision)
	{
		MsgBoxAssert("번개모드 콜리전이 Null입니다.");
		return;
	}

	GameEngineSound::SoundPlay("SwordKnight_AttackSound.wav");


	float SwordCollisionAdjustment = 0.0f;
	if (ActorDir::Left == Dir)
	{
		SwordCollisionAdjustment = -40.0f;
	}
	else if (ActorDir::Right == Dir)
	{
		SwordCollisionAdjustment = 40.0f;
	}

	SwordEffectCollision->SetCollisionPos(float4{ SwordCollisionAdjustment , -SmallTypeScale.Half().Y});
	SwordEffectCollision->On();
}

void Kirby::SwordAbilityUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}




	if (true == IsChangeState)
	{
		if (nullptr == SwordEffectCollision)
		{
			MsgBoxAssert("번개모드 콜리전이 Null입니다.");
			return;
		}

		SwordEffectCollision->Off();
		ChangeState(KirbyState::ReleaseSpecialAbility);
		return;
	}





	// 데미지 상태 패턴
	CheckKirbyCollision();

	// 능력 충돌 검사
	int DamageValue = GameEngineRandom::MainRandom.RandomInt(2, 4);
	CheckKirbyAbilityCollision(SwordEffectCollision, DamageValue);





	MoveHorizontal(WALKSPEED, _Delta);


	// 지형락
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();



	// 발이 땅에 있을 때 중력적용 x
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}


	// X축 속도 업데이트
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
}



void Kirby::AerialUseSpecialAbilityStart()
{
	IsChangeState = false;

	if (nullptr == AerialSwordEffectCollision)
	{
		MsgBoxAssert("번개모드 콜리전이 Null입니다.");
		return;
	}

	AerialSwordEffectCollision->On();



	GameEngineSound::SoundPlay("SwordAieralAttack.wav");

	ChangeAnimationState("AerialUseSpecialAbility");
}

void Kirby::AerialUseSpecialAbilityUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (true == MainRenderer->IsAnimationEnd() || true == GetGroundState())
	{
		IsChangeState = true;
	}




	if (true == IsChangeState)
	{
		if (nullptr == AerialSwordEffectCollision)
		{
			MsgBoxAssert("번개모드 콜리전이 Null입니다.");
			return;
		}

		AerialSwordEffectCollision->Off();
		ChangeState(KirbyState::ReleaseSpecialAbility);
		return;
	}





	// 데미지 상태 패턴
	CheckKirbyCollision();

	// 능력 충돌 검사
	int DamageValue = GameEngineRandom::MainRandom.RandomInt(2, 4);
	CheckKirbyAbilityCollision(AerialSwordEffectCollision, DamageValue);


	MoveHorizontal(WALKSPEED, _Delta);


	// 지형락
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();



	// 발이 땅에 있을 때 중력적용 x
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}


	// X축 속도 업데이트
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);
}