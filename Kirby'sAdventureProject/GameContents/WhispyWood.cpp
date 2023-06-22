#include "WhispyWood.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "Kirby.h"
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
		MsgBoxAssert("������ ������ �����߽��ϴ�.");
		return;
	}

	// �ε�
	GlobalContents::SpriteFileLoad("WhispyWood_3x4_144x264.bmp", "Resources\\Unit\\Boss", 3, 4);

	// �ִϸ��̼� ����
	MainRenderer->CreateAnimation("Left_Idle", "WhispyWood_3x4_144x264.bmp", 0, 0, 0.15f, false);

	MainRenderer->CreateAnimationToFrame("Left_SummonApple", "WhispyWood_3x4_144x264.bmp", { 0, 1, 2, 1, 0 }, 0.1f, true);
	MainRenderer->FindAnimation("Left_SummonApple")->Inters = { 0.1f, 0.1f, 0.2f, 0.1f, 5.0f, };

	MainRenderer->CreateAnimationToFrame("Left_Whispy", "WhispyWood_3x4_144x264.bmp", { 3, 5, 4, 5, 3 }, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Frown", "WhispyWood_3x4_144x264.bmp", 6, 7, 0.15f, false);

	MainRenderer->CreateAnimation("Left_Kaonashi", "WhispyWood_3x4_144x264.bmp", 10, 10, 0.15f, false);
	
	MainRenderer->CreateAnimation("Left_CryingFace", "WhispyWood_3x4_144x264.bmp", 9, 9, 0.15f, false);


	// �⺻����
	Scale = WHISPYWOOD_SCALE;

	Dir = ActorDir::Left;


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
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

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


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


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

}


void WhispyWood::WhispyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	ChangeAnimationState("Whispy");
}

void WhispyWood::WhispyUpdate(float _Delta)
{

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
	if (true == IsHitted)
	{
		ChangeState(WhispyWoodState::Frown);
		return;
	}
}



void WhispyWood::LevelStart()
{
	UIManager* UIPtr = UIManager::UI;
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
}


void WhispyWood::Render(float _Delta)
{
}