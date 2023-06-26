#include "Kirby.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GlobalContents.h"
#include "KirbySparkEffect.h"


void Kirby::Spark_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Ability_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	GlobalContents::SpriteFileLoad("Ability_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	GlobalContents::SpriteFileLoad("Ability_Left_Use.bmp", "Resources\\Unit\\Kirby", 3, 3);
	GlobalContents::SpriteFileLoad("Ability_Right_Use.bmp", "Resources\\Unit\\Kirby", 3, 3);

	MainRenderer->CreateAnimation("Spark_Left_Idle", "Ability_Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Spark_Right_Idle", "Ability_Right_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Spark_Left_Walk", "Ability_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Spark_Right_Walk", "Ability_Right_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Spark_Left_Run", "Ability_Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Spark_Right_Run", "Ability_Right_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Spark_Left_Turn", "Ability_Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Spark_Right_Turn", "Ability_Right_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Spark_Left_Jump", "Ability_Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_Jump", "Ability_Right_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_AerialMotion", "Ability_Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Spark_Right_AerialMotion", "Ability_Right_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Spark_Left_Fall", "Ability_Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_Fall", "Ability_Right_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_AccelerateDown", "Ability_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_AccelerateDown", "Ability_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_Bounce", "Ability_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_Bounce", "Ability_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_Landing", "Ability_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_Landing", "Ability_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_LowerPosture", "Ability_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_LowerPosture", "Ability_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_LowerAttack", "Ability_Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_LowerAttack", "Ability_Right_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_HittheWall", "Ability_Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_HittheWall", "Ability_Right_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_HittheCeiling", "Ability_Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_HittheCeiling", "Ability_Right_Kirby.bmp", 91, 91, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_TakeOff", "Ability_Left_Kirby.bmp", 15, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_TakeOff", "Ability_Right_Kirby.bmp", 15, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_Fly", "Ability_Left_Kirby.bmp", 19, 20, 0.2f, true);
	MainRenderer->CreateAnimation("Spark_Right_Fly", "Ability_Right_Kirby.bmp", 19, 20, 0.2f, true);

	MainRenderer->CreateAnimation("Spark_Left_ExhaleAttack", "Ability_Left_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Spark_Right_ExhaleAttack", "Ability_Right_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Spark_Left_UseSpecialAbility", "Ability_Left_Use.bmp", 1, 2, 0.1f, true);
	MainRenderer->CreateAnimation("Spark_Right_UseSpecialAbility", "Ability_Right_Use.bmp", 1, 2, 0.1f, true);

	MainRenderer->CreateAnimation("Spark_Left_ReleaseSpecialAbility", "Ability_Left_Use.bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_ReleaseSpecialAbility", "Ability_Right_Use.bmp", 0, 0, 0.1f, false);

	MainRenderer->CreateAnimation("Spark_Left_Enter", "Ability_Left_Kirby.bmp", 93, 94, 0.1f, false);
	MainRenderer->CreateAnimation("Spark_Right_Enter", "Ability_Right_Kirby.bmp", 93, 94, 0.1f, false);

	MainRenderer->CreateAnimationToFrame("Spark_Left_GetAbility", "Ability_Left_Use.bmp", { 0 ,1 , 2 , 1 , 2 , 1 , 2 , 1 , 2 , 0 }, 0.1f, false);
	MainRenderer->CreateAnimationToFrame("Spark_Right_GetAbility", "Ability_Right_Use.bmp", { 0 ,1 , 2 , 1 , 2 , 1 , 2 , 1 , 2 ,0 }, 0.1f, false);

}


void Kirby::SparkAbilityStart()
{
	Duration = 0.0f;

	if (nullptr == SparkEffectCollision)
	{
		MsgBoxAssert("번개모드 콜리전이 Null입니다.");
		return;
	}

	SparkEffectCollision->On();
}

void Kirby::SparkAbilityUpdate(float _Delta)
{
	StateTime += _Delta;
	Duration += _Delta;

	// 능력 최소 지속시간
	if (Duration > AbilityMinDuration && false == IsChangeState)
	{
		IsChangeState = true;
	}


	// 스킬 쿨타임이 돌았으면 변개 효과
	if (StateTime > KIRBYSPARKEFFECTCREATECYCLE)
	{
		StateTime = 0.0f;

		KirbySparkEffect* KirbySparkEffectPtr = GetLevel()->CreateActor<KirbySparkEffect>(UpdateOrder::Ability);
		if (nullptr == KirbySparkEffectPtr)
		{
			MsgBoxAssert("액터가 Null일리가 없어..");
			return;
		}

		KirbySparkEffectPtr->init(GetPos(), GetKirbyScale());
	}



	// 'Z' 키를 때면 능력 해제
	if (true == GameEngineInput::IsFree('Z') && true == IsChangeState)
	{
		if (nullptr == SparkEffectCollision)
		{
			MsgBoxAssert("번개모드 콜리전이 Null입니다.");
			return;
		}

		SparkEffectCollision->Off();
		ChangeState(KirbyState::ReleaseSpecialAbility);
		return;
	}





	// 데미지 상태 패턴
	CheckKirbyCollision();

	// 능력 충돌 검사
	int DamageValue = GameEngineRandom::MainRandom.RandomInt(1, 3);
	CheckKirbyAbilityCollision(SparkEffectCollision, DamageValue);



	// 지형락
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();



	// 발이 땅에 있을 때 중력적용 x
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}


	// X축 속도 업데이트
	ContentsActor::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);
}