#include "Kabu.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"



Kabu::Kabu()
{
}

Kabu::~Kabu()
{
}




void Kabu::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}


	GlobalContents::SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	GlobalContents::SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);



	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 4, 7, KABUIDLESPIN, true);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 4, 7, KABUIDLESPIN, true);
	
	MainRenderer->CreateAnimation("Left_Jump", "Left_NormalEnemy.bmp", 4, 7, KABUJUMPSPIN, true);
	MainRenderer->CreateAnimation("Right_Jump", "Right_NormalEnemy.bmp", 4, 7, KABUJUMPSPIN, true);

	MainRenderer->CreateAnimation("Left_Sit", "Left_NormalEnemy.bmp", 18, 18, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Sit", "Right_NormalEnemy.bmp", 18, 18, 0.5f, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);



	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	SetName("Kabu");


	ChangeState(NormalState::Idle);


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Null 일리가 없어");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Kabu::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}




void Kabu::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	GetKirbyDirection();

	ChangeAnimationState("Idle");

}

void Kabu::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= KABUCHANGETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Sit);
		return; 
	}


	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	EnemyCollisionCheck();
}



void Kabu::SitStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	ChangeAnimationState("Sit");
}

void Kabu::SitUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= KABUSITTIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Jump);
		return; 
	}


	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	EnemyCollisionCheck();
}



void Kabu::JumpStart()
{
	StateTime = 0.0f;
	CurrentSpeed = 0.0f;
	CurrentJumpDistance = 0.0f;
	JumpRatio = 1.0f;
	IsChangeState = false;
	AbleJump = true;

	// 점프 비율 설정
	int RatioNumber = GameEngineRandom::MainRandom.RandomInt(0,2);
	JumpRatio += static_cast<float>(RatioNumber) * 0.5f;

	GetKirbyDirection();
	GravityReset();

	ChangeAnimationState("Jump");
}

void Kabu::JumpUpdate(float _Delta)
{
	if (true == CeilingCheck())
	{
		GravityReset();
		IsChangeState = true;
		AbleJump = false;
	}

	if (GetGravityVector().Y > 0.0f)
	{
		IsChangeState = true;
	}

	if (true == GetGroundState() && true == IsChangeState)
	{
		ChangeState(NormalState::Idle);
		return;
	}



	if (true == AbleJump)
	{
		float JumpPower = KABUJUMPDISTANCE / KABUJUMPTIME;
		CurrentJumpDistance += JumpPower * _Delta;
	}

	if (CurrentJumpDistance > KABUJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (true == AbleJump)
	{
		SetGravityVector(float4::UP * CurrentJumpDistance);
	}


	if (false == IsChangeState)
	{
		if (ActorDir::Left == Dir)
		{
			CurrentSpeed -= KABUSPEED * _Delta;
		}
		if (ActorDir::Right == Dir)
		{
			CurrentSpeed += KABUSPEED * _Delta;
		}
	}

	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;

		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return;
		}

		MainRenderer->ChangeAnimation("Right_Jump");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;

		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return;
		}

		MainRenderer->ChangeAnimation("Left_Jump");
	}


	BlockedByGround();
	BlockedByCeiling();
	BlockedByWall();

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);

	if (true == IsChangeState)
	{
		DecelerationUpdate(KABUDECELERATIONSPEED, _Delta);
	}
	HorizontalSpeedLimit(KABUMAXSPEED);
	HorizontalUpdate(_Delta);



	EnemyCollisionCheck();
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Kabu::Render(float _Delta)
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
	ThisDebugRender(dc, TextRenderNum, TextXPos, TextYPos);

}


void Kabu::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	{
		std::string Text = "";
		Text += "점프 비율 : ";
		Text += std::to_string(JumpRatio);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}
