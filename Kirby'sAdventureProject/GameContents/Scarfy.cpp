#include "Scarfy.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "PlayUI.h"
#include "AirExplosionEffect.h"
#include "Kirby.h"



Scarfy::Scarfy()
{
}

Scarfy::~Scarfy()
{
}


void Scarfy::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	GlobalContents::SpriteFileLoad("Left_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);
	GlobalContents::SpriteFileLoad("Right_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);

	MainRenderer->CreateAnimation("Left_Idle", "Left_AerialEnemy.bmp", 0, 1, 0.2f, true);
	MainRenderer->CreateAnimation("Right_Idle", "Right_AerialEnemy.bmp", 0, 1, 0.2f, true);

	MainRenderer->CreateAnimation("Left_TransFormingBefore", "Left_AerialEnemy.bmp", 0, 1, SCARFYWOBBLETIME, true);
	MainRenderer->CreateAnimation("Right_TransFormingBefore", "Right_AerialEnemy.bmp", 0, 1, SCARFYWOBBLETIME, true);

	MainRenderer->CreateAnimationToFrame("Left_TransFormingAfter", "Left_AerialEnemy.bmp", { 2 , 4 } , SCARFYWOBBLETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_TransFormingAfter", "Right_AerialEnemy.bmp", { 2 , 4 } , SCARFYWOBBLETIME, true);

	MainRenderer->CreateAnimation("Left_Following", "Left_AerialEnemy.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Following", "Right_AerialEnemy.bmp", 2, 5, 0.1f, true);

	MainRenderer->CreateAnimation("Left_Bomb", "Left_AerialEnemy.bmp", 2, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Bomb", "Right_AerialEnemy.bmp", 2, 5, 0.1f, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Scarfy::init(const std::string& _FileName, ScarfyState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Max;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */



void Scarfy::Update(float _Delta)
{
	StateUpdate(_Delta);
}



void Scarfy::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ScarfyState::Idle:					return IdleUpdate(_Delta);
	case ScarfyState::TransFormingBefore:	return TransFormingBeforeUpdate(_Delta);
	case ScarfyState::TransFormingAfter:	return TransFormingAfterUpdate(_Delta);
	case ScarfyState::Following:			return FollowingUpdate(_Delta);
	case ScarfyState::Bomb:					return BombUpdate(_Delta);
	case ScarfyState::Hitted:				return HittedUpdate(_Delta);
	default:
		break;
	}
}



void Scarfy::ChangeState(ScarfyState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case ScarfyState::Idle:					IdleStart();					break;
		case ScarfyState::TransFormingBefore:	TransFormingBeforeStart();		break;
		case ScarfyState::TransFormingAfter:	TransFormingAfterStart();		break;
		case ScarfyState::Following:			FollowingStart();				break;
		case ScarfyState::Bomb:					BombStart();					break;
		case ScarfyState::Hitted:				HittedStart();					break;
		default:	
			break;
		}
	}

	State = _State;
}



void Scarfy::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void Scarfy::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsGravityReverse = false;
	ChangeGravityDistance = RespawnLocation.Y + SCARFYFLIGHTCHANGRAVITYCONVERSIONPOINT;
	GravityReset();

	ChangeAnimationState("Idle");
}

void Scarfy::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	// Ŀ�������� ���⼳��
	GetKirbyDirection();


	// �ְ� �� ���� ���̷� ���� �߷¹���
	if (GetPos().Y > ChangeGravityDistance && false == IsGravityReverse)
	{
		IsGravityReverse = true;
	}
	else if (GetPos().Y < ChangeGravityDistance && true == IsGravityReverse)
	{
		IsGravityReverse = false;
	}


	// ���� ���� ����ȯ
	if (true == IsInhaledStateOn)
	{
		ChangeState(ScarfyState::TransFormingBefore);
		return;
	}


	// ���� ��ȯ�� ���� �ִϸ��̼� ����
	ChangeAnimationState("Idle");



	// �浹 �˻�
	EnemyCollisionCheck();


	// �߷� �� Y�� ������Ʈ
	if (true == IsGravityReverse)
	{
		ReverseGravity(_Delta);
	}
	else if (false == IsGravityReverse)
	{
		Gravity(_Delta);
	}

	VerticalUpdate(_Delta);
}


void Scarfy::TransFormingBeforeStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	GravityReset();
	ChangeAnimationState("TransFormingBefore");
}

void Scarfy::TransFormingBeforeUpdate(float _Delta)
{
	StateTime += _Delta;

	// Scarfy �յڷ� ����
	if (StateTime > SCARFYWOBBLETIME)
	{
		StateTime = 0.0f;
		++WobbleCount;
		if (1 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::RIGHT * 12.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::LEFT * 12.0f);
			}
		}
		else if (0 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::LEFT * 6.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::RIGHT * 6.0f);
			}
		}
	}



	// �� ��������
	if (6 == WobbleCount)
	{
		IsChangeState = true;
	}

	// 2�� ����ȯ
	if (true == IsChangeState)
	{
		ChangeState(ScarfyState::TransFormingAfter);
		return;
	}



	// �浹�˻�
	EnemyCollisionCheck();
}


void Scarfy::TransFormingAfterStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	GravityReset();
	ChangeAnimationState("TransFormingAfter");
}

void Scarfy::TransFormingAfterUpdate(float _Delta)
{
	StateTime += _Delta;


	// 10ȸ ����
	if (StateTime > SCARFYWOBBLETIME)
	{
		StateTime = 0.0f;
		++WobbleCount;
		if (1 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::RIGHT * 12.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::LEFT * 12.0f);
			}
		}
		else if (0 == WobbleCount % 2)
		{
			if (ActorDir::Left == Dir)
			{
				AddPos(float4::LEFT * 6.0f);
			}
			else if (ActorDir::Right == Dir)
			{
				AddPos(float4::RIGHT * 6.0f);
			}
		} 
	}



	// �� �������� 
	if (10 == WobbleCount)
	{
		IsChangeState = true;
	}


	// �m�ư�
	if (true == IsChangeState)
	{
		ChangeState(ScarfyState::Following);
		return;
	}


	// �浹�˻�
	EnemyCollisionCheck();
}


void Scarfy::FollowingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("Following");
}

void Scarfy::FollowingUpdate(float _Delta)
{
	StateTime += _Delta;

	// ���� ���� ������ ���ų� �ð��� ������
	if (SCARFYRECOGNITIONRANGE > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X) || StateTime > SCARFYFOLLOWINGTIME)
	{
		IsChangeState = true;
	}


	// ���� ���� ��ȯ
	if (true == IsChangeState)
	{
		ChangeState(ScarfyState::Bomb);
		return;
	}


	// �浹 �˻�
	EnemyCollisionCheck();


	// Ŀ�� ���� ���ư�
	float4 KirbyUnitVector = GetKirbyUnitVector();
	KirbyUnitVector *= SCARFYFOLLOWINGSPEED;

	AddPos(KirbyUnitVector * _Delta);
}


void Scarfy::BombStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BombCount = 0;
	IsInhaledStateOn = false;
	ChangeAnimationState("Bomb");
}

void Scarfy::BombUpdate(float _Delta)
{
	StateTime += _Delta;


	// ����
	if (StateTime >= SCARFYVIBRATIONTIME)
	{
		StateTime = 0.0f;

		++BombCount;
		if (1 == BombCount % 2)
		{
			AddPos(float4::UP * SCARFYVIBRATIONDISTANCE);
		}
		else if (0 == BombCount % 2)
		{
			AddPos(float4::DOWN * SCARFYVIBRATIONDISTANCE);
		}
	}


	// �ð��Ǹ� ����
	if (30 == BombCount)
	{
		AirExplosionEffect* AirExplosionEffectPtr = GetLevel()->CreateActor<AirExplosionEffect>(UpdateOrder::Ability);
		if (nullptr == AirExplosionEffectPtr)
		{
			MsgBoxAssert("���Ͱ� Null �ϸ��� ����..");
			return;
		}

		AirExplosionEffectPtr->init(GetPos(), Scale);
		AirExplosionEffectPtr->SetActorCollision(CollisionOrder::MonsterAbility, CollisionType::Rect);

		Off();
		return;
	}
}





void Scarfy::EnemyCollisionCheck()
{
	if (true == IsHitted)
	{
		ChangeState(ScarfyState::Hitted);
		return;
	}
}





void Scarfy::HittedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsHitted = true;

	// ������ Bomb
	AirExplosionEffect* AirExplosionEffectPtr = GetLevel()->CreateActor<AirExplosionEffect>(UpdateOrder::Ability);
	if (nullptr == AirExplosionEffectPtr)
	{
		MsgBoxAssert("���Ͱ� Null �ϸ��� ����..");
		return;
	}

	AirExplosionEffectPtr->init(GetPos(), Scale);
	AirExplosionEffectPtr->SetActorCollision(CollisionOrder::MonsterAbility, CollisionType::Rect);


	PlayUI::PlayUI_Score += 500;
}


void Scarfy::HittedUpdate(float _Delta)
{
	IsHitted = false;
	Off();
}



void Scarfy::Render(float _Delta)
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


	EnemyDebugRender(dc, TextRenderNum, TextXPos, TextYPos);
}

