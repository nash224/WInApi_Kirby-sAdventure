#include "Kirby.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>


#include "GlobalContents.h"
#include "FadeObject.h"
#include "VegetableValley13.h"
#include "Boss.h"




void Kirby::MoveLevel_StateResourceLoad()
{


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}


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



	MainRenderer->CreateAnimationToFrame("Normal_Right_OpenDoorAndRaiseFlag", "1Normal_KirbyOpenTheDoor.bmp", { 19 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 }, 0.1f, false);
	MainRenderer->FindAnimation("Normal_Right_OpenDoorAndRaiseFlag")->Inters = { 1.0f , 0.2f, 0.3f, 0.1f, 0.5f , 5.0f , 0.15f , 0.15f , 0.15f , 0.15f };

	MainRenderer->CreateAnimationToFrame("Normal_Right_OpenDoorAndRaiseFlagAfter", "Normal_Right_Kirby.bmp", { 13 , 12 , 11 , 13 , 7 }, 0.1f, false);



	MainRenderer->CreateAnimation("Normal_Left_StageClearWalk", "Normal_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_StageClearWalk", "Normal_Right_Kirby.bmp", 2, 5, 0.2f, true);


	MainRenderer->CreateAnimation("Normal_Right_StageClear", "1Normal_KirbyOpenTheDoor.bmp", 9, 15, 0.1f, false);
	MainRenderer->FindAnimation("Normal_Right_StageClear")->Inters = { 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 1.0f };

	Left_KirbyRenderer->CreateAnimation("Ready", "Summon_KirbyEgo.bmp", 0, 0, 0.075f, false);
	Right_KirbyRenderer->CreateAnimation("Ready", "Summon_KirbyEgo.bmp", 0, 0, 0.075f, false);
	Left_KirbyRenderer->CreateAnimation("StarSpin", "Summon_KirbyEgo.bmp", 0, 8, 0.075f, false);
	Right_KirbyRenderer->CreateAnimation("StarSpin", "Summon_KirbyEgo.bmp", 0, 8, 0.075f, false);


	MainRenderer->CreateAnimation("Normal_Right_Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);
	Left_KirbyRenderer->CreateAnimation("Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);
	Right_KirbyRenderer->CreateAnimation("Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);


	MainRenderer->FindAnimation("Normal_Right_Performance")->Inters
		= { Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration 
		, Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration 
		, 5.0f , 0.05f , 0.05f , 0.05f , 0.05f , 5.0f
		, 0.2f , 0.3f , 0.2f , 5.0f , 0.1f , 0.2f , 0.1f , 0.2f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.3f , 1.0f };


	Left_KirbyRenderer->FindAnimation("Performance")->Inters
		= { Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration
		, Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration
		, 5.0f , 0.05f , 0.05f , 0.05f , 0.05f , 5.0f
		, 0.2f , 0.3f , 0.2f , 5.0f , 0.1f , 0.2f , 0.1f , 0.2f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.3f , 1.0f };


	Right_KirbyRenderer->FindAnimation("Performance")->Inters
		= { Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration
		, Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration , Performance_0_7_Duration
		, 5.0f , 0.05f , 0.05f , 0.05f , 0.05f , 5.0f
		, 0.2f , 0.3f , 0.2f , 5.0f , 0.1f , 0.2f , 0.1f , 0.2f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.3f , 1.0f };


	Left_KirbyRenderer->ChangeAnimation("Ready");
	Right_KirbyRenderer->ChangeAnimation("Ready");
	Left_KirbyRenderer->Off();
	Right_KirbyRenderer->Off();
	Left_KirbyRenderer->SetRenderPos(float4{ -StageClear_KirbyBackUpDancer_RenderInter , 0.0f });
	Right_KirbyRenderer->SetRenderPos(float4{ StageClear_KirbyBackUpDancer_RenderInter , 0.0f });


	// ����
	GlobalContents::SoundFileLoad("08_Level_Cleared_Dance.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("EnterSound.wav", "Resources\\SoundResources\\EffectVoice");


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

	GameEngineSound::SoundPlay("EnterSound.wav");

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

	if (true == FadeObject::IsFadeDone)
	{
		IsChangeState = true;
	}


	// ���� �̵� Ʈ����
	if (true == IsChangeState)
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
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
	IsKirbyOpenDoorToLevel = false;
	IsKirbyOpenedDoor = false;
	IsKirbyClosedDoor = false;
	IsCheckRaiseUpWithFlag = false;

	Dir = ActorDir::Right;

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


	if (1 == MainRenderer->GetCurFrame())
	{
		if (false == IsKirbyOpenedDoor)
		{
			IsKirbyOpenDoorToLevel = true;
			IsKirbyOpenedDoor = true;
		}
	}

	if (3 == MainRenderer->GetCurFrame())
	{
		if (false == IsKirbyClosedDoor)
		{
			IsKirbyCloseDoorToLevel = true;
			IsKirbyClosedDoor = true;
			CurrentSpeed = 20.0f * 10.0f;
		}

		HorizontalUpdate(_Delta);
	}


	if (4 == MainRenderer->GetCurFrame())
	{
		if (false == IsCheckRaiseUpWithFlag)
		{
			IsCheckRaiseUpWithFlag = true;
			CurrentSpeed = 0.0f;
			SetGravityVector(float4::UP * 400.0f);
		}

		Gravity(_Delta);
		VerticalUpdate(_Delta);
	}


	if (5 == MainRenderer->GetCurFrame())
	{
		Gravity(_Delta);
		VerticalUpdate(_Delta);

		if (true == GetGroundState())
		{
			MainRenderer->FindAnimation("Normal_Right_OpenDoorAndRaiseFlag")->CurFrame = 6;
			MainRenderer->FindAnimation("Normal_Right_OpenDoorAndRaiseFlag")->CurInter = 0.0f;
		}
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


	BlockedByGround();
}



// �������� Ŭ���� ��� �� ���
void Kirby::OpenDoorAndRaiseFlagAfterStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	Dir = ActorDir::Right;

	CurrentSpeed = -150.0f;
	SetGravityVector(float4::UP * 300.0f);

	VegetableValleyPlayLevel::ChangeClearDoor = true;

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

	Gravity(_Delta);
	VerticalUpdate(_Delta);

	HorizontalUpdate(_Delta);
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

	if (true == VegetableValleyPlayLevel::IsBGM_On)
	{
		VegetableValleyPlayLevel::IsBGM_On = false;

		VegetableValleyPlayLevel::BGM_Player.Stop();
	}
	

	if (nullptr == Left_KirbyRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.")
	}

	if (nullptr == Right_KirbyRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.")
	}


	Left_KirbyRenderer->On();
	Right_KirbyRenderer->On();
	Left_KirbyRenderer->ChangeAnimation("StarSpin");
	Right_KirbyRenderer->ChangeAnimation("StarSpin");
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
	IsKirby_FinishPosCheck = false;

	Kirby_Performance_StartXPos = GetPos().X;

	VegetableValleyPlayLevel::BGM_Player = GameEngineSound::SoundPlay("08_Level_Cleared_Dance.mp3");


	GravityReset();

	Left_KirbyRenderer->ChangeAnimation("Performance");
	Right_KirbyRenderer->ChangeAnimation("Performance");
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

		CurrentSpeed += 200.0f * _Delta;
		HorizontalSpeedLimit(200.0f);
		HorizontalUpdate(_Delta);


		if (GetGravityVector().Y > 0.0f)
		{
			if (nullptr == Left_KirbyRenderer)
			{
				MsgBoxAssert("�������� Null �Դϴ�.");
				return;
			}

			if (nullptr == Right_KirbyRenderer)
			{
				MsgBoxAssert("�������� Null �Դϴ�.");
				return;
			}


			MainRenderer->FindAnimation("Normal_Right_Performance")->CurFrame = 9;
			MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter = 0.0f;

			Left_KirbyRenderer->FindAnimation("Performance")->CurFrame = 9;
			Left_KirbyRenderer->FindAnimation("Performance")->CurInter = 0.0f;

			Right_KirbyRenderer->FindAnimation("Performance")->CurFrame = 9;
			Right_KirbyRenderer->FindAnimation("Performance")->CurInter = 0.0f;
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
			HorizontalSpeedLimit(150.0f);
			HorizontalUpdate(_Delta);
		}
		else if (true == GetGroundState())
		{
			ActorUtils::DecelerationUpdate(_Delta, 300.0f);
			HorizontalUpdate(_Delta);

			if (0.0f == CurrentSpeed)
			{
				if (nullptr == Left_KirbyRenderer)
				{
					MsgBoxAssert("�������� Null �Դϴ�.");
					return;
				}

				if (nullptr == Right_KirbyRenderer)
				{
					MsgBoxAssert("�������� Null �Դϴ�.");
					return;
				}


				MainRenderer->FindAnimation("Normal_Right_Performance")->CurFrame = 14;
				MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter = 0.0f;


				Left_KirbyRenderer->FindAnimation("Performance")->CurFrame = 14;
				Left_KirbyRenderer->FindAnimation("Performance")->CurInter = 0.0f;

				Right_KirbyRenderer->FindAnimation("Performance")->CurFrame = 14;
				Right_KirbyRenderer->FindAnimation("Performance")->CurInter = 0.0f;
			}

		}
	}

	if (14 == MainRenderer->GetCurFrame())
	{
		CurentVerticalSpeed = -60.0f;
		CurrentSpeed = Performance_15_17_MovePos;
	}

	if (15 == MainRenderer->GetCurFrame())
	{
		VerticalDecelerationUpdate(60.0f / 0.3f, _Delta);
		VerticalUpdateBasedlevitation(_Delta);

		ActorUtils::DecelerationUpdate(_Delta, Performance_15_17_MovePos / 0.3f);
		ActorUtils::HorizontalUpdate(_Delta);
	}

	if (16 == MainRenderer->GetCurFrame())
	{
		CurentVerticalSpeed = -60.0f;
		CurrentSpeed = -Performance_15_17_MovePos;
	}


	if (17 == MainRenderer->GetCurFrame())
	{
		if (false == IsPerformance_17Frames_FallStartTime)
		{
			VerticalDecelerationUpdate(60.0f / 0.3f, _Delta);
			VerticalUpdateBasedlevitation(_Delta);

			ActorUtils::DecelerationUpdate(_Delta, Performance_15_17_MovePos / 0.3f);
			ActorUtils::HorizontalUpdate(_Delta);
		}
		else if (true == IsPerformance_17Frames_FallStartTime)
		{
			Gravity(_Delta);
			VerticalUpdate(_Delta);

			if (true == GetGroundState())
			{
				if (nullptr == Left_KirbyRenderer)
				{
					MsgBoxAssert("�������� Null �Դϴ�.");
					return;
				}

				if (nullptr == Right_KirbyRenderer)
				{
					MsgBoxAssert("�������� Null �Դϴ�.");
					return;
				}


				MainRenderer->FindAnimation("Normal_Right_Performance")->CurFrame = 18;
				MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter = 0.0f;


				Left_KirbyRenderer->FindAnimation("Performance")->CurFrame = 18;
				Left_KirbyRenderer->FindAnimation("Performance")->CurInter = 0.0f;


				Right_KirbyRenderer->FindAnimation("Performance")->CurFrame = 18;
				Right_KirbyRenderer->FindAnimation("Performance")->CurInter = 0.0f;
			}
		}

		if (false == IsPerformance_17Frames_FallStartTime && 0.0f == CurrentSpeed)
		{
			MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter;
			IsPerformance_17Frames_FallStartTime = true;
			SetGravityVector(float4::DOWN * 200.0f);
		}
	}

	if (18 == MainRenderer->GetCurFrame() || 20 == MainRenderer->GetCurFrame())
	{
		CurrentSpeed = 300.0f;
	}

	if (19 == MainRenderer->GetCurFrame() || 21 == MainRenderer->GetCurFrame())
	{
		ActorUtils::DecelerationUpdate(_Delta, 300.0f / 0.2f);
		ActorUtils::HorizontalUpdate(_Delta);
	}


	if (MainRenderer->GetCurFrame() >= 22 && MainRenderer->GetCurFrame() <= 27)
	{
		if (false == IsKirby_FinishPosCheck)
		{
			IsKirby_FinishPosCheck = true;
			Kirby_SetFinishPos = GetPos().X - Kirby_Performance_StartXPos;
		}

		CurrentSpeed = -Kirby_SetFinishPos / 0.6f;
		HorizontalUpdate(_Delta);
	}



	if (true == MainRenderer->IsAnimationEnd())
	{
		//IsChangeState = true;
		VegetableValley13::IsEndingCreditOn = true;
	}


	if (true == IsChangeState)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		GlobalContents::FadeOut(CurLevelPtr);

		FadeObject::IsFadeOutScreenRelease = true;
		VegetableValleyPlayLevel::NextLevelTriggerOn = true;
		ChangeState(KirbyState::Idle);
		return;
	}
}