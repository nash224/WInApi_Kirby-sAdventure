#include "Togezo.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"


Togezo::Togezo()
{
}

Togezo::~Togezo()
{
}


void Togezo::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	GlobalContents::SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	GlobalContents::SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_PowerEnemy.bmp", 12, 13, 0.2f, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_PowerEnemy.bmp", 12, 13, 0.2f, true);

	MainRenderer->CreateAnimationToFrame("Left_Bounce", "Left_PowerEnemy.bmp", {14, 15, 16, 29}, TOGEZOROLLINGCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Bounce", "Right_PowerEnemy.bmp", { 14, 15, 16, 29 }, TOGEZOROLLINGCHANGEFRAMETIME, true);

	MainRenderer->CreateAnimationToFrame("Left_Roll", "Left_PowerEnemy.bmp", { 14, 15, 16, 29 }, TOGEZOROLLINGCHANGEFRAMETIME, true);
	MainRenderer->CreateAnimationToFrame("Right_Roll", "Right_PowerEnemy.bmp", { 14, 15, 16, 29 }, TOGEZOROLLINGCHANGEFRAMETIME, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	SetName("Togezo");


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("바디 콜리전이 Null일리가 없어..");
		return;
	}
	BodyCollision->SetCollisionPos(float4{ 0.0f, -Scale.hY()});
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->On();

	AbilityCollision = CreateCollision(CollisionOrder::MonsterAbility);
	if (nullptr == AbilityCollision)
	{
		MsgBoxAssert("바디 콜리전이 Null일리가 없어..");
		return;
	}
	AbilityCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY()});
	AbilityCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	AbilityCollision->SetCollisionType(CollisionType::Rect);
	AbilityCollision->Off();
}

void Togezo::init(const std::string& _FileName, TogezoState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Thorn;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void Togezo::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}


// 상태 업데이트
void Togezo::StateUpdate(float _Delta)
{
	switch (State)
	{
	case TogezoState::Walk:						return WalkUpdate(_Delta);
	case TogezoState::Bounce:					return BounceUpdate(_Delta);
	case TogezoState::Roll:						return RollUpdate(_Delta);
	case TogezoState::BeInhaled:				return BeInhaledUpdate(_Delta);
	case TogezoState::Hitted:					return HittedUpdate(_Delta);
	default:
		break;
	}
}


// 상태 변경
void Togezo::ChangeState(TogezoState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case TogezoState::Walk:						WalkStart();					break;
		case TogezoState::Bounce:					BounceStart();					break;
		case TogezoState::Roll:						RollStart();					break;
		case TogezoState::BeInhaled:				BeInhaledStart();				break;
		case TogezoState::Hitted:					HittedStart();					break;
		default:
			break;
		}
	}

	State = _State;
}


// 순수가상함수 Level에서 호출
void Togezo::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Togezo::WalkStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("Walk");
}

void Togezo::WalkUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > TOGEZOROLLINGCOOLDOWN)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(TogezoState::Bounce);
		return;
	}

	EnemyCollisionCheck();

	if (true == CheckLeftWall() || true == LeftGroundIsCliff())
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_Walk");
	}
	else if (true == CheckRightWall() || true == RightGroundIsCliff())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_Walk");
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -TOGEZOSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = TOGEZOSPEED;
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



void Togezo::BounceStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	BounceCount = 0;
	GetKirbyDirection();
	GravityReset();
	AbilityCollision->On();
	ChangeAnimationState("Bounce");
}

void Togezo::BounceUpdate(float _Delta)
{
	// 공이 튀기는 모습
	if (true == GetGroundState() && 0.0f < GetGravityVector().Y)
	{
		switch (BounceCount)
		{
		case 0:
			++BounceCount;
			SetGravityVector(float4::UP * TOGEZOJUMPDISTANCE);
			break;
		case 1:
			++BounceCount;
			SetGravityVector(float4::UP * TOGEZOJUMPDISTANCE * 0.7f);
			break;
		case 2:
			++BounceCount;
			SetGravityVector(float4::UP * TOGEZOJUMPDISTANCE * 0.35f);
			break;
		case 3:
			IsChangeState = true;
			break;
		default:
			break;
		}
	}

	if (true == IsChangeState)
	{
		ChangeState(TogezoState::Roll);
		return;
	}


	EnemyCollisionCheck();
	EnemyAbilityAttack();

	BlockedByGround();

	Gravity(_Delta);
	GravityLimit(GRAVITYMAXVECTOR);
	VerticalUpdate(_Delta);
}

void Togezo::RollStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	IsRollingSpeedZero = false;
	RollingSpeedZeroTime = 1.0f;

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -TOGEZOROLLINGSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = TOGEZOROLLINGSPEED;
	}
	ChangeAnimationState("Roll");
}

void Togezo::RollUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > TOGEZOROLLINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		AbilityCollision->Off();
		ChangeState(TogezoState::Walk);
		return;
	}



	EnemyCollisionCheck();
	EnemyAbilityAttack();




	if (ActorDir::Left == Dir && true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = TOGEZOROLLINGSPEED;
		ChangeAnimationState("Roll");
	}
	else if (ActorDir::Right == Dir && true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -TOGEZOROLLINGSPEED;
		ChangeAnimationState("Roll");
	}

	if ((ActorDir::Left == Dir && true == LeftGroundIsCliff()) || 
		(ActorDir::Right == Dir && true == RightGroundIsCliff()))
	{
		IsRollingSpeedZero = true;
	}

	if (true == IsRollingSpeedZero)
	{
		RollingSpeedZeroTime -= _Delta;
	}

	if (RollingSpeedZeroTime < 0.0f && true == IsRollingSpeedZero)
	{
		if (ActorDir::Left == Dir)
		{
			Dir = ActorDir::Right;
		}
		else if (ActorDir::Right == Dir)
		{
			Dir = ActorDir::Left;
		}
		CurrentSpeed = -CurrentSpeed;

		ChangeAnimationState("Roll");

		RollingSpeedZeroTime = 1.0f;
		IsRollingSpeedZero = false;
	}


	BlockedByGround();
	BlockedByWall();

	if (false == IsRollingSpeedZero)
	{
		HorizontalUpdate(_Delta);
	}
}



// 충돌 처리 분기
void Togezo::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(TogezoState::BeInhaled);
		return;
	}

	if (true == IsHitted)
	{
		ChangeState(TogezoState::Hitted);
		return;
	}
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Togezo::Render(float _Delta)
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

}


void Togezo::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	if (nullptr == _dc)
	{
		MsgBoxAssert("핸들을 불러오지 못했습니다.");
		return;
	}

	{
		std::string Text = "";
		Text += "바운스 횟수 : ";
		Text += std::to_string(BounceCount);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "방향 전환 타이머 : ";
		Text += std::to_string(RollingSpeedZeroTime);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}
