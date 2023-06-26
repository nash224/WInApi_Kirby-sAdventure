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
#include "VegetableValleyPlayLevel.h"
#include "Boss.h"




void Kirby::MoveLevel_StateResourceLoad()
{


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}


	Left_KirbyRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == Left_KirbyRenderer)
	{
		MsgBoxAssert("렌더러 생성에 필했습니다.");
		return;
	}

	Left_KirbyRenderer->Off();

	Right_KirbyRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == Left_KirbyRenderer)
	{
		MsgBoxAssert("렌더러 생성에 필했습니다.");
		return;
	}

	Right_KirbyRenderer->Off();



	GlobalContents::SpriteFileLoad("1Normal_KirbyOpenTheDoor.bmp", "Resources\\Unit\\Kirby", 5, 4);
	GlobalContents::SpriteFileLoad("Kirby_Performance.bmp", "Resources\\Unit\\Kirby", 8, 4);
	GlobalContents::SpriteFileLoad("Summon_KirbyEgo.bmp", "Resources\\Unit\\Kirby", 9, 1);



	MainRenderer->CreateAnimationToFrame("Normal_Right_OpenDoorAndRaiseFlag", "1Normal_KirbyOpenTheDoor.bmp", { 19 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 }, 0.1f, false);
	MainRenderer->FindAnimation("Normal_Right_OpenDoorAndRaiseFlag")->Inters = { 2.0f , 0.1f, 0.3f, 0.1f, 5.0f , 5.0f , 0.04f , 0.04f , 0.04f , 0.04f };

	MainRenderer->CreateAnimationToFrame("Normal_Right_OpenDoorAndRaiseFlagAfter", "Normal_Right_Kirby.bmp", { 13 , 12 , 11 , 13 , 7 }, 0.1f, false);



	MainRenderer->CreateAnimation("Normal_Left_StageClearWalk", "Normal_Left_Kirby.bmp", 2, 5, 0.2f, true);
	MainRenderer->CreateAnimation("Normal_Right_StageClearWalk", "Normal_Right_Kirby.bmp", 2, 5, 0.2f, true);

	MainRenderer->CreateAnimation("Normal_Right_StageClear", "1Normal_KirbyOpenTheDoor.bmp", 9, 15, 0.1f, false);
	MainRenderer->FindAnimation("Normal_Right_StageClear")->Inters = { 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 1.0f };
	Left_KirbyRenderer->CreateAnimation("StarSpin", "Summon_KirbyEgo.bmp", 0, 8, 0.075f, false);
	Right_KirbyRenderer->CreateAnimation("StarSpin", "Summon_KirbyEgo.bmp", 0, 8, 0.075f, false);

	MainRenderer->CreateAnimation("Normal_Right_Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);
	Left_KirbyRenderer->CreateAnimation("Normal_Right_Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);
	Right_KirbyRenderer->CreateAnimation("Normal_Right_Performance", "Kirby_Performance.bmp", 0, 29, 5.0f, false);

	MainRenderer->FindAnimation("Normal_Right_Performance")->Inters
		= { 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 0.2f , 5.0f , 0.05f , 0.05f , 0.05f , 0.05f , 5.0f
		, 0.2f , 0.3f , 0.2f , 5.0f , 0.1f , 0.15f , 0.1f , 0.15f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.1f , 0.2f , 1.0f };

}







// 레벨 이동
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
	// 한 동작이 끝나면 
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


	// 레벨 이동 트리거
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



// 문열고 깃발 꽂는 모션
void Kirby::OpenDoorAndRaiseFlagStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsKirbyOpenDoor = false;

	Dir = ActorDir::Right;

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오는데 실패했습니다.");
		return;
	}

	MainRenderer->ChangeAnimation("Normal_Right_OpenDoorAndRaiseFlag");
}


void Kirby::OpenDoorAndRaiseFlagUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 Null 입니다.");
		return;
	}


	if (1 == MainRenderer->GetCurFrame())
	{
		if (false == IsKirbyOpenDoor)
		{
			IsKirbyOpenDoor = true;
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
}



// 스테이지 클리어 모션 후 모션
void Kirby::OpenDoorAndRaiseFlagAfterStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	Dir = ActorDir::Right;


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오는데 실패했습니다.");
		return;
	}

	MainRenderer->ChangeAnimation("Normal_Right_OpenDoorAndRaiseFlagAfter");
}


void Kirby::OpenDoorAndRaiseFlagAfterUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 Null 입니다.");
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







// 스테이지 클리어 후 중앙이동 모션
void Kirby::StageClearWalkStart()
{
	IsChangeState = false;
	IsReachedStarStick = false;


	// 보스맵 중앙 X좌표
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("보스를 불러오지 못헀습니다.");
		return;
	}

	VegetableValleyPlayLevel* PlayLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
	if (nullptr == PlayLevelPtr)
	{
		MsgBoxAssert("다운 캐스팅 변환에 실패했습니다.");
		return;
	}

	Boss* BossPtr = PlayLevelPtr->GetLevelBossPtr();
	if (nullptr == BossPtr)
	{
		MsgBoxAssert("보스를 불러오지 못했습니다.");
		return;
	}

	StageClear_X_CenterPos = BossPtr->Boss_Map_X_Center;




	// 중앙 기준 이동할 방향 Set
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




// 스테이지 클리어 모션
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
		MsgBoxAssert("랜더러가 Null 입니다.");
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



// 스테이지 클리어 모션 후 모션
void Kirby::PerformanceStart()
{
	IsChangeState = false;
	CurrentSpeed = 0.0f;
	IsPerformance_17Frames_FallStartTime = false;
	IsKirby_FinishPosCheck = false;

	Kirby_Performance_StartXPos = GetPos().X;

	GravityReset();
	ChangeAnimationState("Performance");
}


void Kirby::PerformanceUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 Null 입니다.");
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
			HorizontalSpeedLimit(150.0f);
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
		CurrentSpeed = 400.0f;
		CurentVerticalSpeed = -60.0f;
	}

	if (15 == MainRenderer->GetCurFrame())
	{
		VerticalDecelerationUpdate(60.0f / 0.3f, _Delta);
		VerticalUpdateBasedlevitation(_Delta);

		ActorUtils::DecelerationUpdate(_Delta, 400.0f / 0.3f);
		HorizontalUpdate(_Delta);
	}

	if (16 == MainRenderer->GetCurFrame())
	{
		CurrentSpeed = -400.0f;
		CurentVerticalSpeed = -60.0f;
	}


	if (17 == MainRenderer->GetCurFrame())
	{
		if (false == IsPerformance_17Frames_FallStartTime)
		{
			VerticalDecelerationUpdate(60.0f / 0.3f, _Delta);
			VerticalUpdateBasedlevitation(_Delta);

			ActorUtils::DecelerationUpdate(_Delta, 400.0f / 0.3f);
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

		if (false == IsPerformance_17Frames_FallStartTime && 0.0f == CurrentSpeed)
		{
			MainRenderer->FindAnimation("Normal_Right_Performance")->CurInter;
			IsPerformance_17Frames_FallStartTime = true;
			SetGravityVector(float4::DOWN * 200.0f);
		}
	}

	if (18 == MainRenderer->GetCurFrame() || 20 == MainRenderer->GetCurFrame())
	{
		CurrentSpeed = 200.0f;
	}

	if (19 == MainRenderer->GetCurFrame() || 21 == MainRenderer->GetCurFrame())
	{
		ActorUtils::DecelerationUpdate(_Delta, 200.0f * 0.15f);
		HorizontalUpdate(_Delta);
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
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}

		GlobalContents::FadeOut(CurLevelPtr);
		IsChangeState = true;
	}


	if (true == IsChangeState)
	{
		IsFadeOut = false;
		VegetableValleyPlayLevel::NextLevelTriggerOn = true;
		ChangeState(KirbyState::Idle);
		return;
	}

}