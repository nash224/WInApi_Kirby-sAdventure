#include "SwordKnight.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "Kirby.h"
#include <vector>

SwordKnight::SwordKnight()
{
}

SwordKnight::~SwordKnight()
{
}


void SwordKnight::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	GlobalContents::SpriteFileLoad("Left_SwordKnight.bmp", "Resources\\Unit\\Grunt", 7, 3);
	GlobalContents::SpriteFileLoad("Right_SwordKnight.bmp", "Resources\\Unit\\Grunt", 7, 3);
	 
	MainRenderer->CreateAnimation("Left_PendulumStride", "Left_SwordKnight.bmp", 14, 19, 0.15f, true);
	MainRenderer->CreateAnimation("Right_PendulumStride", "Right_SwordKnight.bmp", 14, 19, 0.15f, true);

	MainRenderer->CreateAnimation("Left_RaiseSword", "Left_SwordKnight.bmp", 7, 7, SWORDKNIGHTRAISESWORDTIME, false);
	MainRenderer->CreateAnimation("Right_RaiseSword", "Right_SwordKnight.bmp", 7, 7, SWORDKNIGHTRAISESWORDTIME, false);

	MainRenderer->CreateAnimation("Left_Slash", "Left_SwordKnight.bmp", 7, 13, SWORDKNIGHTSLASHFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_Slash", "Right_SwordKnight.bmp", 7, 13, SWORDKNIGHTSLASHFRAMETIME, false);

	MainRenderer->CreateAnimation("Left_Underhand", "Left_SwordKnight.bmp", 0, 0, SWORDKNIGHTUNDERHANDTIME, false);
	MainRenderer->CreateAnimation("Right_Underhand", "Right_SwordKnight.bmp", 0, 0, SWORDKNIGHTUNDERHANDTIME, false);

	MainRenderer->CreateAnimation("Left_ReversingSlash", "Left_SwordKnight.bmp", 0, 6, SWORDKNIGHTSLASHFRAMETIME, false);
	MainRenderer->CreateAnimation("Right_ReversingSlash", "Right_SwordKnight.bmp", 0, 6, SWORDKNIGHTSLASHFRAMETIME, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;




	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("바디 콜리전이 Null일리가 없어..");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->On();



	AbilityCollision = CreateCollision(CollisionOrder::MonsterAbility);
	if (nullptr == AbilityCollision)
	{
		MsgBoxAssert("바디 콜리전이 Null일리가 없어..");
		return;
	}

	AbilityCollision->SetCollisionScale(float4{ 141.0f, 99.0f });
	AbilityCollision->SetCollisionType(CollisionType::Rect);
	AbilityCollision->Off();


	// 사운드 로드
	GlobalContents::SoundFileLoad("SwordKnight_AttackSound.wav", "Resources\\SoundResources\\EffectVoice");
}

void SwordKnight::init(const std::string& _FileName, SwordKnightState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Sword;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void SwordKnight::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}

void SwordKnight::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SwordKnightState::PendulumStride:				return PendulumStrideUpdate(_Delta);
	case SwordKnightState::RaiseSword:					return RaiseSwordUpdate(_Delta);
	case SwordKnightState::Slash:						return SlashUpdate(_Delta);
	case SwordKnightState::Underhand:					return UnderhandUpdate(_Delta);
	case SwordKnightState::ReversingSlash:				return ReversingSlashUpdate(_Delta);
	case SwordKnightState::BeInhaled:					return BeInhaledUpdate(_Delta);
	case SwordKnightState::Hitted:						return HittedUpdate(_Delta);
	default:
		break;
	}
}

void SwordKnight::ChangeState(SwordKnightState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case SwordKnightState::PendulumStride:				PendulumStrideStart();				break;
		case SwordKnightState::RaiseSword:					RaiseSwordStart();					break;
		case SwordKnightState::Slash:						SlashStart();						break;
		case SwordKnightState::Underhand:					UnderhandStart();					break;
		case SwordKnightState::ReversingSlash:				ReversingSlashStart();				break;
		case SwordKnightState::BeInhaled:					BeInhaledStart();					break;
		case SwordKnightState::Hitted:						HittedStart();						break;
		default:
			break;
		}
	}

	State = _State;
}

void SwordKnight::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void SwordKnight::PendulumStrideStart()
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

void SwordKnight::PendulumStrideUpdate(float _Delta)
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
			ChangeState(SwordKnightState::Underhand);
			break;
		case 2:
			ChangeState(SwordKnightState::RaiseSword);
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


void SwordKnight::RaiseSwordStart()
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
		MsgBoxAssert("충돌체가 Null 입니다.");
		return;
	}


	AbilityCollision->SetCollisionPos(float4{ CollisionPosX , -49.5f });
	

	ChangeAnimationState("RaiseSword");
}

void SwordKnight::RaiseSwordUpdate(float _Delta)
{
	StateTime += _Delta;


	if (StateTime > SWORDKNIGHTRAISESWORDTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SwordKnightState::Slash);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
}


void SwordKnight::SlashStart()
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
		MsgBoxAssert("충돌체가 Null 입니다.");
		return;
	}


	// 사운드 재생
	GameEngineSound::SoundPlay("SwordKnight_AttackSound.wav");



	AbilityCollision->On();
	ChangeAnimationState("Slash");
}

void SwordKnight::SlashUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		if (nullptr == AbilityCollision)
		{
			MsgBoxAssert("충돌체가 Null 입니다.");
			return;
		}

		AbilityCollision->Off();


		int SlashLink = GameEngineRandom::MainRandom.RandomInt(0, 2) / 2;
		switch (SlashLink)
		{
		case 0:
			ChangeState(SwordKnightState::PendulumStride);
			break;
		case 1:
			ChangeState(SwordKnightState::ReversingSlash);
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


void SwordKnight::UnderhandStart()
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
		MsgBoxAssert("충돌체가 Null 입니다.");
		return;
	}

	AbilityCollision->SetCollisionPos(float4{ CollisionPosX , -49.5f });


	ChangeAnimationState("Underhand");
}

void SwordKnight::UnderhandUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SWORDKNIGHTUNDERHANDTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SwordKnightState::ReversingSlash);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
}


void SwordKnight::ReversingSlashStart()
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
		MsgBoxAssert("충돌체가 Null 입니다.");
		return;
	}



	// 사운드 재생
	GameEngineSound::SoundPlay("SwordKnight_AttackSound.wav");


	AbilityCollision->On();
	ChangeAnimationState("ReversingSlash");
}

void SwordKnight::ReversingSlashUpdate(float _Delta)
{

	if (true == MainRenderer->IsAnimationEnd())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		AbilityCollision->Off();
		ChangeState(SwordKnightState::PendulumStride);
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



void SwordKnight::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(SwordKnightState::BeInhaled);
		return;
	}

	if (true == IsHitted)
	{
		ChangeState(SwordKnightState::Hitted);
		return;
	}
}




void SwordKnight::Render(float _Delta)
{
	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//int CameraPos = GetLevel()->GetMainCamera()->GetPos().iX();

	//GameEngineWindowTexture* Backbuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	//HDC LineDC = Backbuffer->GetImageDC();

	//MoveToEx(LineDC, GetPos().iX() - CameraPos, 0, NULL);
	//LineTo(LineDC, GetPos().iX() - CameraPos, WinScale.iY());
}