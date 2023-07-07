#include "BrontoBurt.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"



BrontoBurt::BrontoBurt()
{
}

BrontoBurt::~BrontoBurt()
{
}




void BrontoBurt::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더를 불러오지 못했습니다.");
		return;
	}

	GlobalContents::SpriteFileLoad("Left_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);
	GlobalContents::SpriteFileLoad("Right_AerialEnemy.bmp", "Resources\\Unit\\Grunt", 3, 3);


	MainRenderer->CreateAnimation("Left_Idle", "Left_AerialEnemy.bmp", 7, 7, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_AerialEnemy.bmp", 7, 7, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Rise", "Left_AerialEnemy.bmp", 6, 7, 0.3f, true);
	MainRenderer->CreateAnimation("Right_Rise", "Right_AerialEnemy.bmp", 6, 7, 0.3f, true);

	MainRenderer->CreateAnimation("Left_Fly", "Left_AerialEnemy.bmp", 6, 7, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Fly", "Right_AerialEnemy.bmp", 6, 7, 0.1f, true);

	MainRenderer->CreateAnimation("Left_WaveFlightRise", "Left_AerialEnemy.bmp", 6, 7, 0.15f, true);
	MainRenderer->CreateAnimation("Right_WaveFlightRise", "Right_AerialEnemy.bmp", 6, 7, 0.15f, true);

	MainRenderer->CreateAnimation("Left_WaveFlightFall", "Left_AerialEnemy.bmp", 6, 6, 0.5f, false);
	MainRenderer->CreateAnimation("Right_WaveFlightFall", "Right_AerialEnemy.bmp", 6, 6, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Exit", "Left_AerialEnemy.bmp", 6, 7, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Exit", "Right_AerialEnemy.bmp", 6, 7, 0.5f, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);



	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	SetName("Bronto Burt");


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Collision 이 Null 일리가 없어..");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void BrontoBurt::init(const std::string& _FileName, BrontoState _State, const float4& _Pos)
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


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void BrontoBurt::Update(float _Delta)
{
	StateUpdate(_Delta);
}


void BrontoBurt::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BrontoState::Idle:					return IdleUpdate(_Delta);
	case BrontoState::Rise:					return RiseUpdate(_Delta);
	case BrontoState::Fly:					return FlyUpdate(_Delta);
	case BrontoState::WaveFlightRise:		return WaveFlightRiseUpdate(_Delta);
	case BrontoState::WaveFlightFall:		return WaveFlightFallUpdate(_Delta);
	case BrontoState::BeInhaled:			return BeInhaledUpdate(_Delta);
	case BrontoState::Hitted:				return HittedUpdate(_Delta);
	default:
		break;
	}
}

void BrontoBurt::ChangeState(BrontoState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case BrontoState::Idle:					IdleStart();					break;
		case BrontoState::Rise:					RiseStart();					break;
		case BrontoState::Fly:					FlyStart();						break;
		case BrontoState::WaveFlightRise:		WaveFlightRiseStart();			break;
		case BrontoState::WaveFlightFall:		WaveFlightFallStart();			break;
		case BrontoState::BeInhaled:			BeInhaledStart();				break;
		case BrontoState::Hitted:				HittedStart();					break;
		default:
			break;
		}
	}

	State = _State;
}

void BrontoBurt::ChangeRespawnState()
{
	ChangeState(RespawnState);
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void BrontoBurt::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsFlyVertically = true;
	ChangeAnimationState("Idle");
}

void BrontoBurt::IdleUpdate(float _Delta)
{
	if (BRONTORECOGNITIONRANGE > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(BrontoState::Rise);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
	BlockedByWall();
}


void BrontoBurt::RiseStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	StopRise = false;
	RiseDistance = 0.0f;
	ParabolicRiseStartDistance = GetPos().Y - BRONTORISEDISTANCE;
	GravityReset();
	ChangeAnimationState("Rise");
}

void BrontoBurt::RiseUpdate(float _Delta)
{
	if (RiseDistance > BRONTORISEDISTANCE && false == StopRise)
	{
		StopRise = true;
	}

	if (true == StopRise && GetPos().Y > ParabolicRiseStartDistance && GetGravityVector().Y > 0.0f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(BrontoState::Fly);
		return;
	}

	EnemyCollisionCheck();

	if (RiseDistance < BRONTORISEDISTANCE && false == StopRise)
	{
		float RisePower = BRONTORISEDISTANCE / BRONTORISETIME;
		RiseDistance += RisePower * _Delta;
		SetGravityVector(float4::UP * RisePower);
	}


	if (true == StopRise)
	{
		Gravity(_Delta);
	}

	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void BrontoBurt::FlyStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsGoForward = false;
	CurrentSpeed = 0.0f;
	ChangeAnimationState("Fly");
}

void BrontoBurt::FlyUpdate(float _Delta)
{
	EnemyCollisionCheck();

	if (GetGravityVector().Y < 0.0f)
	{
		IsGoForward = true;
	}

	if (false == IsGoForward)
	{
		float NowGravityVector = GetGravityVector().Y;
		SetGravityVector(float4::UP * ( NowGravityVector - BRONTOFLYPOWER * _Delta ));
		VerticalUpdate(_Delta);
	}

	if (true == IsGoForward)
	{
		if (ActorDir::Left == Dir)
		{
			CurrentSpeed -= BRONTOFLYSPEED / BRONTOFLYSPEEDACCELERATIONTIME * _Delta;
		}
		else if (ActorDir::Right == Dir)
		{
			CurrentSpeed += BRONTOFLYSPEED / BRONTOFLYSPEEDACCELERATIONTIME * _Delta;
		}

		HorizontalUpdate(_Delta);
	}
}


void BrontoBurt::WaveFlightRiseStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsChangeGravityReverse = false;
	ChangeGravityDistance = RespawnLocation.Y + BRONTOWAVEFLIGHTCHANGEHEIGHT;
	ChangeAnimationState("WaveFlightRise");
}

void BrontoBurt::WaveFlightRiseUpdate(float _Delta)
{
	if (GetPos().Y < ChangeGravityDistance)
	{
		IsChangeGravityReverse = true;
	}

	if (GetGravityVector().Y > 0.0f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(BrontoState::WaveFlightFall);
		return;
	}

	EnemyCollisionCheck();

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -BRONTOWAVEFLIGHTSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = BRONTOWAVEFLIGHTSPEED;
	}

	if (false == IsChangeGravityReverse)
	{
		ReverseGravity(_Delta);
	}
	else if (true == IsChangeGravityReverse)
	{
		Gravity(_Delta);
	}

	VerticalUpdate(_Delta);
	HorizontalUpdate(_Delta);
}


void BrontoBurt::WaveFlightFallStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsChangeGravityReverse = false;

	if (WaveFlightCountBasedFall == 3)
	{
		GravityReset();
		WaveFlightCountBasedFall = 0;
	}
	++WaveFlightCountBasedFall;

	ChangeGravityDistance = RespawnLocation.Y + BRONTOWAVEFLIGHTCHANGEHEIGHT;
	ChangeAnimationState("WaveFlightFall");
}

void BrontoBurt::WaveFlightFallUpdate(float _Delta)
{
	if (GetPos().Y > ChangeGravityDistance)
	{
		IsChangeGravityReverse = true;
	}

	if (GetGravityVector().Y < 0.0f)
	{
		IsChangeState = true;
	}


	if (true == IsChangeState && WaveFlightCountBasedFall < 3)
	{
		ChangeState(BrontoState::WaveFlightRise);
		return;
	}

	EnemyCollisionCheck();


	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -BRONTOWAVEFLIGHTSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = BRONTOWAVEFLIGHTSPEED;
	}

	if (false == IsChangeGravityReverse)
	{
		Gravity(_Delta);
	}
	else if (true == IsChangeGravityReverse)
	{
		ReverseGravity(_Delta);
	}

	VerticalUpdate(_Delta);
	HorizontalUpdate(_Delta);
}


void BrontoBurt::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(BrontoState::BeInhaled);
		return;
	}

	if (true == IsHitted)
	{
		ChangeState(BrontoState::Hitted);
		return;
	}
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void BrontoBurt::Render(float _Delta)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("백버퍼를 불러오지 못했습니다.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();
	if (nullptr == dc)
	{
		MsgBoxAssert("핸들을 불러오지 못했습니다.");
		return;
	}

	int TextRenderNum = 0;


	float4 ActorScenePos = ActorCameraPos();

	int TextXPos = ActorScenePos.iX() - Scale.Half().iX();
	int TextYPos = ActorScenePos.iY() - (Scale * 2.0f).iY();


	EnemyDebugRender(dc, TextRenderNum, TextXPos, TextYPos);
	ThisDebugRender(dc, TextRenderNum, TextXPos, TextYPos);

	ThisDebugTriggerRender(dc);
}


void BrontoBurt::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	if (nullptr == _dc)
	{
		MsgBoxAssert("핸들을 불러오지 못했습니다.");
		return;
	}


	{
		std::string Text = "";
		Text += "비행모드 : ";
		if (true == IsFlyVertically)
		{
			Text += "수직";
		}
		else if (false == IsFlyVertically)
		{
			Text += "커브";
		}
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}


void BrontoBurt::ThisDebugTriggerRender(HDC _dc)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	float4 ActorScenePos = ActorCameraPos();
	float4 DistanceToKriby = GetKirbyOpponentDistance();


	float4 ActorPos = GetPos();

	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return;
	}

	float4 KirbyPos = KirbyPtr->GetPos();
	

	float4 OpponentDistance = KirbyPos - ActorPos;

	if (BrontoState::Idle == State)
	{
		if (OpponentDistance.X < 0.0f)
		{
			MoveToEx(_dc, ActorScenePos.iX() - static_cast<int>(BRONTORECOGNITIONRANGE), 0, NULL);
			LineTo(_dc, ActorScenePos.iX() - static_cast<int>(BRONTORECOGNITIONRANGE), WinScale.iY());
		}
		else if (OpponentDistance.X >= 0.0f)
		{
			MoveToEx(_dc, ActorScenePos.iX() - static_cast<int>(BRONTORECOGNITIONRANGE), 0, NULL);
			LineTo(_dc, ActorScenePos.iX() - static_cast<int>(BRONTORECOGNITIONRANGE), WinScale.iY());
		}
	}

}