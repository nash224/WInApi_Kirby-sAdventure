#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "GlobalContents.h"
#include "FrameBreathEffect.h"
#include "IceBreathEffect.h"



void Kirby::Ice_StateResourceLoad()
{
	GlobalContents::SpriteFileLoad("Ice_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	GlobalContents::SpriteFileLoad("Ice_Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	GlobalContents::SpriteFileLoad("Ability_Left_Use.bmp", "Resources\\Unit\\Kirby", 3, 3);
	GlobalContents::SpriteFileLoad("Ability_Right_Use.bmp", "Resources\\Unit\\Kirby", 3, 3);


	MainRenderer->CreateAnimation("Ice_Left_Idle", "Ice_Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Ice_Right_Idle", "Ice_Right_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Ice_Left_Walk", "Ice_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Ice_Right_Walk", "Ice_Right_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Ice_Left_Run", "Ice_Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Ice_Right_Run", "Ice_Right_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Ice_Left_Turn", "Ice_Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Ice_Right_Turn", "Ice_Right_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Ice_Left_Jump", "Ice_Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_Jump", "Ice_Right_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_AerialMotion", "Ice_Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Ice_Right_AerialMotion", "Ice_Right_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Ice_Left_Fall", "Ice_Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_Fall", "Ice_Right_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_AccelerateDown", "Ice_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_AccelerateDown", "Ice_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_Bounce", "Ice_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_Bounce", "Ice_Right_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_Landing", "Ice_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_Landing", "Ice_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_LowerPosture", "Ice_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_LowerPosture", "Ice_Right_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_LowerAttack", "Ice_Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_LowerAttack", "Ice_Right_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_HittheWall", "Ice_Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_HittheWall", "Ice_Right_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_HittheCeiling", "Ice_Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_HittheCeiling", "Ice_Right_Kirby.bmp", 91, 91, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_TakeOff", "Ice_Left_Kirby.bmp", 15, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_TakeOff", "Ice_Right_Kirby.bmp", 15, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_Fly", "Ice_Left_Kirby.bmp", 19, 20, 0.2f, true);
	MainRenderer->CreateAnimation("Ice_Right_Fly", "Ice_Right_Kirby.bmp", 19, 20, 0.2f, true);

	MainRenderer->CreateAnimation("Ice_Left_ExhaleAttack", "Ice_Left_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Ice_Right_ExhaleAttack", "Ice_Right_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Ice_Left_Enter", "Ice_Left_Kirby.bmp", 93, 94, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_Enter", "Ice_Right_Kirby.bmp", 93, 94, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_UseSpecialAbility", "Ice_Left_Kirby.bmp", 16, 16, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_UseSpecialAbility", "Ice_Right_Kirby.bmp", 16, 16, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_ReleaseSpecialAbility", "Ice_Left_Kirby.bmp", 16, 16, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_ReleaseSpecialAbility", "Ice_Right_Kirby.bmp", 16, 16, 0.1f, false);

	MainRenderer->CreateAnimation("Ice_Left_GetAbility", "Ice_Left_Kirby.bmp", 16, 16, 0.1f, false);
	MainRenderer->CreateAnimation("Ice_Right_GetAbility", "Ice_Right_Kirby.bmp", 16, 16, 0.1f, false);



	GlobalContents::SoundFileLoad("Kirby_IceAttack.wav", "Resources\\SoundResources\\EffectVoice");
	
}


void Kirby::IceAbilityStart()
{
	Duration = 0.0f;
	IceSoundTime = 1.0f;
}

void Kirby::IceAbilityUpdate(float _Delta)
{
	StateTime += _Delta;
	Duration += _Delta;
	IceSoundTime += _Delta;

	if (IceSoundTime > IceSoundCycle)
	{
		IceSoundTime = 0.0f;

		GameEngineSound::SoundPlay("Kirby_IceAttack.wav");
	}


	// 능력 최소 지속시간
	if (Duration > AbilityMinDuration && false == IsChangeState)
	{
		IsChangeState = true;
	}

	// 쿨이 돌아오면 아이스 브레스 하나 소환
	if (StateTime > KIRBYFRAMEEFFECTCREATECYCLE)
	{
		StateTime = 0.0f;

		IceBreathEffect* IceBreathEffectPtr = GetLevel()->CreateActor<IceBreathEffect>(UpdateOrder::Ability);

		if (nullptr == IceBreathEffectPtr)
		{
			MsgBoxAssert("액터가 Null입니다.");
			return;
		}

		IceBreathEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
		IceBreathEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
		IceBreathEffectPtr->SetGroundTexture(CurrentLevelBitMapFileName);
	}


	// Z를 때면 능력 해제
	if (true == GameEngineInput::IsFree('Z') && true == IsChangeState)
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
	ContentsActor::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);
}






void Kirby::TriggerIceAbilityAfterProcess(float _Delta)
{
	IceTime += _Delta;
	IceSoundTime += _Delta;

	if (IceSoundTime > IceSoundCycle)
	{
		IceSoundTime = 0.0f;

		GameEngineSound::SoundPlay("Kirby_IceAttack.wav");
	}

	if (IceTime > KIRBYFRAMEEFFECTCREATECYCLE)
	{
		IceTime = 0.0f;

		IceBreathEffect* IceBreathEffectPtr = GetLevel()->CreateActor<IceBreathEffect>(UpdateOrder::UI);

		if (nullptr == IceBreathEffectPtr)
		{
			MsgBoxAssert("액터가 Null입니다.");
			return;
		}

		IceBreathEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
		IceBreathEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
		IceBreathEffectPtr->SetGroundTexture(CurrentLevelBitMapFileName);
	}

}