#include "HotHead.h"
#include "ContentsEnum.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "Kirby.h"
#include "VegetableValleyPlayLevel.h"
#include "FrameBreathEffect.h"
#include "FireBallEffect.h"


HotHead::HotHead()
{
}

HotHead::~HotHead()
{
}


void HotHead::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	GlobalContents::SpriteFileLoad("Left_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);
	GlobalContents::SpriteFileLoad("Right_PowerEnemy.bmp", "Resources\\Unit\\Grunt", 6, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_PowerEnemy.bmp", 6, 7, HOTHEADWALKINGCHANGEANIMATIONTIME, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_PowerEnemy.bmp", 6, 7, HOTHEADWALKINGCHANGEANIMATIONTIME, true);

	MainRenderer->CreateAnimation("Left_FireBallCharging", "Left_PowerEnemy.bmp", 8, 9, HOTHEADWOBBLETIME, true);
	MainRenderer->CreateAnimation("Right_FireBallCharging", "Right_PowerEnemy.bmp", 8, 9, HOTHEADWOBBLETIME, true);

	MainRenderer->CreateAnimation("Left_FireBall", "Left_PowerEnemy.bmp", 10, 11, HOTHEADWOBBLETIME, true);
	MainRenderer->CreateAnimation("Right_FireBall", "Right_PowerEnemy.bmp", 10, 11, HOTHEADWOBBLETIME, true);

	MainRenderer->CreateAnimation("Left_FlameBreathCharging", "Left_PowerEnemy.bmp", 8, 9, HOTHEADWOBBLETIME, true);
	MainRenderer->CreateAnimation("Right_FlameBreathCharging", "Right_PowerEnemy.bmp", 8, 9, HOTHEADWOBBLETIME, true);

	MainRenderer->CreateAnimation("Left_FlameBreath", "Left_PowerEnemy.bmp", 10, 11, HOTHEADWOBBLETIME, true);
	MainRenderer->CreateAnimation("Right_FlameBreath", "Right_PowerEnemy.bmp", 10, 11, HOTHEADWOBBLETIME, true);


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
	BodyCollision->SetCollisionPos(float4{ 0.0f , -SmallTypeScale.hY()});
	BodyCollision->SetCollisionScale(SmallTypeScale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void HotHead::init(const std::string& _FileName, HotHeadState _State, const float4& _Pos)
{
	Attribute = AttributeType::Fire;
	Ability = AbilityStar::Fire;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void HotHead::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	//CheckOverScreen();
}

void HotHead::StateUpdate(float _Delta)
{
	switch (State)
	{
	case HotHeadState::Walk:					return WalkUpdate(_Delta);
	case HotHeadState::FireBallCharging:		return FireBallChargingUpdate(_Delta);
	case HotHeadState::FireBall:				return FireBallUpdate(_Delta);
	case HotHeadState::FlameBreathCharging:		return FlameBreathChargingUpdate(_Delta);
	case HotHeadState::FlameBreath:				return FlameBreathUpdate(_Delta);
	case HotHeadState::BeInhaled:				return BeInhaledUpdate(_Delta);
	case HotHeadState::Hitted:					return HittedUpdate(_Delta);
	default:
		break;
	}
}

void HotHead::ChangeState(HotHeadState _State)
{
	if (_State != State || _State == RespawnState)
	{
		switch (_State)
		{
		case HotHeadState::Walk:					WalkStart();					break;
		case HotHeadState::FireBallCharging:		FireBallChargingStart();		break;
		case HotHeadState::FireBall:				FireBallStart();				break;
		case HotHeadState::FlameBreathCharging:		FlameBreathChargingStart();		break;
		case HotHeadState::FlameBreath:				FlameBreathStart();				break;
		case HotHeadState::BeInhaled:				BeInhaledStart();				break;
		case HotHeadState::Hitted:					HittedStart();					break;
		default:
			break;
		}
	}

	State = _State;
}

void HotHead::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void HotHead::WalkStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GravityReset();
	GetKirbyDirection();
	ChangeAnimationState("Walk");
}

void HotHead::WalkUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HOTHEADWALKINGCHANGESTATETIME)
	{
		StateTime = 0.0f;

		if(HOTHEADFIREBALLRANGEDETECTION > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
		{
			ChangeState(HotHeadState::FlameBreathCharging);
			return;
		}
		else if (HOTHEADRANGEDETECTION > abs(Kirby::GetMainKirby()->GetPos().X - GetPos().X))
		{
			ChangeState(HotHeadState::FireBallCharging);
			return;
		}
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
		CurrentSpeed = -HOTHEADSPEED;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = HOTHEADSPEED;
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


void HotHead::FireBallChargingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("FireBall");
}

void HotHead::FireBallChargingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HOTHEADFIREBALLCHARGINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(HotHeadState::FireBall);
		return;
	}

	EnemyCollisionCheck();
}


void HotHead::FireBallStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;

	ActorDirUnitVector = GetDirUnitVector();

	float4 DistanceToKriby = GetKirbyOpponentDistance();
	float EffectDeg = DistanceToKriby.AngleDeg();

	if (DistanceToKriby.X < 0.0f)
	{
		if (EffectDeg < SemicircleAngle - FireBall_HighAngle)
		{
			EffectDeg = SemicircleAngle - FireBall_HighAngle;
		}
		else if (EffectDeg >= SemicircleAngle + FireBall_HighAngle)
		{
			EffectDeg = SemicircleAngle + FireBall_HighAngle;
		}
	}
	else if (DistanceToKriby.X >= 0.0f)
	{
		if (EffectDeg > FireBall_HighAngle)
		{
			EffectDeg = -FireBall_HighAngle;
		}
		else if (EffectDeg <= -FireBall_HighAngle)
		{
			EffectDeg = FireBall_HighAngle;
		}
	}

	FireBallEffect* FireBallEffectPtr = GetLevel()->CreateActor<FireBallEffect>(UpdateOrder::Ability);
	if (nullptr == FireBallEffectPtr)
	{
		MsgBoxAssert("액터가 Null 입니다..");
		return;
	}


	FireBallEffectPtr->init(GetPos(), Scale, float4::GetUnitVectorFromDeg(EffectDeg));
	FireBallEffectPtr->SetActorCollision(CollisionOrder::MonsterAbility, CollisionType::Rect);

	ChangeAnimationState("FireBall");
}

void HotHead::FireBallUpdate(float _Delta)
{
	StateTime += _Delta;
	if (StateTime > HOTHEADWOBBLETIME)
	{
		StateTime = 0.0f;
		++WobbleCount;

		if (ActorDir::Left == Dir)
		{
			if (1 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 6.0f);
			}
			else if (2 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 4.0f);
			}
			else if (0 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 2.0f);
			}
		}
		else if (ActorDir::Right == Dir)
		{
			if (1 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 6.0f);
			}
			else if (2 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 4.0f);
			}
			else if (0 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 2.0f);
			}
		}
	}

	if (9 == WobbleCount)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ActorDirUnitVector = float4::ZERO;
		ChangeState(HotHeadState::Walk);
		return;
	}

	EnemyCollisionCheck();

}

void HotHead::FlameBreathChargingStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	GetKirbyDirection();
	ChangeAnimationState("FlameBreathCharging");
}

void HotHead::FlameBreathChargingUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HOTHEADFLAMEBREATHCHARGINGTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(HotHeadState::FlameBreath);
		return;
	}

	EnemyCollisionCheck();
}


void HotHead::FlameBreathStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	WobbleCount = 0;
	ActorDirUnitVector = GetDirUnitVector();
	ChangeAnimationState("FlameBreath");
}

void HotHead::FlameBreathUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > HOTHEADWOBBLETIME)
	{
		StateTime = 0.0f;
		++WobbleCount;

		FrameBreathEffect* FrameBreathEffectPtr = GetLevel()->CreateActor<FrameBreathEffect>(UpdateOrder::Ability);
		FrameBreathEffectPtr->init(GetPos(), Scale, ActorDirUnitVector);
		FrameBreathEffectPtr->SetActorCollision(CollisionOrder::MonsterAbility, CollisionType::Rect);


		if (ActorDir::Left == Dir)
		{
			if (1 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 6.0f);
			}
			else if (2 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 4.0f);
			}
			else if (0 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 2.0f);
			}
		}
		else if (ActorDir::Right == Dir)
		{
			if (1 == WobbleCount % 3)
			{
				AddPos(float4::RIGHT * 6.0f);
			}
			else if (2 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 4.0f);
			}
			else if (0 == WobbleCount % 3)
			{
				AddPos(float4::LEFT * 2.0f);
			}
		}
	}

	if (45 == WobbleCount)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ActorDirUnitVector = float4::ZERO;
		ChangeState(HotHeadState::Walk);
		return;
	}

	EnemyCollisionCheck();
}


void HotHead::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(HotHeadState::BeInhaled);
		return;
	}

	if (true == IsHitted)
	{
		ChangeState(HotHeadState::Hitted);
		return;
	}
}


void HotHead::Render(float _Delta)
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


	float4 DistanceToKriby = GetKirbyOpponentDistance();
	float EffectDeg = DistanceToKriby.AngleDeg();

	{
		std::string Text = "";
		Text += "FireBall 각도";
		Text += std::to_string(static_cast<int>(EffectDeg));
		TextOutA(dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}

	{
		std::string Text = "";
		Text += "클리어";
		TextOutA(dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}

	

}