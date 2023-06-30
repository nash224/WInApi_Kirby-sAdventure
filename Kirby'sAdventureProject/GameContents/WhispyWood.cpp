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
		MsgBoxAssert("������ ������ �����߽��ϴ�.");
		return;
	}

	// �ε�
	GlobalContents::SpriteFileLoad("WhispyWood_3x4_144x264.bmp", "Resources\\Unit\\Boss", 3, 4);

	// �ִϸ��̼� ����
	MainRenderer->CreateAnimation("Left_Idle", "WhispyWood_3x4_144x264.bmp", 0, 0, 0.15f, false);

	MainRenderer->CreateAnimationToFrame("Left_SummonApple", "WhispyWood_3x4_144x264.bmp", { 0, 1, 2, 1, 0 }, 0.1f, true);
	MainRenderer->FindAnimation("Left_SummonApple")->Inters = { 0.1f, 0.1f, 0.2f, 0.1f, 5.0f, };

	MainRenderer->CreateAnimationToFrame("Left_Whispy", "WhispyWood_3x4_144x264.bmp", { 3, 5, 4, 5, 3, 0 }, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Frown", "WhispyWood_3x4_144x264.bmp", 6, 7, 0.15f, false);
	MainRenderer->FindAnimation("Left_Frown")->Inters = { 0.15f, 1.05f};

	MainRenderer->CreateAnimation("Left_Kaonashi", "WhispyWood_3x4_144x264.bmp", 10, 10, 0.15f, false);
	
	MainRenderer->CreateAnimation("Left_CryingFace", "WhispyWood_3x4_144x264.bmp", 9, 9, 0.15f, false);


	// �⺻����
	Scale = WHISPYWOOD_SCALE;

	Dir = ActorDir::Left;

	Boss_Map_X_Center = 264.0f;


	SetPos(WHISPYWOOD_RESPAWNLOCATION - float4{ 0.0f, Scale.Half().Y});
	ChangeState(WhispyWoodState::Idle);

	Attribute = AttributeType::None;




	// �浹ü ����
	BodyCollision = CreateCollision(CollisionOrder::BossBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("�ٵ� �ݸ����� Null�ϸ��� ����..");
		return;
	}

	BodyCollision->SetCollisionPos(float4::ZERO);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->Off();


	// ����
	GlobalContents::SoundFileLoad("Boss_HittedSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Boss_0Hp.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Boss_StealtheStarStick.wav", "Resources\\SoundResources\\EffectVoice");
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

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


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


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
		MsgBoxAssert("Ŀ�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	if (nullptr == BossUIPtr)
	{
		MsgBoxAssert("UI�� �ҷ����� ���߽��ϴ�.");
		return;
	}


	if (true == BossUIPtr->Boss_Stamina_Full_Done)
	{
		if (nullptr == BodyCollision)
		{
			MsgBoxAssert("�浹ü�� Null �Դϴ�.");
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


		// ����
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
		MsgBoxAssert("�������� �ҷ����µ� �����߽��ϴ�.");
		return;
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		// ���� ��������
		float NextCloseEyesTurn = GameEngineRandom::MainRandom.RandomFloat(0.0f, 3.0f) + 2.0f;
		MainRenderer->FindAnimation("Left_SummonApple")->Inters = { 0.1f, 0.1f, 0.2f, 0.1f, NextCloseEyesTurn };

		++TwinkleCount;
	}

	// ��� ù��° ��
	if (0 == TwinkleCount  && false == IsCharge_SummonAppleCount)
	{
		SummonAppleCount = 4;

		IsCharge_SummonAppleCount = true;
	}


	// ��� ��ź�� ������
	if (0 != SummonAppleCount)
	{
		// �����ȯ ����
		SummonAppleTime += _Delta;

		if (SummonAppleTime > SummonAppleDuration)
		{
			SummonAppleTime = 0.0f;

			// ��� ��ȯ ���� ��ġ
			float Summon_WidthDistance = GameEngineRandom::MainRandom.RandomFloat(SummonApple_Min_Width, SummonApple_Max_Width);

			GameEngineLevel* CurLevelPtr = GetLevel();
			if (nullptr == CurLevelPtr)
			{
				MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
				return;
			}

			Apple* ApplePtr = CurLevelPtr->CreateActor<Apple>(UpdateOrder::Monster);
			if (nullptr == ApplePtr)
			{
				MsgBoxAssert("���� ������ �����߽��ϴ�.");
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
		MsgBoxAssert("�������� �ҷ����µ� �����߽��ϴ�.");
		return;
	}


	// Whispy ����
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
		MsgBoxAssert("�������� �ҷ����µ� �����߽��ϴ�.");
		return;
	}
	

	// Ư�� �ð����� �ٶ�����
	if (2 == MainRenderer->FindAnimation("Left_Whispy")->CurFrame && Whispy_RemainCount > 0)
	{
		Whispy_ReChargeTime += _Delta;

		if (Whispy_ReChargeTime > Whispy_FireCycle)
		{
			Whispy_ReChargeTime = 0.0f;

			GameEngineLevel* CurLevelPtr = GetLevel();
			if (nullptr == CurLevelPtr)
			{
				MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
				return;
			}

			Boss_WhispyEffect* Boss_WhispyEffectPtr = CurLevelPtr->CreateActor<Boss_WhispyEffect>(UpdateOrder::Ability);
			if (nullptr == Boss_WhispyEffectPtr)
			{
				MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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


	// ����
	GameEngineSound::SoundPlay("Boss_HittedSound.wav");

	ChangeAnimationState("Frown");
}

void WhispyWood::FrownUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �ҷ����µ� �����߽��ϴ�.");
		return;
	}


	// ����ȿ��



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
	// ��� �ٲ�޶�� ��û
	BossBackGroundPtr->IsBossChangeMap = true;
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0.0f);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Ability, 0.0f);


	VegetableValleyPlayLevel::RequestShakeCountToLevel(4);
	VegetableValleyPlayLevel::RequestShakeMagnitudeToLevel(6.0f);


	// ����
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
	// BackGround ���� �� ����
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

	// ��� ����
	std::list<Apple*>::iterator StarIter = WhispyApple_list.begin();
	std::list<Apple*>::iterator EndIter = WhispyApple_list.end();

	for (; StarIter != EndIter; ++StarIter)
	{
		Apple* ApplePtr = *StarIter;

		if (nullptr == ApplePtr)
		{
			MsgBoxAssert("�� ����� �̹� ó���� ��ü�Դϴ�.");
			return;
		}

		ApplePtr->Death();
		ApplePtr->EnemyPointerRelease();
	}


	// �ܹٶ� ����
	std::list<Boss_WhispyEffect*>::iterator WhispyStarIter = WhispyEffect_list.begin();
	std::list<Boss_WhispyEffect*>::iterator WhispyEndIter = WhispyEffect_list.end();

	for (; WhispyStarIter != WhispyEndIter; ++WhispyStarIter)
	{
		Boss_WhispyEffect* WhispyEffectPtr = *WhispyStarIter;

		if (nullptr == WhispyEffectPtr)
		{
			MsgBoxAssert("�� ����� �̹� ó���� ��ü�Դϴ�.");
			return;
		}

		WhispyEffectPtr->Death();
		WhispyEffectPtr->EffectPointerRelease();
	}


	// ��Ÿ ��ƽ ����
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}


	StarStick* StarStickPtr = CurLevelPtr->CreateActor<StarStick>(UpdateOrder::Item);
	if (nullptr == StarStickPtr)
	{
		MsgBoxAssert("��Ÿ ��ƽ�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 CurrentPos = GetPos();

	StarStickPtr->init(CurrentPos, StickTargetPos);




	// ����
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
			MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
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

	// ���� ����
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	VegetableValleyPlayLevel* PlayLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
	if (nullptr == PlayLevelPtr)
	{
		MsgBoxAssert("�ٿ�ĳ������ �����߽��ϴ�.");
		return;
	}


	BossBackGroundPtr = PlayLevelPtr->GetLevelBackGroundPtr();
	if (nullptr == BossBackGroundPtr)
	{
		MsgBoxAssert("��׶��带 �о���� ���߽��ϴ�.");
		return;
	}


	// UI ����
	UIManager* UIPtr =  PlayLevelPtr->GetUIManager();
	if (nullptr == UIPtr)
	{
		MsgBoxAssert("UI�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	BossUIPtr = dynamic_cast<BossUI*>(UIPtr);
	if (nullptr == BossUIPtr)
	{
		MsgBoxAssert("�ٿ� ĳ������ �����߽��ϴ�.");
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