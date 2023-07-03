#include "StarStick.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"
#include "MoveStarEffect.h"



StarStick::StarStick()
{
}

StarStick::~StarStick()
{
}



void StarStick::Start()
{
	// 렌더러 생성
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	HaloEffectRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == HaloEffectRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}


	// 파일로드
	GlobalContents::SpriteFileLoad("StarStick_4x4_72x72.bmp", "Resources\\Unit\\Object", 4, 4);

	// 애니메이션 설정
	MainRenderer->CreateAnimation("StarStick", "StarStick_4x4_72x72.bmp", 0, 11, 0.08f, true);
	HaloEffectRenderer->CreateAnimation("StarStickHalEffect", "StarStick_4x4_72x72.bmp", 12, 13, 0.08f, true);

	MainRenderer->ChangeAnimation("StarStick");
	HaloEffectRenderer->ChangeAnimation("StarStickHalEffect");


	// 기타설정
	Scale = float4{ 48.0f, 48.0f };
	ItemNumber = 1;

	// 초기 상태
	ChangeState(StarStickState::BounceOff);


	// 충돌체 설정
	BodyCollision = CreateCollision(CollisionOrder::Object);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Collision 이 Null 일리가 없어..");
		return;
	}


	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void StarStick::init(const float4& _StartPos, const float4& _TargetPos)
{
	SetPos(_StartPos);

	TargetPos = _TargetPos;


	float4 StickPos = _StartPos;
	TargetMovePos = TargetPos - StickPos;

	Target_UnitVector = TargetMovePos.NormalizeReturn();
	Target_Distance = TargetMovePos.Size();
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void StarStick::Update(float _Delta)
{
	StateUpdate(_Delta);
}


void StarStick::StateUpdate(float _Delta)
{
	switch (State)
	{
	case StarStickState::BounceOff:					return BounceOffUpdate(_Delta);
	case StarStickState::Floating:					return FloatingUpdate(_Delta);
	default:
		break;
	}
}

void StarStick::ChangeState(StarStickState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case StarStickState::BounceOff:				BounceOffStart();				break;
		case StarStickState::Floating:				FloatingStart();				break;
		default:
			break;
		}
	}

	State = _State;
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void StarStick::BounceOffStart()
{

}

void StarStick::BounceOffUpdate(float _Delta)
{
	Target_TotalDecelection_UnitVector += Target_UnitVector * Target_Distance * 0.5f * _Delta;
	float4 MovePos = TargetMovePos - Target_TotalDecelection_UnitVector;

	if (Target_UnitVector.X > 0.0f)
	{
		if (MovePos.X < 0.0f)
		{
			ChangeState(StarStickState::Floating);
			return;
		}
	}
	else if (Target_UnitVector.X < 0.0f)
	{
		if (MovePos.X > 0.0f)
		{
			ChangeState(StarStickState::Floating);
			return;
		}
	}


	AddPos(MovePos * _Delta);


	// 충돌
	ItemCollisionCheck();
	ItemReachedState();
}


void StarStick::FloatingStart()
{
	IsChangeReverseDir = false;
	ChangePosTime = 0.0f;
	Center_Origin_YPos = GetPos().Y;
}

void StarStick::FloatingUpdate(float _Delta)
{
	ChangePosTime += _Delta;

	// 매 특정시간마다
	if (ChangePosTime > ChangePosCycle)
	{
		ChangePosTime = 0.0f;

		// 방향이 바꾸지 않으면
		if (false == IsChangeReverseDir)
		{
			// 특정 픽셀만큼 밑으로
			float4 MovePos = float4::DOWN * OneTime_Move_HeightDistance;

			AddPos(MovePos);

			// 지정 범위를 벗어나면 방향바뀜
			if (GetPos().Y >= Center_Origin_YPos + LimitHeight_ToCenter)
			{
				IsChangeReverseDir = true;
			}
		}
		// 이하동문
		else if (true == IsChangeReverseDir)
		{
			float4 MovePos = float4::UP * OneTime_Move_HeightDistance;

			AddPos(MovePos);

			if (GetPos().Y <= Center_Origin_YPos - LimitHeight_ToCenter)
			{
				IsChangeReverseDir = false;
			}
		}
	}


	// 충돌
	ItemCollisionCheck();
	ItemReachedState();
}




void StarStick::ItemReachedState()
{
	if (true == IsReached)
	{
		
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}


		float CreateDirDeg = 0.0f;

		for (size_t i = 0; i < 4; i++)
		{
			MoveStarEffect* MoveStarEffectPtr = CurLevelPtr->CreateActor<MoveStarEffect>(UpdateOrder::Ability);
			if (nullptr == MoveStarEffectPtr)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			CreateDirDeg = 180.0f;

			switch (i)
			{
			case 0:
				CreateDirDeg += 0.0f;
				break;
			case 1:
				CreateDirDeg += 30.0f;
				break;
			case 2:
				CreateDirDeg += 150.0f;
				break;
			case 3:
				CreateDirDeg += 180.0f;
				break;
			default:
				break;
			}

			float4 StarEffectDir = float4::GetUnitVectorFromDeg(CreateDirDeg);

			MoveStarEffectPtr->init(GetPos(), StarEffectDir);
			MoveStarEffectPtr->SetSpeedAndDuration(200.0f, 1.5f);
		}




		Death();
		ItemPointerRelease();
		if (nullptr != HaloEffectRenderer)
		{
			HaloEffectRenderer = nullptr;
		}

		return;
	}
}



void StarStick::Render(float _Delta)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	int TextRenderNum = 0;


	float4 ActorScenePos = ActorCameraPos();

	int TextXPos = ActorScenePos.iX() - Scale.Half().iX();
	int TextYPos = ActorScenePos.iY() - (Scale * 2.0f).iY();


	ThisDebugRender(dc, TextRenderNum, TextXPos, TextYPos);

}


void StarStick::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	{
		std::string Text = "";
		Text += "!!Clear!!";

		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


}