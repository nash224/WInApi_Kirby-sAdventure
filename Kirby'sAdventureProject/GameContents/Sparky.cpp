#include "Sparky.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"
#include "Kirby.h"
#include "SparkEffect.h"
#include <vector>

Sparky::Sparky()
{
}

Sparky::~Sparky()
{
}


void Sparky::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	GlobalContents::SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	GlobalContents::SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_PowerEnemy.bmp", 25, 25, 0.3f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_PowerEnemy.bmp", 25, 25, 0.3f, false);

	MainRenderer->CreateAnimation("Left_FrontJump", "Left_PowerEnemy.bmp", 24, 24, 0.3f, false);
	MainRenderer->CreateAnimation("Right_FrontJump", "Right_PowerEnemy.bmp", 24, 24, 0.3f, false);

	MainRenderer->CreateAnimation("Left_StanceJump", "Left_PowerEnemy.bmp", 24 , 24 , 0.3f, false);
	MainRenderer->CreateAnimation("Right_StanceJump", "Right_PowerEnemy.bmp", 24 , 24 , 0.3f, false);

	MainRenderer->CreateAnimation("Left_LongJump", "Left_PowerEnemy.bmp", 24, 24, 0.1f, false);
	MainRenderer->CreateAnimation("Right_LongJump", "Right_PowerEnemy.bmp", 24, 24, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Landing", "Left_PowerEnemy.bmp", 26, 26, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Landing", "Right_PowerEnemy.bmp", 26, 26, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Spark", "Left_PowerEnemy.bmp", 27, 28, SPARKYSPARKCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimation("Right_Spark", "Right_PowerEnemy.bmp", 27, 28, SPARKYSPARKCHANGEFRAMETIME, true);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Sparky::init(const std::string& _FileName, SparkyState _State, const float4& _Pos)
{
	Attribute = AttributeType::Electricity;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void Sparky::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}

void Sparky::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SparkyState::Idle:						return IdleUpdate(_Delta);
	case SparkyState::FrontJump:				return FrontJumpUpdate(_Delta);
	case SparkyState::StanceJump:				return StanceJumpUpdate(_Delta);
	case SparkyState::LongJump:					return LongJumpUpdate(_Delta);
	case SparkyState::Landing:					return LandingUpdate(_Delta);
	case SparkyState::Spark:					return SparkUpdate(_Delta);
	default:
		break;
	}
}

void Sparky::ChangeState(SparkyState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case SparkyState::Idle:					IdleStart();					break;
		case SparkyState::FrontJump:			FrontJumpStart();				break;
		case SparkyState::StanceJump:			StanceJumpStart();				break;
		case SparkyState::LongJump:				LongJumpStart();				break;
		case SparkyState::Landing:				LandingStart();					break;
		case SparkyState::Spark:				SparkStart();					break;
		default:
			break;
		}
	}

	State = _State;
}

void Sparky::ChangeRespawnState()
{
	ChangeState(RespawnState);
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Sparky::SetCheckPoint(const float4& _ScaleSize)
{
	GroundLeftCheckPoint = { -_ScaleSize.X + CHECKGROUNDGAP , 0.0f };
	GroundRightCheckPoint = { _ScaleSize.X + -CHECKGROUNDGAP , 0.0f };
	WallBotLeftCheckPoint = { -_ScaleSize.X + CHECKWALLWIDTHHGAP , -CHECKWALLHEIGHTHGAP };
	WallTopLeftCheckPoint = { -_ScaleSize.X + CHECKWALLWIDTHHGAP , -_ScaleSize.Y + CHECKWALLHEIGHTHGAP };
	WallBotRightCheckPoint = { _ScaleSize.X + -CHECKWALLWIDTHHGAP , -CHECKWALLHEIGHTHGAP };
	WallTopRightCheckPoint = { _ScaleSize.X + -CHECKWALLWIDTHHGAP , -_ScaleSize.Y + CHECKWALLHEIGHTHGAP };
	CeilLeftCheckPoint = { -_ScaleSize.X + CHECKGROUNDGAP , -_ScaleSize.Y };
	CeilRightCheckPoint = { _ScaleSize.X + -CHECKGROUNDGAP , -_ScaleSize.Y };

	StairLeftBottomCheckPoint = { -_ScaleSize.X + -SPARKYLONGJUMPSTAIRCOGNIZANCE , -CHECKGAP };
	StairLeftTopCheckPoint = { -_ScaleSize.X + -SPARKYLONGJUMPSTAIRCOGNIZANCE , -CHECKSTAIRHEIGHT + -CHECKGAP };
	StairRightBottomCheckPoint = { _ScaleSize.X + SPARKYLONGJUMPSTAIRCOGNIZANCE , -CHECKGAP };
	StairRightTopCheckPoint = { _ScaleSize.X + SPARKYLONGJUMPSTAIRCOGNIZANCE , -CHECKSTAIRHEIGHT + -CHECKGAP };
}


bool Sparky::IsLeftStair()
{
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), StairLeftBottomCheckPoint);
	unsigned int LeftTopColor = GetGroundColor(RGB(255, 255, 255), StairLeftTopCheckPoint);
	if (RGB(0, 255, 255) == LeftBottomColor && RGB(255, 255, 255) == LeftTopColor)
	{
		return true;
	}

	return false;
}

bool Sparky::IsRightStair()
{
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), StairRightBottomCheckPoint);
	unsigned int RightTopColor = GetGroundColor(RGB(255, 255, 255), StairRightTopCheckPoint);
	if (RGB(0, 255, 255) == RightBottomColor && (RGB(255, 255, 255) == RightTopColor))
	{
		return true;
	}

	return false;
}

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Sparky::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	CurrentSpeed = 0.0f;
	GravityReset();
	ChangeAnimationState("Idle");
}

void Sparky::IdleUpdate(float _Delta)
{
	StateTime += _Delta;
	AbilityStartDeltaTime += _Delta;

	if (AbilityStartDeltaTime > SPARKYIDLETIME * 10.0f)
	{
		ChangeState(SparkyState::Spark);
		return;
	}


	if (StateTime > SPARKYIDLETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		float4 CurrentDir = Kirby::GetMainKirby()->GetPos() - GetPos();

		if ((ActorDir::Left == Dir && CurrentDir.X > 0.0f) ||
			(ActorDir::Right == Dir && CurrentDir.X < 0.0f))
		{
			RemainStanceJumpCount = GameEngineRandom::MainRandom.RandomInt(1, 6) / 3 + 1;
		}

		if (0 != RemainStanceJumpCount)
		{
			--RemainStanceJumpCount;
			ChangeState(SparkyState::StanceJump);
			return;
		}
		else if ((ActorDir::Left == Dir && true == IsLeftStair()) || 
			(ActorDir::Right == Dir && true == IsRightStair()))
		{
			ChangeState(SparkyState::LongJump);
			return;
		}
		else
		{
			ChangeState(SparkyState::FrontJump);
			return;
		}
	}
	

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}
	VerticalUpdate(_Delta);
}


void Sparky::FrontJumpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("FrontJump");
}

void Sparky::FrontJumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (CurrentJumpDistance > SPARKYFRONTJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (true == CeilingCheck())
	{
		AbleJump = false;
		GravityReset();
	}

	if (false == AbleJump && true == GetGroundState())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Landing);
		return;
	}


	if (true == AbleJump)
	{
		float JumpPower = SPARKYFRONTJUMPDISTANCE / SPARKYFRONTJUMPTIME;
		CurrentJumpDistance += JumpPower * _Delta;
		SetGravityVector(float4::UP * CurrentJumpDistance);
	}


	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_FrontJump");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_FrontJump");
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -SPARKYSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = SPARKYSPEED;
	}


	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);

	BlockedByGround();
	BlockedByWall();

	HorizontalUpdate(_Delta);
}


void Sparky::StanceJumpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("StanceJump");
}

void Sparky::StanceJumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (CurrentJumpDistance > SPARKYSTANCEJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (true == CeilingCheck())
	{
		AbleJump = false;
		GravityReset();
	}

	if (false == AbleJump && true == GetGroundState())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Landing);
		return;
	}


	if (true == AbleJump)
	{
		float JumpPower = SPARKYSTANCEJUMPDISTANCE / SPARKYSTANCEJUMPTIME;
		CurrentJumpDistance += JumpPower * _Delta;
		SetGravityVector(float4::UP * CurrentJumpDistance);
	}

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);

	BlockedByGround();
}



void Sparky::LongJumpStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("LongJump");
}

void Sparky::LongJumpUpdate(float _Delta)
{
	StateTime += _Delta;

	if (CurrentJumpDistance > SPARKYLONGJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (true == CeilingCheck())
	{
		AbleJump = false;
		GravityReset();
	}

	if (false == AbleJump && true == GetGroundState())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Landing);
		return;
	}


	if (true == AbleJump)
	{
		float JumpPower = SPARKYLONGJUMPDISTANCE / SPARKYLONGJUMPTIME;
		CurrentJumpDistance += JumpPower * _Delta;
		SetGravityVector(float4::UP * CurrentJumpDistance);
	}


	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_LongJump");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_LongJump");
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -SPARKYSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = SPARKYSPEED;
	}


	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);

	BlockedByGround();
	BlockedByWall();

	HorizontalUpdate(_Delta);
}


void Sparky::LandingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Landing");
}

void Sparky::LandingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > SPARKYLANDINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Idle);
		return;
	}

	BlockedByGround();
	BlockedByWall();

	DecelerationUpdate(_Delta, SPARKYDECELERATIONSPEED);
	HorizontalUpdate(_Delta);
}


void Sparky::SparkStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	AbilityStartDeltaTime = 0.0f;
	SparkCoolDown = 0.0f;
	ChangeAnimationState("Spark");
}

void Sparky::SparkUpdate(float _Delta)
{
	StateTime += _Delta;
	SparkCoolDown += _Delta;

	if (SparkCoolDown > SPARKYSPARKFREQUENCY)
	{
		SparkCoolDown = 0.0f;

		SparkEffect* SparkEffectPtr = GetLevel()->CreateActor<SparkEffect>();
		SparkEffectPtr->init(GetPos(), Scale, float4::UP);
		SparkEffectPtr->SetActorCollision(CollisionOrder::MonsterAbility, CollisionType::Rect);
	}


	if (StateTime > SPARKYABILITYTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(SparkyState::Idle);
		return; 
	}
}


void Sparky::Render(float _Detla)
{
	ActorCollisionDetectionPointRender();
}


void Sparky::ActorCollisionDetectionPointRender()
{
	HDC BackDC = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	// 원점
	Data.Pos = ActorCameraPos();
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 바닥 왼쪽
	Data.Pos = ActorCameraPos() + GroundLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 바닥 오른쪽
	Data.Pos = ActorCameraPos() + GroundRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 하단왼쪽
	Data.Pos = ActorCameraPos() + WallBotLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 상단왼쪽
	Data.Pos = ActorCameraPos() + WallTopLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 하단오른쪽
	Data.Pos = ActorCameraPos() + WallBotRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 상단오른쪽
	Data.Pos = ActorCameraPos() + WallTopRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 천장 왼쪽
	Data.Pos = ActorCameraPos() + CeilLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 천장 오른쪽
	Data.Pos = ActorCameraPos() + CeilRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 계단 왼쪽하단
	Data.Pos = ActorCameraPos() + StairLeftBottomCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 계단 왼쪽상단
	Data.Pos = ActorCameraPos() + StairLeftTopCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 계단 오른쪽하단
	Data.Pos = ActorCameraPos() + StairRightBottomCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 계단 오른쪽상단
	Data.Pos = ActorCameraPos() + StairRightTopCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}