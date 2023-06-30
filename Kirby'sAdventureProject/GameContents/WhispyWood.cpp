#include "WhispyWood.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"
#include "Apple.h"
#include "StarStick.h"
#include "Boss_WhispyEffect.h"
#include "BossUI.h"
#include "BackGround.h"




WhispyWood::WhispyWood()
{
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

	MainRenderer->CreateAnimationToFrame("Left_Whispy", "WhispyWood_3x4_144x264.bmp", { 3, 5, 4, 5, 3, 0 }, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Frown", "WhispyWood_3x4_144x264.bmp", 6, 7, 0.15f, false);
	MainRenderer->FindAnimation("Left_Frown")->Inters = { 0.15f, 1.05f};

	MainRenderer->CreateAnimation("Left_Kaonashi", "WhispyWood_3x4_144x264.bmp", 10, 10, 0.15f, false);
	
	MainRenderer->CreateAnimation("Left_CryingFace", "WhispyWood_3x4_144x264.bmp", 9, 9, 0.15f, false);


	// 기본설정
	Scale = WHISPYWOOD_SCALE;

	Dir = ActorDir::Left;

	Boss_Map_X_Center = 264.0f;


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


	// 사운드
	GlobalContents::SoundFileLoad("Boss_HittedSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Boss_0Hp.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Boss_StealtheStarStick.wav", "Resources\\SoundResources\\EffectVoice");
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void WhispyWood::Update(float _Delta)
{
	DebugShortcut();


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

	MainBossPtr = this;

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
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 1.0f);

		ChangeState(WhispyWoodState::SummonApple);
		return;
	}


	float4 KirbyPos = KirbyPtr->GetPos();


	if (false == BossUIPtr->IsBossStaminaFull && KirbyPos.Y > BossFindPlayer_Y_Distance)
	{
		GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0.0f);
		IsBossFindKirby = true;


		// 사운드
		VegetableValleyPlayLevel::BGM_Player = GameEngineSound::SoundPlay("07_Boss.mp3");
		VegetableValleyPlayLevel::IsBGM_On = true;
	}
}


void WhispyWood::SummonAppleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	SummonAppleCount = 0;
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

		++TwinkleCount;
	}

	// 사과 첫번째 젠
	if (0 == TwinkleCount  && false == IsCharge_SummonAppleCount)
	{
		SummonAppleCount = 4;

		IsCharge_SummonAppleCount = true;
	}


	// 사과 잔탄이 있으면
	if (0 != SummonAppleCount)
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
			WhispyApple_list.push_back(ApplePtr);


			--SummonAppleCount;

		}
	}

	if (false == IsReCharge_SummonAppleCount && true == IsCharge_SummonAppleCount && TwinkleCount >= 2)
	{
		SummonAppleCount = 4;
		IsReCharge_SummonAppleCount = true;
	}




	if (3 == TwinkleCount)
	{
		TwinkleCount = 0;
		IsCharge_SummonAppleCount = false;
		IsReCharge_SummonAppleCount = false;

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


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오는데 실패했습니다.");
		return;
	}


	// Whispy 장전
	if (-1 == Whispy_RemainCount)
	{
		int SetWhispyCount = GameEngineRandom::MainRandom.RandomInt(0, 3) / 3;

		switch (SetWhispyCount)
		{
		case 0:
			MainRenderer->FindAnimation("Left_Whispy")->Inters = { 0.1f, 0.1f, 1.6f, 0.1f, 0.1f, 0.3f };
			Whispy_RemainCount = 2;
			break;
		case 1:
			MainRenderer->FindAnimation("Left_Whispy")->Inters = { 0.1f, 0.1f, 2.4f, 0.1f, 0.1f, 0.3f };
			Whispy_RemainCount = 4;
			break;
		default:
			break;
		}
	}
	else
	{
		float WhispyThirdFrametime = static_cast<float>(Whispy_RemainCount + 2) * Whispy_FireCycle;
		MainRenderer->FindAnimation("Left_Whispy")->Inters = { 0.1f, 0.1f, WhispyThirdFrametime, 0.1f, 0.1f, 0.3f };
		MainRenderer->FindAnimation("Left_Whispy")->CurFrame = 2;
	}

	ChangeAnimationState("Whispy");
}

void WhispyWood::WhispyUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오는데 실패했습니다.");
		return;
	}
	

	// 특정 시간마다 바람공격
	if (2 == MainRenderer->FindAnimation("Left_Whispy")->CurFrame && Whispy_RemainCount > 0)
	{
		Whispy_ReChargeTime += _Delta;

		if (Whispy_ReChargeTime > Whispy_FireCycle)
		{
			Whispy_ReChargeTime = 0.0f;

			GameEngineLevel* CurLevelPtr = GetLevel();
			if (nullptr == CurLevelPtr)
			{
				MsgBoxAssert("레벨을 불러오지 못했습니다.");
				return;
			}

			Boss_WhispyEffect* Boss_WhispyEffectPtr = CurLevelPtr->CreateActor<Boss_WhispyEffect>(UpdateOrder::Ability);
			if (nullptr == Boss_WhispyEffectPtr)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			Boss_WhispyEffectPtr->init(GetPos(), WHISPYWOOD_SCALE);
			Boss_WhispyEffectPtr->SetActorCollision(CollisionOrder::MonsterAbility, CollisionType::Rect);
			WhispyEffect_list.push_back(Boss_WhispyEffectPtr);

			--Whispy_RemainCount;
		}
	}



	if (true == MainRenderer->IsAnimationEnd())
	{
		Whispy_RemainCount = -1;
		PrevState = WhispyWoodState::Max;

		ChangeState(WhispyWoodState::SummonApple);
		return;
	}


	EnemyCollisionCheck();
}


void WhispyWood::FrownStart()
{
	IsImmune = true;


	VegetableValleyPlayLevel::RequestShakeCountToLevel(2);


	// 사운드
	GameEngineSound::SoundPlay("Boss_HittedSound.wav");

	ChangeAnimationState("Frown");
}

void WhispyWood::FrownUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오는데 실패했습니다.");
		return;
	}


	// 지진효과



	if (true == MainRenderer->IsAnimationEnd())
	{
		IsImmune = false;
		BodyCollision->On();

		if (WhispyWoodState::Whispy == PrevState)
		{
			ChangeState(WhispyWoodState::Whispy);
		}
		else
		{
			ChangeState(WhispyWoodState::SummonApple);
		}

		return;
	}
}


void WhispyWood::KaonashiStart()
{
	// 배경 바꿔달라고 요청
	BossBackGroundPtr->IsBossChangeMap = true;
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Ability, 0.0f);


	VegetableValleyPlayLevel::RequestShakeCountToLevel(4);
	VegetableValleyPlayLevel::RequestShakeMagnitudeToLevel(6.0f);


	// 사운드
	GameEngineSound::SoundPlay("Boss_0Hp.wav");

	if (true == VegetableValleyPlayLevel::IsBGM_On)
	{
		VegetableValleyPlayLevel::BGM_Player.Stop();
		VegetableValleyPlayLevel::IsBGM_On = false;
	}


	ChangeAnimationState("Kaonashi");
}

void WhispyWood::KaonashiUpdate(float _Delta)
{
	// BackGround 에서 값 변경
	if (true == BossChangeMapPattern)
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
		ChangeState(WhispyWoodState::CryingFace);
		return;
	}

}


void WhispyWood::CryingFaceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	// 사과 없앰
	std::list<Apple*>::iterator StarIter = WhispyApple_list.begin();
	std::list<Apple*>::iterator EndIter = WhispyApple_list.end();

	for (; StarIter != EndIter; ++StarIter)
	{
		Apple* ApplePtr = *StarIter;

		if (nullptr == ApplePtr)
		{
			MsgBoxAssert("이 사과는 이미 처리된 객체입니다.");
			return;
		}

		ApplePtr->Death();
		ApplePtr->EnemyPointerRelease();
	}


	// 휫바람 없앰
	std::list<Boss_WhispyEffect*>::iterator WhispyStarIter = WhispyEffect_list.begin();
	std::list<Boss_WhispyEffect*>::iterator WhispyEndIter = WhispyEffect_list.end();

	for (; WhispyStarIter != WhispyEndIter; ++WhispyStarIter)
	{
		Boss_WhispyEffect* WhispyEffectPtr = *WhispyStarIter;

		if (nullptr == WhispyEffectPtr)
		{
			MsgBoxAssert("이 사과는 이미 처리된 객체입니다.");
			return;
		}

		WhispyEffectPtr->Death();
		WhispyEffectPtr->EffectPointerRelease();
	}


	// 스타 스틱 생성
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}


	StarStick* StarStickPtr = CurLevelPtr->CreateActor<StarStick>(UpdateOrder::Item);
	if (nullptr == StarStickPtr)
	{
		MsgBoxAssert("스타 스틱을 불러오지 못했습니다.");
		return;
	}

	float4 CurrentPos = GetPos();

	StarStickPtr->init(CurrentPos, StickTargetPos);




	// 사운드
	GameEngineSound::SoundPlay("Boss_StealtheStarStick.wav");



	ChangeAnimationState("CryingFace");
}

void WhispyWood::CryingFaceUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > Boss_StealtheStarStick_Duration && false == IsBoss_StealtheStarStickDone)
	{
		IsBoss_StealtheStarStickDone = true;

		VegetableValleyPlayLevel::BGM_Player = GameEngineSound::SoundPlay("30_Level_Clear.mp3");
	}
}



void WhispyWood::EnemyCollisionCheck()
{
	if (true == IsHitted && false == IsImmune)
	{
		if (nullptr == BodyCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return;
		}

		BodyCollision->Off();


		IsHitted = false;
		

		if (m_BossHp > 0)
		{
			ChangeState(WhispyWoodState::Frown);
			return;
		}
		else if (m_BossHp <= 0)
		{
			m_BossHp = 0;

			ChangeState(WhispyWoodState::Kaonashi);
			return;
		}
	}
}



void WhispyWood::LevelStart()
{

	// 레벨 참조
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


	BossBackGroundPtr = PlayLevelPtr->GetLevelBackGroundPtr();
	if (nullptr == BossBackGroundPtr)
	{
		MsgBoxAssert("백그라운드를 읽어오지 못했습니다.");
		return;
	}


	// UI 참조
	UIManager* UIPtr =  PlayLevelPtr->GetUIManager();
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


	CurLevel_BitMap_FileName = PlayLevelPtr->GetLevelBitMapFileName();


}

void WhispyWood::LevelEnd()
{
	Death();

	if (nullptr != MainRenderer)
	{
		MainRenderer = nullptr;
	}

	if (nullptr != BodyCollision)
	{
		BodyCollision = nullptr;
	}
}


void WhispyWood::Render(float _Delta)
{
}


void WhispyWood::DebugShortcut()
{
	if (true == GameEngineInput::IsDown('B'))
	{
		m_BossHp = 1;
	}
}