#include "Kirby.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "DustEffect.h"
#include "HitObjectEffect.h"
#include "ExhaleEffect.h"


void Kirby::Thorn_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Ability_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	GlobalContents::SpriteFileLoad("Ability_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	GlobalContents::SpriteFileLoad("Thorn_Left_Use.bmp", "Resources\\Unit\\Kirby", 4, 2);
	GlobalContents::SpriteFileLoad("Thorn_Right_Use.bmp", "Resources\\Unit\\Kirby", 4, 2);


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}


	MainRenderer->CreateAnimation("Thorn_Left_Idle", "Ability_Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Thorn_Right_Idle", "Ability_Right_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Thorn_Left_Walk", "Ability_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Thorn_Right_Walk", "Ability_Right_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Thorn_Left_Run", "Ability_Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Thorn_Right_Run", "Ability_Right_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Thorn_Left_Turn", "Ability_Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Thorn_Right_Turn", "Ability_Right_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Thorn_Left_Jump", "Ability_Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_Jump", "Ability_Right_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_AerialMotion", "Ability_Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Thorn_Right_AerialMotion", "Ability_Right_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Thorn_Left_Fall", "Ability_Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_Fall", "Ability_Right_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_AccelerateDown", "Ability_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_AccelerateDown", "Ability_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_Bounce", "Ability_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_Bounce", "Ability_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_Landing", "Ability_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_Landing", "Ability_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_LowerPosture", "Ability_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_LowerPosture", "Ability_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_LowerAttack", "Ability_Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_LowerAttack", "Ability_Right_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_HittheWall", "Ability_Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_HittheWall", "Ability_Right_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_HittheCeiling", "Ability_Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_HittheCeiling", "Ability_Right_Kirby.bmp", 91, 91, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_TakeOff", "Ability_Left_Kirby.bmp", 15, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_TakeOff", "Ability_Right_Kirby.bmp", 15, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Thorn_Left_Fly", "Ability_Left_Kirby.bmp", 19, 20, 0.2f, true);
	MainRenderer->CreateAnimation("Thorn_Right_Fly", "Ability_Right_Kirby.bmp", 19, 20, 0.2f, true);

	MainRenderer->CreateAnimation("Thorn_Left_ExhaleAttack", "Ability_Left_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Thorn_Right_ExhaleAttack", "Ability_Right_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Thorn_Left_UseSpecialAbility", "Thorn_Left_Use.bmp", 0, 5, 0.04f, false);
	MainRenderer->CreateAnimation("Thorn_Right_UseSpecialAbility", "Thorn_Right_Use.bmp", 0, 5, 0.04f, false);

	MainRenderer->CreateAnimation("Thorn_Left_ReleaseSpecialAbility", "Thorn_Left_Use.bmp", 5, 0, 0.04f, false);
	MainRenderer->CreateAnimation("Thorn_Right_ReleaseSpecialAbility", "Thorn_Right_Use.bmp", 5, 0, 0.04f, false);

	MainRenderer->CreateAnimation("Thorn_Left_Enter", "Ability_Left_Kirby.bmp", 93, 94, 0.1f, false);
	MainRenderer->CreateAnimation("Thorn_Right_Enter", "Ability_Right_Kirby.bmp", 93, 94, 0.1f, false);

	MainRenderer->CreateAnimationToFrame("Thorn_Left_GetAbility", "Thorn_Left_Use.bmp", { 0 , 1 , 2 , 3 , 4 , 5 , 4 , 3 , 2, 1 , 0 } , 0.04f, false);
	MainRenderer->CreateAnimationToFrame("Thorn_Right_GetAbility", "Thorn_Right_Use.bmp", { 0 , 1 , 2 , 3 , 4 , 5 , 4 , 3 , 2, 1 , 0 }, 0.04f, false);
	MainRenderer->FindAnimation("Thorn_Left_GetAbility")->Inters = { 0.04f ,0.04f ,0.04f ,0.04f ,1.0f ,0.04f ,0.04f ,0.04f ,0.04f , 0.04f };
	MainRenderer->FindAnimation("Thorn_Right_GetAbility")->Inters = { 0.04f ,0.04f ,0.04f ,0.04f ,1.0f ,0.04f ,0.04f ,0.04f ,0.04f , 0.04f };
}


void Kirby::ThornAbilityStart()
{
	if (nullptr == ThornEffectCollision)
	{
		MsgBoxAssert("가시모드 콜리전이 Null입니다.");
		return;
	}

	ThornEffectCollision->On();
}

void Kirby::ThornAbilityUpdate(float _Delta)
{
	StateTime += _Delta;


	if (nullptr == ThornEffectCollision)
	{
		MsgBoxAssert("가시모드 콜리전이 Null입니다.");
		return;
	}


	// 능력 최소 지속시간
	if (StateTime > AbilityMinDuration && false == IsChangeState)
	{
		IsChangeState = true;
	}


	// 'Z' 키 를 때면 능력 해제
	if (true == GameEngineInput::IsFree('Z') && true == IsChangeState)
	{

		ThornEffectCollision->Off();
		ChangeState(KirbyState::ReleaseSpecialAbility);
		return;
	}




	// 커비 충돌검사
	CheckKirbyCollision();


	// 능력 충돌 검사
	int DamageValue = GameEngineRandom::MainRandom.RandomInt(2, 3);
	CheckKirbyAbilityCollision(ThornEffectCollision, DamageValue);




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
	ContentsActor::DecelerationUpdate(_Delta, DecelerationSpeed);
	HorizontalUpdate(_Delta);
}


void Kirby::OneTimeThorn()
{
	if (nullptr == ThornEffectCollision)
	{
		MsgBoxAssert("가시 충돌체가 Null 입니다.");
		return;
	}

	ThornEffectCollision->On();
}