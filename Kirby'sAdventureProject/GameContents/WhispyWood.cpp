#include "WhispyWood.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"
#include "Apple.h"
#include "BossUI.h"




WhispyWood* WhispyWood::WhispyWoodPtr = nullptr;
WhispyWood::WhispyWood()
{
	WhispyWoodPtr = this;
}

WhispyWood::~WhispyWood()
{
}


void WhispyWood::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러 생성에 실패했습니다.");
		return;
	}

	// 로드
	GlobalContents::SpriteFileLoad("WhispyWood_3x4_144x264.bmp", "Resources\\Unit\\Boss", 3, 4);

	// 애니메이션 생성
	MainRenderer->CreateAnimation("Left_Idle", "WhispyWood_3x4_144x264.bmp", 0, 0, 0.15f, false);

	MainRenderer->CreateAnimationToFrame("Left_SummonApple", "WhispyWood_3x4_144x264.bmp", { 0, 1, 2, 1, 0 }, 0.1f, true);
	MainRenderer->FindAnimation("Left_SummonApple")->Inters = { 0.1f, 0.1f, 0.2f, 0.1f, 5.0f, };

	MainRenderer->CreateAnimationToFrame("Left_Whispy", "WhispyWood_3x4_144x264.bmp", { 3, 5, 4, 5, 3 }, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Frown", "WhispyWood_3x4_144x264.bmp", 6, 7, 0.15f, false);

	MainRenderer->CreateAnimation("Left_Kaonashi", "WhispyWood_3x4_144x264.bmp", 10, 10, 0.15f, false);
	
	MainRenderer->CreateAnimation("Left_CryingFace", "WhispyWood_3x4_144x264.bmp", 9, 9, 0.15f, false);


	// 기본설정
	Scale = WHISPYWOOD_SCALE;

	Dir = ActorDir::Left;


	SetPos(WHISPYWOOD_RESPAWNLOCATION - float4{ 0.0f, Scale.Half().Y});
	ChangeState(WhispyWoodState::Idle);

	Attribute = AttributeType::None;




	// 충돌체 세팅
	BodyCollision = CreateCollision(CollisionOrder::BossBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("바디 콜리전이 Null일리가 없어..");
		return;
	}

	BodyCollision->SetCollisionPos(float4::ZERO);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->Off();
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void WhispyWood::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void WhispyWood::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WhispyWoodState::Idle:							return IdleUpdate(_Delta);
	case WhispyWoodState::SummonApple:					return SummonAppleUpdate(_Delta);
	case WhispyWoodState::Whispy:						return WhispyUpdate(_Delta);
	case WhispyWoodState::Frown:						return FrownUpdate(_Delta);
	case WhispyWoodState::Kaonashi:						return KaonashiUpdate(_Delta);
	case WhispyWoodState::CryingFace:					return CryingFaceUpdate(_Delta);
	default:
		break;
	}
}

void WhispyWood::ChangeState(WhispyWoodState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case WhispyWoodState::Idle:						IdleStart();						break;
		case WhispyWoodState::SummonApple:				SummonAppleStart();					break;
		case WhispyWoodState::Whispy:					WhispyStart();						break;
		case WhispyWoodState::Frown:					FrownStart();						break;
		case WhispyWoodState::Kaonashi:					KaonashiStart();					break;
		case WhispyWoodState::CryingFace:				CryingFaceStart();					break;
		default:
			break;
		}
	}

	State = _State;
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void WhispyWood::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsBossFindKirby = false;

	ChangeAnimationState("Idle");
}

void WhispyWood::IdleUpdate(float _Delta)
{
	StateTime += _Delta;
	
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return;
	}

	if (nullptr == BossUIPtr)
	{
		MsgBoxAssert("UI를 불러오지 못했습니다.");
		return;
	}


	if (true == BossUIPtr->Boss_Stamina_Full_Done)
	{
		if (nullptr == BodyCollision)
		{
			MsgBoxAssert("충돌체가 Null 입니다.");
			return;
		}

		BodyCollision->On();

		ChangeState(WhispyWoodState::SummonApple);
		return;
	}


	float4 KirbyPos = KirbyPtr->GetPos();


	if (false == BossUIPtr->IsBossStaminaFull && KirbyPos.Y > BossFindPlayer_Y_Distance)
	{
		IsBossFindKirby = true;
	}
}


void WhispyWood::SummonAppleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	ChangeAnimationState("SummonApple");
}

void WhispyWood::SummonAppleUpdate(float _Delta)
{
	StateTime += _Delta;


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오는데 실패했습니다.");
		return;
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		// 랜덤 눈깜빡임
		float NextCloseEyesTurn = GameEngineRandom::MainRandom.RandomFloat(0.0f, 3.0f) + 2.0f;
		MainRenderer->FindAnimation("Left_SummonApple")->Inters = { 0.1f, 0.1f, 0.2f, 0.1f, NextCloseEyesTurn };

		++TwinkleCount_ToSummonApple;
	}

	if (1 == TwinkleCount_ToSummonApple || 3 == TwinkleCount_ToSummonApple)
	{
		// 사과소환 로직
		SummonAppleTime += _Delta;

		if (SummonAppleTime > SummonAppleDuration)
		{
			SummonAppleTime = 0.0f;

			// 사과 소환 가로 위치
			float Summon_WidthDistance = GameEngineRandom::MainRandom.RandomFloat(SummonApple_Min_Width, SummonApple_Max_Width);

			GameEngineLevel* CurLevelPtr = GetLevel();
			if (nullptr == CurLevelPtr)
			{
				MsgBoxAssert("레벨을 불러오지 못했습니다.");
				return;
			}

			Apple* ApplePtr = CurLevelPtr->CreateActor<Apple>(UpdateOrder::Monster);
			if (nullptr == ApplePtr)
			{
				MsgBoxAssert("액터 생성에 실패했습니다.");
				return;
			}

			// Apple->SetPos
			ApplePtr->init(float4{ Summon_WidthDistance , SummonApple_Height });
			ApplePtr->SetGroundTexture(CurLevel_BitMap_FileName);
		}
	}

	if (7 == TwinkleCount_ToSummonApple)
	{
		TwinkleCount_ToSummonApple = 0;
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(WhispyWoodState::Whispy);
		return;
	}


	EnemyCollisionCheck();
}


void WhispyWood::WhispyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	PrevState = WhispyWoodState::Whispy;

	ChangeAnimationState("Whispy");
}

void WhispyWood::WhispyUpdate(float _Delta)
{



	PrevState = WhispyWoodState::Max;

}


void WhispyWood::FrownStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Frown");
}

void WhispyWood::FrownUpdate(float _Delta)
{
	StateTime += _Delta;


	EnemyCollisionCheck();
}


void WhispyWood::KaonashiStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	ChangeAnimationState("Kaonashi");
}

void WhispyWood::KaonashiUpdate(float _Delta)
{

}


void WhispyWood::CryingFaceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	ChangeAnimationState("CryingFace");
}

void WhispyWood::CryingFaceUpdate(float _Delta)
{

}



void WhispyWood::EnemyCollisionCheck()
{
	if (true == IsHitted && WhispyWoodState::Whispy == PrevState)
	{
		ChangeState(WhispyWoodState::SummonApple);
		return;
	}

	if (true == IsHitted)
	{
		ChangeState(WhispyWoodState::SummonApple);
		return;
	}
}



void WhispyWood::LevelStart()
{
	UIManager* UIPtr = UIManager::UI;
	if (nullptr == UIPtr)
	{
		MsgBoxAssert("UI를 불러오지 못했습니다.");
		return;
	}

	BossUIPtr = dynamic_cast<BossUI*>(UIPtr);
	if (nullptr == BossUIPtr)
	{
		MsgBoxAssert("다운 캐스팅을 실패했습니다.");
		return;
	}

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	VegetableValleyPlayLevel* PlayLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
	if (nullptr == PlayLevelPtr)
	{
		MsgBoxAssert("다운캐스팅을 실패했습니다.");
		return;
	}

	CurLevel_BitMap_FileName = PlayLevelPtr->GetLevelBitMapFileName();


}


void WhispyWood::Render(float _Delta)
{
}