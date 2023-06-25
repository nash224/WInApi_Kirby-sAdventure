#include "Kirby.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"
#include "DustEffect.h"
#include "HitObjectEffect.h"
#include "ExhaleEffect.h"
#include "VegetableValleyPlayLevel.h"
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






	Left_KirbyRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == Left_KirbyRenderer)
	{
		MsgBoxAssert("������ ������ ���߽��ϴ�.");
		return;
	}

	Left_KirbyRenderer->Off();

	Right_KirbyRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == Left_KirbyRenderer)
	{
		MsgBoxAssert("������ ������ ���߽��ϴ�.");
		return;
	}

	Right_KirbyRenderer->Off();





	GlobalContents::SpriteFileLoad("1Normal_KirbyOpenTheDoor.bmp", "Resources\\Unit\\Kirby", 5, 4);
	GlobalContents::SpriteFileLoad("Kirby_Performance.bmp", "Resources\\Unit\\Kirby", 8, 4);
	GlobalContents::SpriteFileLoad("Summon_KirbyEgo.bmp", "Resources\\Unit\\Kirby", 9, 1);



	MainRenderer->CreateAnimation("Normal_Right_OpenDoorAndRaiseFlag", "1Normal_KirbyOpenTheDoor.bmp", 0, 8, 0.1f, false);

	MainRenderer->CreateAnimationToFrame("Normal_Right_OpenDoorAndRaiseFlagAfter", "Normal_Right_Kirby.bmp", { 13 , 12 , 11 , 13 , 7 }, 0.1f, false);



	MainRenderer->CreateAnimation("Normal_Left_StageClearWalk", "Normal_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_StageClearWalk", "Normal_Right_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Right_StageClear", "1Normal_KirbyOpenTheDoor.bmp", 9, 15, 0.1f, false);
	Left_KirbyRenderer->CreateAnimation("StarSpin", "Summon_KirbyEgo.bmp", 0, 8, 0.075f, false);
	Right_KirbyRenderer->CreateAnimation("StarSpin", "Summon_KirbyEgo.bmp", 0, 8, 0.075f, false);

	MainRenderer->CreateAnimation("Normal_Right_Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);
	Left_KirbyRenderer->CreateAnimation("Normal_Right_Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);
	Right_KirbyRenderer->CreateAnimation("Normal_Right_Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);

	MainRenderer->FindAnimation("Normal_Right_Performance")->Inters
		= { 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 5.0f , 0.05f , 0.05f , 0.05f , 0.05f , 5.0f
		, 0.2f , 0.3f , 0.2f , 5.0f , 0.1f , 0.15f , 0.1f , 0.15f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.2f , 2.0f };
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

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



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


	MoveHorizontal(RUNSPEED, _Delta);
	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



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
	DustEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
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

	ActorUtils::DecelerationUpdate(_Delta, BRAKESPEED);
	HorizontalUpdate(_Delta);




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


	ChangeAnimationState("Jump");

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);




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

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);




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
	ChangeAnimationState("Fall");

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
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

	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::BounceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

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

	HorizontalUpdate(_Delta);

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::LandingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>();
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

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

	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);



	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::LowerPostureStart()
{
	StateTime = 0.0f;
	ChangeKirbyBodyState(KirbyBodyState::Lower);
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

	ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);




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



	// X�� ���� �� ������Ʈ 
	if (StateTime > LOWERATTACKDECELECTIONSTARTTIME)
	{
		ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	}

	HorizontalUpdate(_Delta);




	// ������ ���� ����
	CheckKirbyCollision();
}



void Kirby::HittheWallStart()
{
	StateTime = 0.0f;
	CurrentSpeed = 0.0f;
	IsChangeState = false;

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

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




	// ������ ���� ����
	CheckKirbyCollision();
}


void Kirby::HittheCeilingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();

	HitObjectEffect* HitObjectEffectPtr = GetLevel()->CreateActor<HitObjectEffect>(UpdateOrder::Ability);
	HitObjectEffectPtr->init(GetPos(), float4::ZERO);

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


void Kirby::TakeOffStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	KeepDamagedState = KirbyState::Fly;
	ChangeKirbyBodyState(KirbyBodyState::Fat);
	SetAirResistance(0.4f);
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



	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);




	DecelerationUpdate(_Delta);
	HorizontalUpdate(_Delta);

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




	// ������ ���� ����
	CheckKirbyCollision();
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




	// ������ ���� ����
	CheckKirbyCollision();
}



// ������ ���
void Kirby::DamagedStart()
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



// ���� �̵�
void Kirby::EnterStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	VegetableValleyPlayLevel::IsPlayerEnter = true;

	IsFadeOut = false;
	FadeOutTime = 0.0f;

	GameEngineTime::MainTimer.SetAllTimeScale(0.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Other, 1.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::UI, 1.0f);

	GravityReset();
	ChangeAnimationState("Enter");
}

void Kirby::EnterUpdate(float _Delta)
{
	// �� ������ ������ 
	if (true == MainRenderer->IsAnimationEnd() && false == IsFadeOut)
	{
		// FadeOut
		GlobalContents::FadeOut(GetLevel());
		IsFadeOut = true;
	}


	if (true == IsFadeOut)
	{
		FadeOutTime += _Delta;
	}

	if (FadeOutTime > FadeOutDuration)
	{
		IsChangeState = true;
	}


	// ���� �̵� Ʈ����
	if (true == IsChangeState)
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
		IsFadeOut = false;
		VegetableValleyPlayLevel::NextLevelTriggerOn = true;


		if (true == VegetableValleyPlayLevel::IsStageEnd)
		{
			ChangeState(KirbyState::OpenDoorAndRaiseFlag);
			return;
		}

		ChangeState(KirbyState::Idle);
		return;
	}


}



// ������ ��� �ȴ� ���
void Kirby::OpenDoorAndRaiseFlagStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	Dir = ActorDir::Right;

	CurState = "OpenDoorAndRaiseFlag";

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �ҷ����µ� �����߽��ϴ�.");
		return;
	}

	MainRenderer->ChangeAnimation("Normal_Right_OpenDoorAndRaiseFlag");
}


void Kirby::OpenDoorAndRaiseFlagUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}


	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}


	if (true == IsChangeState)
	{
		ChangeState(KirbyState::OpenDoorAndRaiseFlagAfter);
		return;
	}
}



// �������� Ŭ���� ��� �� ���
void Kirby::OpenDoorAndRaiseFlagAfterStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	Dir = ActorDir::Right;

	CurState = "OpenDoorAndRaiseFlagAfter";

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �ҷ����µ� �����߽��ϴ�.");
		return;
	}

	MainRenderer->ChangeAnimation("Normal_Right_OpenDoorAndRaiseFlagAfter");
}


void Kirby::OpenDoorAndRaiseFlagAfterUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}


	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}


	if (true == IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}







// �������� Ŭ���� �� �߾��̵� ���
void Kirby::StageClearWalkStart()
{
	IsChangeState = false;
	IsReachedStarStick = false;

	
	// ������ �߾� X��ǥ
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� �������ϴ�.");
		return;
	}

	VegetableValleyPlayLevel* PlayLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
	if (nullptr == PlayLevelPtr)
	{
		MsgBoxAssert("�ٿ� ĳ���� ��ȯ�� �����߽��ϴ�.");
		return;
	}

	Boss* BossPtr = PlayLevelPtr->GetLevelBossPtr();
	if (nullptr == BossPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	StageClear_X_CenterPos = BossPtr->Boss_Map_X_Center;




	// �߾� ���� �̵��� ���� Set
	float4 KirbyPos = GetPos();

	if (KirbyPos.X < StageClear_X_CenterPos)
	{
		Dir = ActorDir::Right;
		CurrentSpeed = StageClear_WalkingScalar;
	}
	else if (KirbyPos.X > StageClear_X_CenterPos)
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -StageClear_WalkingScalar;
	}



	ChangeAnimationState("StageClearWalk");
}


void Kirby::StageClearWalkUpdate(float _Delta)
{

	float4 KirbyPos = GetPos();

	if (ActorDir::Left == Dir && KirbyPos.X < StageClear_X_CenterPos)
	{
		IsChangeState = true;
	}
	else if (ActorDir::Right == Dir && KirbyPos.X > StageClear_X_CenterPos)
	{
		IsChangeState = true;
	}


	if (true == IsChangeState)
	{
		ChangeState(KirbyState::StageClear);
		return;
	}



	HorizontalUpdate(_Delta);
}




// �������� Ŭ���� ���
void Kirby::StageClearStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	Dir = ActorDir::Right;

	ChangeAnimationState("StageClear");
}


void Kirby::StageClearUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}
	

	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}


	if (true == IsChangeState)
	{
		ChangeState(KirbyState::Performance);
		return;
	}
}



// �������� Ŭ���� ��� �� ���
void Kirby::PerformanceStart()
{
	IsChangeState = false;
	CurrentSpeed = 0.0f;
	IsPerformance_17Frames_FallStartTime = false;

	GravityReset();
	ChangeAnimationState("Performance");
}


void Kirby::PerformanceUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}


	if (MainRenderer->GetCurFrame() >= 0 && MainRenderer->GetCurFrame() <= 6)
	{
		CurrentSpeed = -60.0f;
		HorizontalUpdate(_Delta);
	}

	if (7 == MainRenderer->GetCurFrame())
	{
		SetGravityVector(float4::UP * 400.0f);
		CurrentSpeed = 0.0f;
	}

	if (8 == MainRenderer->GetCurFrame())
	{
		Gravity(_Delta);
		VerticalUpdate(_Delta);

		CurrentSpeed += 300.0f * _Delta;
		HorizontalSpeedLimit(300.0f);
		HorizontalUpdate(_Delta);


		if (GetGravityVector().Y > 0.0f)
		{
			MainRenderer->FindAnimation("Normal_Right_Performance")->CurFrame = 9;
			MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter = 0.0f;
		}
	}


	if (MainRenderer->GetCurFrame() >= 9 && MainRenderer->GetCurFrame() <= 12)
	{
		Gravity(_Delta);
		VerticalUpdate(_Delta);

		CurrentSpeed += 300.0f * _Delta;
		HorizontalSpeedLimit(200.0f);
		HorizontalUpdate(_Delta);
	}


	if (13 == MainRenderer->GetCurFrame())
	{
		if (false == GetGroundState())
		{
			Gravity(_Delta);
			VerticalUpdate(_Delta);

			CurrentSpeed += 300.0f * _Delta;
			HorizontalSpeedLimit(300.0f);
			HorizontalUpdate(_Delta);
		}
		else if (true == GetGroundState())
		{
			ActorUtils::DecelerationUpdate(_Delta, 300.0f);
			HorizontalUpdate(_Delta);

			if (0.0f == CurrentSpeed)
			{
				MainRenderer->FindAnimation("Normal_Right_Performance")->CurFrame = 14;
				MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter = 0.0f;
			}

		}
	}

	if (14 == MainRenderer->GetCurFrame())
	{
		CurrentSpeed = 100.0f;
		CurentVerticalSpeed = -100.0f;
	}

	if (15 == MainRenderer->GetCurFrame())
	{
		VerticalDecelerationUpdate(100.0f * 0.3f, _Delta);
		VerticalUpdateBasedlevitation(_Delta);

		ActorUtils::DecelerationUpdate(_Delta, 100.0f * 0.3f);
		HorizontalUpdate(_Delta);
	}

	if (16 == MainRenderer->GetCurFrame())
	{
		CurrentSpeed = -100.0f;
		CurentVerticalSpeed = -100.0f;
	}


	if (17 == MainRenderer->GetCurFrame())
	{
		if (false == IsPerformance_17Frames_FallStartTime)
		{
			VerticalDecelerationUpdate(100.0f * 0.3f, _Delta);
			VerticalUpdateBasedlevitation(_Delta);

			ActorUtils::DecelerationUpdate(_Delta, 100.0f * 0.3f);
			HorizontalUpdate(_Delta);
		}
		else if (true == IsPerformance_17Frames_FallStartTime)
		{
			Gravity(_Delta);
			VerticalUpdate(_Delta);

			if (true == GetGroundState())
			{
				MainRenderer->FindAnimation("Normal_Right_Performance")->CurFrame = 18;
				MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter = 0.0f;
			}
		}

		if (false == IsPerformance_17Frames_FallStartTime && MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter > 0.3f)
		{
			IsPerformance_17Frames_FallStartTime = true;
			GravityReset();
		}
	}

	if (18 == MainRenderer->GetCurFrame() || 20 == MainRenderer->GetCurFrame())
	{
		CurrentSpeed = 100.0f;
	}

	if (19 == MainRenderer->GetCurFrame() || 21 == MainRenderer->GetCurFrame())
	{
		ActorUtils::DecelerationUpdate(_Delta, 100.0f * 0.15f);
		HorizontalUpdate(_Delta);
	}


	if (MainRenderer->GetCurFrame() >= 0 && MainRenderer->GetCurFrame() <= 7)
	{

	}



	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}

	if (true== IsChangeState)
	{
		ChangeState(KirbyState::Idle);
		return;
	}


}