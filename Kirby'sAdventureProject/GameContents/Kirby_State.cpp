#include "Kirby.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>


#include "GlobalContents.h"
#include "UIManager.h"
#include "VegetableValleyPlayLevel.h"
#include "DustEffect.h"
#include "HitObjectEffect.h"
#include "FadeObject.h"
#include "ExhaleEffect.h"
#include "KirbyDeathEffect.h"
#include "Boss.h"


void Kirby::Normal_StateResourceLoad()
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}



	GlobalContents::SpriteFileLoad("Normal_Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	GlobalContents::SpriteFileLoad("Normal_RIght_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	MainRenderer->CreateAnimation("Normal_Left_Idle", "Normal_Left_Kirby.bmp", 0, 1, 0.1f, true);
	MainRenderer->CreateAnimation("Normal_Right_Idle", "Normal_RIght_Kirby.bmp", 0, 1, 0.1f, true);

	MainRenderer->CreateAnimation("Normal_Left_Walk", "Normal_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Walk", "Normal_RIght_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Left_Run", "Normal_Left_Kirby.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Normal_Right_Run", "Normal_RIght_Kirby.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Normal_Left_Turn", "Normal_Left_Kirby.bmp", 12, 12, 0.05f, false);
	MainRenderer->CreateAnimation("Normal_Right_Turn", "Normal_RIght_Kirby.bmp", 12, 12, 0.05f, false);

	MainRenderer->CreateAnimation("Normal_Left_Jump", "Normal_Left_Kirby.bmp", 9, 9, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Jump", "Normal_RIght_Kirby.bmp", 9, 9, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_AerialMotion", "Normal_Left_Kirby.bmp", 10, 13, 0.05f, false);
	MainRenderer->CreateAnimation("Normal_Right_AerialMotion", "Normal_RIght_Kirby.bmp", 10, 13, 0.05f, false);

	MainRenderer->CreateAnimation("Normal_Left_Fall", "Normal_Left_Kirby.bmp", 13, 13, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Fall", "Normal_RIght_Kirby.bmp", 13, 13, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_AccelerateDown", "Normal_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_AccelerateDown", "Normal_RIght_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Bounce", "Normal_Left_Kirby.bmp", 10, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Bounce", "Normal_RIght_Kirby.bmp", 10, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Landing", "Normal_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Landing", "Normal_RIght_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_LowerPosture", "Normal_Left_Kirby.bmp", 7, 7, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_LowerPosture", "Normal_RIght_Kirby.bmp", 7, 7, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_LowerAttack", "Normal_Left_Kirby.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_LowerAttack", "Normal_RIght_Kirby.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_HittheWall", "Normal_Left_Kirby.bmp", 92, 92, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_HittheWall", "Normal_RIght_Kirby.bmp", 92, 92, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_HittheCeiling", "Normal_Left_Kirby.bmp", 91, 91, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_HittheCeiling", "Normal_RIght_Kirby.bmp", 91, 91, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_TakeOff", "Normal_Left_Kirby.bmp", 15, 18, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_TakeOff", "Normal_RIght_Kirby.bmp", 15, 18, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Fly", "Normal_Left_Kirby.bmp", 19, 20, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_Fly", "Normal_RIght_Kirby.bmp", 19, 20, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Left_ExhaleAttack", "Normal_Left_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);
	MainRenderer->CreateAnimation("Normal_Right_ExhaleAttack", "Normal_RIght_Kirby.bmp", 21, 24, EXHALEATTACKTIME, false);

	MainRenderer->CreateAnimation("Normal_Left_UseSpecialAbility", "Normal_Left_Kirby.bmp", 24, 26, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_UseSpecialAbility", "Normal_RIght_Kirby.bmp", 24, 26, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_ReleaseSpecialAbility", "Normal_Left_Kirby.bmp", 25, 25, 0.15f, false);
	MainRenderer->CreateAnimation("Normal_Right_ReleaseSpecialAbility", "Normal_RIght_Kirby.bmp", 25, 25, 0.15f, false);

	MainRenderer->CreateAnimation("Normal_Left_Damaged", "Normal_Left_Kirby.bmp", 12, 10, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Damaged", "Normal_RIght_Kirby.bmp", 12, 10, 0.1f, false);

	MainRenderer->CreateAnimation("Normal_Left_Contain_Damaged", "Normal_Left_Kirby.bmp", 79, 79, 0.2f, false);
	MainRenderer->CreateAnimation("Normal_Right_Contain_Damaged", "Normal_RIght_Kirby.bmp", 79, 79, 0.2f, false);
	
	MainRenderer->CreateAnimation("Normal_Left_Enter", "Normal_Left_Kirby.bmp", 93, 94, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_Enter", "Normal_RIght_Kirby.bmp", 93, 94, 0.1f, false);




	GlobalContents::SpriteFileLoad("Kirby_Miss.bmp", "Resources\\Unit\\Kirby", 4, 1);

	MainRenderer->CreateAnimation("Normal_Right_Miss", "Kirby_Miss.bmp", 0, 0, 0.1f, false);
	MainRenderer->CreateAnimation("Normal_Right_MissRaiseUp", "Kirby_Miss.bmp", 0, 3, 0.1f, true);



	// ���� �ε�
	GlobalContents::SoundFileLoad("Kirby_Bounce.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_TurnSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_JumpSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_LowerSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_RunSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_SlidingSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_LandingSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_DropStar.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_TakeOffSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_ExhaleSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_StarAttackSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_LargeStarAttack.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_Hitted.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("NothingSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("GetAbility.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Kirby_Inhale.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Miss.wav", "Resources\\SoundResources\\EffectVoice");

	GlobalContents::SoundFileLoad("38_Miss.mp3", "Resources\\SoundResources\\SoundTrack");

}

// =============================================//



void Kirby::IdleStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Idle");
}

void Kirby::IdleUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}


	if (true == MainRenderer->IsAnimationEnd())
	{
		float OpenEyes = GameEngineRandom::MainRandom.RandomFloat(0.04f, 2.0f);
		MainRenderer->FindAnimation("Normal_Left_Idle")->Inters = { OpenEyes , 0.06f };
		MainRenderer->FindAnimation("Normal_Right_Idle")->Inters = { OpenEyes , 0.06f };
	}


	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		ChangeState(KirbyState::Enter);
		return;
	}


	if (false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::LowerPosture);
		return;
	}
	if (true == (GameEngineInput::IsDown('Z')))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}
	if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
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
	if ((true == CheckLeftWall() || true == CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
		return;
	}
	if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Walk);
		return;
	}




	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);





	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();

}


void Kirby::WalkStart()
{
	StateTime = 0.0f;
	KirbyDirCheck();
	ChangeAnimationState("Walk");
}

void Kirby::WalkUpdate(float _Delta)
{
	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		ChangeState(KirbyState::Enter);
		return;
	}

	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::LowerPosture);
		return;
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (CurrentSpeed < WALKMAXSPEED * 0.2f * _Delta && true == GameEngineInput::IsDown('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Run);
		return;
	}

	if (CurrentSpeed > WALKMAXSPEED * 0.2f * _Delta && true == GameEngineInput::IsDown('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if ((true == CheckLeftWall() || true == CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
		return;
	}

	if (CurrentSpeed == 0.0f && 
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
			(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Idle);
		return;
	}



	
	BlockedByGround();
	MoveHorizontal(WALKSPEED, _Delta);
	BlockedByWall();
	BlockedByAll();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::RunStart()
{
	StateTime = 0.0f;
	DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>(UpdateOrder::Ability);
	if (nullptr == DustEffectPtr)
	{
		MsgBoxAssert("���� ������ �����߽��ϴ�.");
		return;
	}

	DustEffectPtr->init(GetPos(), GetKirbyScale(), -GetDirUnitVector());



	// ���� ���
	GameEngineSound::SoundPlay("Kirby_RunSound.wav");


	KirbyDirCheck();
	ChangeAnimationState("Run");
}

void Kirby::RunUpdate(float _Delta)
{
	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		ChangeState(KirbyState::Enter);
		return;
	}

	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(KirbyState::LowerPosture);
		return;
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GameEngineInput::IsDown('X'))
	{
		ChangeState(KirbyState::Jump);
		return;
	}
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (CurrentSpeed > 0.0f && true == GameEngineInput::IsPress('A') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if (CurrentSpeed < 0.0f && true == GameEngineInput::IsPress('D') && false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Turn);
		return;
	}

	if ((true == CheckLeftWall() || true == CheckRightWall()) && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
		return;
	}

	if (CurrentSpeed == 0.0f &&
		((GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')) ||
			(GameEngineInput::IsFree('A') && GameEngineInput::IsFree('D'))))
	{
		ChangeState(KirbyState::Idle);
		return;
	}





	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	MoveHorizontal(RUNSPEED, _Delta);
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::TurnStart()
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
	if (nullptr == DustEffectPtr)
	{
		MsgBoxAssert("���� ������ ���� ���߽��ϴ�.");
		return;
	}

	DustEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_TurnSound.wav");


	ChangeAnimationState("Turn");
}

void Kirby::TurnUpdate(float _Delta)
{
	if (CurrentSpeed == 0.0f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	if (false == GetGroundState())
	{
		GravityReset();
		ChangeState(KirbyState::Fall);
		return;
	}

	if (true == CheckLeftWall() || true == CheckRightWall())
	{
		CurrentSpeed = 0.0f;
		ChangeState(KirbyState::HittheWall);
	}





	BlockedByGround();
	BlockedByWall();
	BlockedByAll();

	ActorUtils::DecelerationUpdate(_Delta, BRAKESPEED);
	HorizontalUpdate(_Delta);




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::JumpStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	KirbyDirCheck();
	GravityReset();


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_JumpSound.wav");


	ChangeAnimationState("Jump");
}

void Kirby::JumpUpdate(float _Delta)
{
	StateTime += _Delta;



	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		ChangeState(KirbyState::Enter);
		return;
	}



	if (true == GameEngineInput::IsFree('X') || true == IsReachedStarStick)
	{
		IsChangeState = true;
	}

	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (IsChangeState = true && 0.0f < GetGravityVector().Y)
	{
		ChangeState(KirbyState::AerialMotion);
		return;
	}

	if (true == CeilingCheck())
	{
		ChangeState(KirbyState::HittheCeiling);
		return;
	}







	float JumpPower = JUMPMAXDISTANCE / JUMPTIME;
	CurrentJumpDistance += JumpPower * _Delta;

	if (true == GameEngineInput::IsUp('X') || CurrentJumpDistance > JUMPMAXDISTANCE || true == IsReachedStarStick)
	{
		AbleJump = false;
	}

	if (true == GameEngineInput::IsPress('X') && CurrentJumpDistance < JUMPMAXDISTANCE && true == AbleJump)
	{
		SetGravityVector(float4::UP * JumpPower);
	}

	if (false == IsReachedStarStick)
	{
		MoveHorizontal(WALKSPEED, _Delta);
	}

	BlockedByCeiling();
	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	ChangeAnimationState("Jump");

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::AerialMotionStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	KirbyDirCheck();
	ChangeAnimationState("AerialMotion");
}

void Kirby::AerialMotionUpdate(float _Delta)
{
	StateTime += _Delta;

	IsChangeState = MainRenderer->IsAnimationEnd();



	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		ChangeState(KirbyState::Enter);
		return;
	}



	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (IsChangeState == true)
	{
		ChangeState(KirbyState::Fall);
	}
	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GetGroundState())
	{
		ChangeState(KirbyState::Landing);
	}

	if (true == CheckLeftWallBasedSpeed() && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
	}
	if (true == CheckRightWallBasedSpeed() && CurrentSpeed != 0.0f)
	{
		ChangeState(KirbyState::HittheWall);
	}


	if (false == IsReachedStarStick)
	{
		MoveHorizontal(WALKSPEED, _Delta);
	}


	BlockedByGround();
	BlockedByWall();
	BlockedByAll();

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::FallStart()
{
	StateTime = 0.0f;
	FallDistance = 0.0f;
	ChangeAnimationState("Fall");
}

void Kirby::FallUpdate(float _Delta)
{
	StateTime += _Delta;
	FallDistance += GetGravityVector().Y * _Delta;



	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		ChangeState(KirbyState::Enter);
		return;
	}




	if (FallDistance > FALLDISTANCE)
	{
		ChangeState(KirbyState::AccelerateDown);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}

	if (true == GetGroundState())
	{
		ChangeState(KirbyState::Landing);
		return;
	}

	if (true == CheckLeftWallBasedSpeed())
	{
		ChangeState(KirbyState::HittheWall);
	}
	if (true == CheckRightWallBasedSpeed())
	{
		ChangeState(KirbyState::HittheWall);
	}




	if (false == IsReachedStarStick)
	{
		MoveHorizontal(WALKSPEED, _Delta);
	}

	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	ChangeAnimationState("Fall");


	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);





	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}



	// ������ ���� ����
	CheckKirbyCollision();

	if (GetPos().Y > CurrentBackGroundScale.Y - CHECKGAP)
	{
		ChangeState(KirbyState::Miss);
		return;
	}
}


void Kirby::AccelerateDownStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("AccelerateDown");
}

void Kirby::AccelerateDownUpdate(float _Delta)
{
	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		ChangeState(KirbyState::Enter);
		return;
	}



	if (true == GetGroundState())
	{
		SetGravityVector(float4::UP * BOUNCEPOWER);
		ChangeState(KirbyState::Bounce);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::UseSpecialAbility);
		return;
	}

	if (true == (GameEngineInput::IsDown('W')))
	{
		ChangeState(KirbyState::TakeOff);
		return;
	}



	BlockedByGround();
	BlockedByWall();
	BlockedByAll();


	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}



	// ������ ���� ����
	CheckKirbyCollision();

	if (GetPos().Y > CurrentBackGroundScale.Y - CHECKGAP)
	{
		ChangeState(KirbyState::Miss);
		return;
	}
}


void Kirby::BounceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	if (nullptr == HitObjectEffectPtr)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	HitObjectEffectPtr->init(GetPos(), float4::ZERO);


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_Bounce.wav");

	ChangeAnimationState("Bounce");
}

void Kirby::BounceUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= 0.2f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Landing);
		return;
	}




	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();

	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
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


void Kirby::LandingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	if (nullptr == HitObjectEffectPtr)
	{
		MsgBoxAssert("����Ʈ ������ ���� ���߽��ϴ�.");
		return;
	}

	HitObjectEffectPtr->init(GetPos(), float4::ZERO);


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_LandingSound.wav");

	ChangeAnimationState("Landing");
}

void Kirby::LandingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= HITTHEMAPTIME)
	{
		IsChangeState = true;
	}


	if (true == IsReachedStarStick)
	{
		ChangeState(KirbyState::StageClearWalk);
		return;
	}



	if (0.0f == CurrentSpeed && true == IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	else if (0.0f != CurrentSpeed && true == IsChangeState)
	{
		ChangeState(KirbyState::Walk);
		return;
	}






	BlockedByWall();
	BlockedByGround();
	BlockedByAll();


	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);





	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::LowerPostureStart()
{
	StateTime = 0.0f;
	ChangeKirbyBodyState(KirbyBodyState::Lower);


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_LowerSound.wav");


	ChangeAnimationState("LowerPosture");
}

void Kirby::LowerPostureUpdate(float _Delta)
{

	if (false == GetGroundState())
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == GetGroundState() && (GameEngineInput::IsDown('Z') || GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::LowerAttack);
		return;
	}
	if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f == CurrentSpeed)
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		ChangeState(KirbyState::Idle);
		return;
	}
	if (true == GetGroundState() && true == GameEngineInput::IsFree('S') && 0.0f != CurrentSpeed)
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		ChangeState(KirbyState::Walk);
		return;
	}





	BlockedByWall();
	BlockedByGround();
	BlockedByAll();


	ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);





	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::LowerAttackStart()
{
	StateTime = 0.0f;
	IsChangeState = false; 
	Duration = 0.0f;


	// �ӵ� ����
	if (Dir == ActorDir::Left)
	{
		CurrentSpeed = -RUNMAXSPEED;
	}

	if (Dir == ActorDir::Right)
	{
		CurrentSpeed = RUNMAXSPEED;
	}


	// LowerCollison ��ġ ����
	float4 KirbyDirUnitVector = GetDirUnitVector();
	if (KirbyDirUnitVector.X < 0.0f)
	{
		KirbyDirUnitVector =
			float4{ -(LOWERATTACKCOLLISIONSCALE + LOWERTYPECOLLISIONSCALE).Half().X, -LOWERATTACKCOLLISIONSCALE.Half().Y };
	}
	else if (KirbyDirUnitVector.X > 0.0f)
	{
		KirbyDirUnitVector =
			float4{ (LOWERATTACKCOLLISIONSCALE + LOWERTYPECOLLISIONSCALE).Half().X, -LOWERATTACKCOLLISIONSCALE.Half().Y };
	}

	if (nullptr == LowerAttackCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�");
		return;
	}

	LowerAttackCollision->SetCollisionPos(KirbyDirUnitVector);

	LowerAttackCollision->On();



	// ���� ���
	GameEngineSound::SoundPlay("Kirby_SlidingSound.wav");


	ChangeAnimationState("LowerAttack");
}

void Kirby::LowerAttackUpdate(float _Delta)
{
	StateTime += _Delta;
	Duration += _Delta;


	if (nullptr == LowerAttackCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}


	// ���� ������ ���� �΋H��
	if (true == CheckLeftWall() || true == CheckRightWall())
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		LowerAttackCollision->Off();
		ChangeState(KirbyState::HittheWall);
		return;
	}

	// �����̵� �� �ٴ��� ������ ����
	if (false == GetGroundState())
	{
		GravityReset();
		ChangeKirbyBodyState(KirbyBodyState::Little);
		LowerAttackCollision->Off();
		ChangeState(KirbyState::Fall);
		return;
	}

	// �����̵��� ���� ���߸� ���̵�
	if (true == GetGroundState() && 0.0f == CurrentSpeed)
	{
		ChangeKirbyBodyState(KirbyBodyState::Little);
		LowerAttackCollision->Off();
		ChangeState(KirbyState::Idle);
		return;
	}


	// �����̵� �浹 �˻�
	std::vector<GameEngineCollision*> LowerAttackCol;
	if (true == LowerAttackCollision->Collision(CollisionOrder::MonsterBody, LowerAttackCol, CollisionType::Rect, CollisionType::Rect))
	{
		// ���� ��ȸ
		for (size_t i = 0; i < LowerAttackCol.size(); i++)
		{
			// ���� �ݸ��� ����
			GameEngineCollision* MonsterBodyPtr = LowerAttackCol[i];
			if (nullptr == MonsterBodyPtr)
			{
				MsgBoxAssert("������ Monster �� Null �Դϴ�.");
				return;
			}

			ActorUtils* Monster = dynamic_cast<ActorUtils*>(MonsterBodyPtr->GetActor());
			if (nullptr == Monster)
			{
				MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
				return;
			}

			// ���� ���� ���� Ʈ���� On
			Monster->IsHitted = true;
		}
		
	}




	// �����̵� ��ǿ��� ���� ȿ��
	if (Duration > LOWERATTACKDUSTOCCURRENCECYCLE)
	{
		Duration = 0.0f;

		DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>(UpdateOrder::Ability);
		if (nullptr == DustEffectPtr)
		{
			MsgBoxAssert("���Ͱ� Null �Դϴ�");
			return;
		}

		DustEffectPtr->init(GetPos(), GetKirbyScale(), -GetDirUnitVector());
	}


	// �� ���
	BlockedByWall();
	BlockedByGround();
	BlockedByAll();



	// X�� ���� �� ������Ʈ 
	if (StateTime > LOWERATTACKDECELECTIONSTARTTIME)
	{
		ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	}

	HorizontalUpdate(_Delta);




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();
}



void Kirby::HittheWallStart()
{
	StateTime = 0.0f;
	CurrentSpeed = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
	if (nullptr == HitObjectEffectPtr)
	{
		MsgBoxAssert("���� ������ ���� ���߽��ϴ�.");
		return;
	}

	HitObjectEffectPtr->init(GetPos(), float4::ZERO);


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_LandingSound.wav");

	ChangeAnimationState("HittheWall");
}

void Kirby::HittheWallUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HITTHEMAPTIME)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
	else if (false == GetGroundState() && true == IsChangeState)
	{
		ChangeState(KirbyState::Fall);
		return;
	}





	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}





	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}

	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::HittheCeilingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
	if (nullptr == HitObjectEffectPtr)
	{
		MsgBoxAssert("���� ������ ���� ���߽��ϴ�.");
		return;
	}

	HitObjectEffectPtr->init(GetPos(), float4::ZERO);


	// ���� ���
	GameEngineSound::SoundPlay("Kirby_LandingSound.wav");


	ChangeAnimationState("HittheCeiling");
}

void Kirby::HittheCeilingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (HITTHEMAPTIME <= StateTime)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(KirbyState::Fall);
		return;
	}







	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();


	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::TakeOffStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	KeepDamagedState = KirbyState::Fly;
	ChangeKirbyBodyState(KirbyBodyState::Fat);
	SetAirResistance(0.4f);



	// ���� ���
	GameEngineSound::SoundPlay("Kirby_TakeOffSound.wav");

	ChangeAnimationState("TakeOff");
}

void Kirby::TakeOffUpdate(float _Delta)
{
	IsChangeState = MainRenderer->IsAnimationEnd();

	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Enter);
		return;
	}



	if (true == IsChangeState)
	{
		ChangeState(KirbyState::Fly);
		return;
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		SetGravityVector(float4::UP * FLYPOWER);
	}


	if (true == CeilingCheck())
	{
		GravityReset();
	}

	int CurFrame = static_cast<int>(MainRenderer->GetCurFrame());
	ChangeAnimationState("TakeOff", CurFrame);



	MoveHorizontal(FLYSPEED, _Delta);


	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();



	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);




	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
	}


	// ������ ���� ����
	CheckKirbyCollision();
}



// ����
void Kirby::FlyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Fly");
}

void Kirby::FlyUpdate(float _Delta)
{
	StateTime += _Delta;

	// ���� ���� Green �̰� W�� ������ ������, Enter ���� ��ȯ
	if (true == IsEnterPixel() && true == GameEngineInput::IsPress('W'))
	{
		IsNextLevelTriggerOn = true;
		ChangeState(KirbyState::ExhaleAttack);
		return;
	}


	// Z������ ���� ��
	if (true == GameEngineInput::IsDown('Z'))
	{
		ChangeState(KirbyState::ExhaleAttack);
		return;
	}


	// W�� X�� ������ ������ ����� �������鼭 �ö�
	if (true == GameEngineInput::IsPress('W') || true == GameEngineInput::IsPress('X'))
	{
		MainRenderer->FindAnimation("Normal_Left_Fly")->Inters = { 0.1f, 0.1f };
		MainRenderer->FindAnimation("Normal_Right_Fly")->Inters = { 0.1f, 0.1f };
		SetGravityVector(float4::UP * FLYPOWER);
	}


	// W�� X�� ������ ������� ����� ������
	if (false == GameEngineInput::IsPress('W') && false == GameEngineInput::IsPress('X'))
	{
		MainRenderer->FindAnimation("Normal_Left_Fly")->Inters = { 0.2f, 0.2f };
		MainRenderer->FindAnimation("Normal_Right_Fly")->Inters = { 0.2f, 0.2f };
	}

	// õ�忡 ����� ��
	if (true == CeilingCheck())
	{
		GravityReset();
	}

	// û�ϻ� ��Ʈ���� ��
	if (true == IsSolidGround() && false == (GameEngineInput::IsPress('W') || GameEngineInput::IsPress('X')))
	{
		GravityReset();
	}

	// �Ķ��� ��Ʈ���϶�
	if (true == IsPassableGround() && GetGravityVector().Y >= 0.0f && false == (GameEngineInput::IsPress('W') || GameEngineInput::IsPress('X')))
	{
		GravityReset();
	}


	// �¿� �̵�
	MoveHorizontal(FLYSPEED, _Delta);

	// �� ���
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();

	// ������ȯ�� Fly��� ����
	ChangeAnimationState("Fly");



	
	if (false == GetGroundState() || (true == GameEngineInput::IsPress('W') || true == GameEngineInput::IsPress('X')))
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);




	// X�� ���� �� ������Ʈ
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);





	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
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


// ���� ��
void Kirby::ExhaleAttackStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	KeepDamagedState = KirbyState::Idle;
	// �� �浹ü �� ũ�� ����
	ChangeKirbyBodyState(KirbyBodyState::Little);


	// ����Ʈ ����
	ExhaleEffect* ExhaleEffectPtr = GetLevel()->CreateActor<ExhaleEffect>(UpdateOrder::Ability);
	if (nullptr == ExhaleEffectPtr)
	{
		MsgBoxAssert("���Ͱ� Null �Դϴ�.");
		return;
	}

	ExhaleEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
	ExhaleEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);



	// ���� ���
	GameEngineSound::SoundPlay("Kirby_ExhaleSound.wav");


	ChangeAnimationState("ExhaleAttack");
}

void Kirby::ExhaleAttackUpdate(float _Delta)
{
	StateTime += _Delta;

	// �� ������ ������ 
	IsChangeState = MainRenderer->IsAnimationEnd();


	// Fly ���� Enter ���� ��ȯ ������ �������� ��
	if (true == IsChangeState && true == IsNextLevelTriggerOn)
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Enter);
		return;
	}


	// ü�� ������ ��� Fall
	if (true == IsChangeState && false == GetGroundState())
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Fall);
		return;
	}


	// ������ ������ ��� Idle
	if (true == IsChangeState && CurrentSpeed == 0.0f && true == GetGroundState())
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Idle);
		return;
	}


	// ���� �ִµ� �����̸� Walk
	if (true == IsChangeState && CurrentSpeed != 0.0f && true == GetGroundState())
	{
		SetAirResistance(1.0f);
		ChangeState(KirbyState::Walk);
		return;
	}



	// û�忡 ������ �߷� ����
	if (true == CeilingCheck())
	{
		GravityReset();
	}


	// �¿� ������
	MoveHorizontal(FLYSPEED, _Delta);


	// �� ���
	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();
	BlockedByAll();



	// ���� ������ �߷�����x
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}




	// ���� �� X�ӵ� ������Ʈ
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);




	// �ɷ� ����
	if (true == GameEngineInput::IsDown(VK_SHIFT) && Mode != AbilityStar::Normal && Mode != AbilityStar::Max && false == GettingAbility)
	{
		DropAbility();
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



// ������ ���
void Kirby::DamagedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	
	// ������û
	++Camera_ShakeCount;
	
	// ������ ü�°���
	if (m_KirbyHp > 0)
	{
		--m_KirbyHp; 
	}


	// �鿪 On
	ImmuneState = true;

	// Ŀ�� ���� �浹ü Off
	KirbyBodyCollisonOff();


	// �ɷ� ����
	if (Mode != AbilityStar::Normal && Mode != AbilityStar::Max)
	{
		DropAbility();
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



	// ���� ���
	GameEngineSound::SoundPlay("Kirby_Hitted.wav");



	ChangeAnimationState("Damaged");
}



void Kirby::DamagedUpdate(float _Delta)
{
	StateTime += _Delta;


	// ���� ���ӽð�
	if (MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}


	// Ŀ�� ���� �پ����� �� => ���̵�
	if (true == IsChangeState && true == GetGroundState())
	{
		ChangeState(KirbyState::Idle);
		return;
	}



	// Ŀ�� ü�� ������ �� => Fall
	if (true == IsChangeState && false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
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




void Kirby::MissStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	m_KirbyHp = 0;


	// ������û
	for (size_t i = 0; i < 2; i++)
	{
		++Camera_ShakeCount;
	}


	// Ŀ�� ���� �浹ü Off
	KirbyBodyCollisonOff();

	BodyState = KirbyBodyState::Little;
	KeepDamagedState = KirbyState::Idle;
	Dir = ActorDir::Right;

	// ���ظ� ������ �⺻ ���·�
	if (AbilityStar::Normal != Mode)
	{
		Mode = AbilityStar::Normal;
	}

	// ���� ���
	GameEngineSound::SoundPlay("Miss.wav");


	GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player,	1.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::UI, 1.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Other, 1.0f);


	if (true == VegetableValleyPlayLevel::IsBGM_On)
	{
		VegetableValleyPlayLevel::IsBGM_On = false;
		VegetableValleyPlayLevel::BGM_Player.Stop();
	}

	ChangeAnimationState("Miss");
}


void Kirby::MissUpdate(float _Delta)
{
	StateTime += _Delta;
	
	if (StateTime > KIRBY_MISS_STATETIME)
	{
		ChangeState(KirbyState::MissRaiseUp);
		return;
	}
}




void Kirby::MissRaiseUpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsKirbyRevive = false;
	IsKirby_FadeRequest = false;

	// �߷� �ʱⰪ
	SetGravityVector(float4::UP * 600.0f);


	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}


	float4 SetDir = float4::ZERO;

	float Deg = 0.0f;

	for (size_t i = 0; i < 8; i++)
	{
		SetDir = float4::GetUnitVectorFromDeg(Deg);

		KirbyDeathEffect* KirbyDeathEffectPtr = CurLevelPtr->CreateActor<KirbyDeathEffect>(UpdateOrder::UI);
		if (nullptr == KirbyDeathEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		KirbyDeathEffectPtr->init(GetPos(), SetDir);

		Deg += 45.0f;
	}


	// ���� ���
	if (false == VegetableValleyPlayLevel::IsBGM_On)
	{
		VegetableValleyPlayLevel::IsBGM_On = true;
		VegetableValleyPlayLevel::BGM_Player = GameEngineSound::SoundPlay("38_Miss.mp3");
	}


	ChangeAnimationState("MissRaiseUp");
}


void Kirby::MissRaiseUpUpdate(float _Delta)
{
	StateTime += _Delta;



	if (GetPos().Y < CurrentBackGroundScale.Y + 96.0f)
	{
		Gravity(_Delta);
		VerticalUpdate(_Delta);
	}
	else if (GetPos().Y > CurrentBackGroundScale.Y + 96.0f)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�..");
			return;
		}

		if (false == IsKirby_FadeRequest)
		{
			GlobalContents::FadeOut(CurLevelPtr);
			IsKirby_FadeRequest = true;
		}
	}

	if (StateTime > 4.0f)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�..");
			return;
		}

		VegetableValleyPlayLevel* CurrentLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
		if (nullptr == CurrentLevelPtr)
		{
			MsgBoxAssert("�ٿ� ĳ������ ���� ���߽��ϴ�.");
			return;
		}

		GameEngineCamera* MainCameraPtr = CurLevelPtr->GetMainCamera();
		if (nullptr == MainCameraPtr)
		{
			MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
			return;
		}



		VegetableValleyPlayLevel* PlayLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
		if (nullptr == PlayLevelPtr)
		{
			MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
			return;
		}

		float4 KirbyRespawnPos = PlayLevelPtr->Kirby_RespawnPos;
		MainCameraPtr->SetPos(float4::ZERO);

		// ������ ���� ����
		SetPos(KirbyRespawnPos);
		
		// �� ����
		m_KirbyHp = 6;


		// ���̵� �ƿ� Ǯ��
		FadeObject::IsFadeOutScreenRelease = true;

		// Ŀ�� �ٵ� �浹ü ON
		KirbyBodyCollisonOn();

		// UI���� ��ä���޶�� ��û
		IsKirbyRevive = true;

		// �������� �ʱ�ȭ
		SetAirResistance(1.0f);

		// BGM_Off
		VegetableValleyPlayLevel::IsBGM_On = false;

		// TimeSet
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);


		// LevelDown
		VegetableValleyPlayLevel::PrevLevelTriggerOn = true;

		

		ChangeState(KirbyState::Idle);
		return;
	}
}