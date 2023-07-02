#include "Pengi.h"
#include "ContentsEnum.h"


#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "Kirby.h"
#include <vector>


Pengi::Pengi()
{
}

Pengi::~Pengi()
{
}


void Pengi::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	GlobalContents::TextureFileLoad("Right_Pengi.bmp", "Resources\\Unit\\Grunt");

	MainRenderer->SetTexture("Right_Pengi.bmp");


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Right;


	SetName("Pengi");


	BodyCollision = CreateCollision(CollisionOrder::ForDisplay);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("바디 콜리전이 Null일리가 없어..");
		return;
	}
	BodyCollision->SetCollisionPos(float4{ 0.0f, -Scale.hY() });
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->On();
}

void Pengi::init(const std::string& _FileName, PengiState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Ice;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void Pengi::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	//CheckOverScreen();
}

void Pengi::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PengiState::Idle:					return IdleUpdate(_Delta);
	case PengiState::BeInhaled:				return BeInhaledUpdate(_Delta);
	default:
		break;
	}
}

void Pengi::ChangeState(PengiState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PengiState::Idle:					IdleStart();					break;
		case PengiState::BeInhaled:				BeInhaledStart();				break;
		default:
			break;
		}
	}

	State = _State;
}

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Pengi::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("Walk");
}

void Pengi::IdleUpdate(float _Delta)
{
	Gravity(_Delta);
	GravityLimit(_Delta);

	BlockedByGround();

	if (false == GetGroundState())
	{
		VerticalUpdate(_Delta);
	}

	EnemyCollisionCheck();
}



void Pengi::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(PengiState::BeInhaled);
		return;
	}
}
