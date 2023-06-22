#include "WhispyWood.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "Kirby.h"
#include <vector>

WhispyWood::WhispyWood()
{
}

WhispyWood::~WhispyWood()
{
}


void WhispyWood::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	GlobalContents::SpriteFileLoad("Left_WhispyWood.bmp", "Resources\\Unit\\Grunt", 7, 3);
	GlobalContents::SpriteFileLoad("Right_WhispyWood.bmp", "Resources\\Unit\\Grunt", 7, 3);

	MainRenderer->CreateAnimation("Left_PendulumStride", "Left_WhispyWood.bmp", 14, 19, 0.15f, true);
	MainRenderer->CreateAnimation("Right_PendulumStride", "Right_WhispyWood.bmp", 14, 19, 0.15f, true);

	MainRenderer->CreateAnimation("Left_RaiseSword", "Left_WhispyWood.bmp", 7, 7, SWORDKNIGHTRAISESWORDTIME, false);
	MainRenderer->CreateAnimation("Right_RaiseSword", "Right_WhispyWood.bmp", 7, 7, SWORDKNIGHTRAISESWORDTIME, false);

	MainRenderer->CreateAnimation("Left_Slash", "Left_WhispyWood.bmp", 7, 13, SWORDKNIGHTSLASHFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_Slash", "Right_WhispyWood.bmp", 7, 13, SWORDKNIGHTSLASHFRAMETIME, false);

	MainRenderer->CreateAnimation("Left_Underhand", "Left_WhispyWood.bmp", 0, 0, SWORDKNIGHTUNDERHANDTIME, false);
	MainRenderer->CreateAnimation("Right_Underhand", "Right_WhispyWood.bmp", 0, 0, SWORDKNIGHTUNDERHANDTIME, false);

	MainRenderer->CreateAnimation("Left_ReversingSlash", "Left_WhispyWood.bmp", 0, 6, SWORDKNIGHTSLASHFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_ReversingSlash", "Right_WhispyWood.bmp", 0, 6, SWORDKNIGHTSLASHFRAMETIME, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;




	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("�ٵ� �ݸ����� Null�ϸ��� ����..");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->On();



	AbilityCollision = CreateCollision(CollisionOrder::MonsterAbility);
	if (nullptr == AbilityCollision)
	{
		MsgBoxAssert("�ٵ� �ݸ����� Null�ϸ��� ����..");
		return;
	}

	AbilityCollision->SetCollisionScale(float4{ 141.0f, 99.0f });
	AbilityCollision->SetCollisionType(CollisionType::Rect);
	AbilityCollision->Off();
}

void WhispyWood::init(const std::string& _FileName, WhispyWoodState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Normal;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

void WhispyWood::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}

void WhispyWood::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WhispyWoodState::PendulumStride:				return PendulumStrideUpdate(_Delta);
	case WhispyWoodState::RaiseSword:					return RaiseSwordUpdate(_Delta);
	case WhispyWoodState::Slash:						return SlashUpdate(_Delta);
	case WhispyWoodState::Underhand:					return UnderhandUpdate(_Delta);
	case WhispyWoodState::ReversingSlash:				return ReversingSlashUpdate(_Delta);
	case WhispyWoodState::BeInhaled:					return BeInhaledUpdate(_Delta);
	case WhispyWoodState::Hitted:						return HittedUpdate(_Delta);
	default:
		break;
	}
}

void WhispyWood::ChangeState(WhispyWoodState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case WhispyWoodState::PendulumStride:				PendulumStrideStart();				break;
		case WhispyWoodState::RaiseSword:					RaiseSwordStart();					break;
		case WhispyWoodState::Slash:						SlashStart();						break;
		case WhispyWoodState::Underhand:					UnderhandStart();					break;
		case WhispyWoodState::ReversingSlash:				ReversingSlashStart();				break;
		case WhispyWoodState::BeInhaled:					BeInhaledStart();					break;
		case WhispyWoodState::Hitted:						HittedStart();						break;
		default:
			break;
		}
	}

	State = _State;
}

void WhispyWood::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void WhispyWood::PendulumStrideStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	GetKirbyDirection();
	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = SWORDKNIGHTSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = -SWORDKNIGHTSPEED;
	}
	ChangeAnimationState("PendulumStride");
}

void WhispyWood::PendulumStrideUpdate(float _Delta)
{
	StateTime += _Delta;


	if (StateTime > SWORDKNIGHTSLASHCOOLDOWN &&
		SWORDKNIGHTRANGEDETECTION > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		int ActionNumber = GameEngineRandom::MainRandom.RandomInt(2, 5) / 3 + 1;

		switch (ActionNumber)
		{
		case 1:
			ChangeState(WhispyWoodState::Underhand);
			break;
		case 2:
			ChangeState(WhispyWoodState::RaiseSword);
			break;
		default:
			break;
		}
		return;
	}




	EnemyCollisionCheck();

	if (true == CheckLeftWall() || true == LeftGroundIsCliff() ||
		RespawnLocation.X - SWORDKNIGHTRANGEDETECTION > GetPos().X)
	{
		CurrentSpeed = SWORDKNIGHTSPEED;
	}
	else if (true == CheckRightWall() || true == RightGroundIsCliff() ||
		RespawnLocation.X + SWORDKNIGHTRANGEDETECTION < GetPos().X)
	{
		CurrentSpeed = -SWORDKNIGHTSPEED;
	}


	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	HorizontalUpdate(_Delta);
}


void WhispyWood::RaiseSwordStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();

	float CollisionPosX = 0.0f;

	if (ActorDir::Left == Dir)
	{
		CollisionPosX = -10.5f;
	}
	else if (ActorDir::Right == Dir)
	{
		CollisionPosX = 10.5f;
	}



	if (nullptr == AbilityCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}


	AbilityCollision->SetCollisionPos(float4{ CollisionPosX , -49.5f });


	ChangeAnimationState("RaiseSword");
}

void WhispyWood::RaiseSwordUpdate(float _Delta)
{
	StateTime += _Delta;


	if (StateTime > SWORDKNIGHTRAISESWORDTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(WhispyWoodState::Slash);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
}


void WhispyWood::SlashStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -SWORDKNIGHTSLASHINSTANTANEOUSSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = SWORDKNIGHTSLASHINSTANTANEOUSSPEED;
	}

	if (nullptr == AbilityCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}

	AbilityCollision->On();
	ChangeAnimationState("Slash");
}

void WhispyWood::SlashUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		if (nullptr == AbilityCollision)
		{
			MsgBoxAssert("�浹ü�� Null �Դϴ�.");
			return;
		}

		AbilityCollision->Off();


		int SlashLink = GameEngineRandom::MainRandom.RandomInt(0, 2) / 2;
		switch (SlashLink)
		{
		case 0:
			ChangeState(WhispyWoodState::PendulumStride);
			break;
		case 1:
			ChangeState(WhispyWoodState::ReversingSlash);
			break;
		default:
			break;
		}

		return;
	}


	if (true == CheckLeftWall() || true == LeftGroundIsCliff() ||
		true == CheckRightWall() || true == RightGroundIsCliff())
	{
		CurrentSpeed = -CurrentSpeed;
	}



	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta, SWORDKNIGHTDEACELECTIONSPEED);
	HorizontalUpdate(_Delta);


	EnemyCollisionCheck();
	EnemyAbilityAttack();
}


void WhispyWood::UnderhandStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();

	float CollisionPosX = 0.0f;

	if (ActorDir::Left == Dir)
	{
		CollisionPosX = -10.5f;
	}
	else if (ActorDir::Right == Dir)
	{
		CollisionPosX = 10.5f;
	}


	if (nullptr == AbilityCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}

	AbilityCollision->SetCollisionPos(float4{ CollisionPosX , -49.5f });


	ChangeAnimationState("Underhand");
}

void WhispyWood::UnderhandUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SWORDKNIGHTUNDERHANDTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(WhispyWoodState::ReversingSlash);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
}


void WhispyWood::ReversingSlashStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -SWORDKNIGHTUNDERHANDINSTANTANEOUSSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = SWORDKNIGHTUNDERHANDINSTANTANEOUSSPEED;
	}


	if (nullptr == AbilityCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}

	AbilityCollision->On();
	ChangeAnimationState("ReversingSlash");
}

void WhispyWood::ReversingSlashUpdate(float _Delta)
{

	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		AbilityCollision->Off();
		ChangeState(WhispyWoodState::PendulumStride);
		return;
	}


	if (true == CheckLeftWall() || true == LeftGroundIsCliff() ||
		true == CheckRightWall() || true == RightGroundIsCliff())
	{
		CurrentSpeed = -CurrentSpeed;
	}



	BlockedByGround();
	BlockedByWall();


	DecelerationUpdate(_Delta, SWORDKNIGHTDEACELECTIONSPEED);
	HorizontalUpdate(_Delta);



	EnemyCollisionCheck();
	EnemyAbilityAttack();
}



void WhispyWood::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(WhispyWoodState::BeInhaled);
		return;
	}

	if (true == IsHitted)
	{
		ChangeState(WhispyWoodState::Hitted);
		return;
	}
}




void WhispyWood::Render(float _Delta)
{
	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//int CameraPos = GetLevel()->GetMainCamera()->GetPos().iX();

	//GameEngineWindowTexture* Backbuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	//HDC LineDC = Backbuffer->GetImageDC();

	//MoveToEx(LineDC, GetPos().iX() - CameraPos, 0, NULL);
	//LineTo(LineDC, GetPos().iX() - CameraPos, WinScale.iY());
}