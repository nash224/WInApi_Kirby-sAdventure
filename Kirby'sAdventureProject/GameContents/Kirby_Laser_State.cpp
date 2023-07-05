#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"
#include "LaserEffect.h"


void Kirby::Laser_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Ability_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	GlobalContents::SpriteFileLoad("Ability_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	GlobalContents::SpriteFileLoad("Ability_Left_Use.bmp", "Resources\\Unit\\Kirby", 3, 3);
	GlobalContents::SpriteFileLoad("Ability_Right_Use.bmp", "Resources\\Unit\\Kirby", 3, 3);


	MainRenderer->CreateAnimation("Laser_Left_Idle", "Ability_Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Laser_Right_Idle", "Ability_Right_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Laser_Left_Walk", "Ability_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Laser_Right_Walk", "Ability_Right_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Laser_Left_Run", "Ability_Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Laser_Right_Run", "Ability_Right_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Laser_Left_Turn", "Ability_Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Laser_Right_Turn", "Ability_Right_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Laser_Left_Jump", "Ability_Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_Jump", "Ability_Right_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_AerialMotion", "Ability_Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Laser_Right_AerialMotion", "Ability_Right_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Laser_Left_Fall", "Ability_Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_Fall", "Ability_Right_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_AccelerateDown", "Ability_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_AccelerateDown", "Ability_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_Bounce", "Ability_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_Bounce", "Ability_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_Landing", "Ability_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_Landing", "Ability_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_LowerPosture", "Ability_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_LowerPosture", "Ability_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_LowerAttack", "Ability_Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_LowerAttack", "Ability_Right_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_HittheWall", "Ability_Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_HittheWall", "Ability_Right_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_HittheCeiling", "Ability_Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_HittheCeiling", "Ability_Right_Kirby.bmp", 91, 91, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_TakeOff", "Ability_Left_Kirby.bmp", 15, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_TakeOff", "Ability_Right_Kirby.bmp", 15, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_Fly", "Ability_Left_Kirby.bmp", 19, 20, 0.2f, true);
	MainRenderer->CreateAnimation("Laser_Right_Fly", "Ability_Right_Kirby.bmp", 19, 20, 0.2f, true);

	MainRenderer->CreateAnimation("Laser_Left_ExhaleAttack", "Ability_Left_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Laser_Right_ExhaleAttack", "Ability_Right_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Laser_Left_UseSpecialAbility", "Ability_Left_Use.bmp", 7, 7, 0.04f, false);
	MainRenderer->CreateAnimation("Laser_Right_UseSpecialAbility", "Ability_Right_Use.bmp", 7, 7, 0.04f, false);

	MainRenderer->CreateAnimation("Laser_Left_ReleaseSpecialAbility", "Ability_Left_Use.bmp", 8, 8, 0.04f, false);
	MainRenderer->CreateAnimation("Laser_Right_ReleaseSpecialAbility", "Ability_Right_Use.bmp", 8, 8, 0.04f, false);

	MainRenderer->CreateAnimation("Laser_Left_Enter", "Ability_Left_Kirby.bmp", 93, 94, 0.1f, false);
	MainRenderer->CreateAnimation("Laser_Right_Enter", "Ability_Right_Kirby.bmp", 93, 94, 0.1f, false);

	MainRenderer->CreateAnimation("Laser_Left_GetAbility", "Ability_Left_Use.bmp", 7, 8, 0.04f, true);
	MainRenderer->CreateAnimation("Laser_Right_GetAbility", "Ability_Right_Use.bmp", 7, 8, 0.04f, true);
}


void Kirby::LaserAbilityStart()
{
	// 레이저 소환
	LaserEffect* LaserEffectPtr = GetLevel()->CreateActor<LaserEffect>();
	if (nullptr == LaserEffectPtr)
	{
		MsgBoxAssert("Null인 액터에 참조하려고 했습니다.");
		return;
	}

	LaserEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());

	LaserEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
}

void Kirby::LaserAbilityUpdate(float _Delta)
{
	// Laser 모션이 끝나면 능력 해제
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(KirbyState::ReleaseSpecialAbility);
		return;
	}



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



void Kirby::OneTimeLaser()
{
	// 레이저 소환
	LaserEffect* LaserEffectPtr = GetLevel()->CreateActor<LaserEffect>(UpdateOrder::UI);
	if (nullptr == LaserEffectPtr)
	{
		MsgBoxAssert("Null인 액터에 참조하려고 했습니다.");
		return;
	}

	LaserEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
	LaserEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
}

