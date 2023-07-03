#include "PoppyBrosJr.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"





// 슈도코드
// GameEngienRenderer* AppleRender = CreateRenderer()
// AppleRender->SetRenderPos(0,0,0)

// 슈도코드
// GameEngienRenderer* MonsterRender = CreateRenderer()
// MonsterRender->SetRenderPos(0,-90,0)

// AppleRunStart() 
//{
//   AppleRender->Change("AppleRun");
//   MonsterRender->Change("AppleRun");
//}

// AppleDeathStart() 
//{
//   AppleRender->Death();
//   AppleRender = nullptr;
//   MonsterRender->Change("AppleRun");
//   MonsterRender->SetRenderPos({0, 0, 0});
//}

// AppleDeathUpdate() 
//{
//   AppleRender->Death();
//   AppleRender = nullptr;
//   MonsterRender->Change("AppleRun");
//   MonsterRender->SetRenderPos();
//}




PoppyBrosJr::PoppyBrosJr()
{
}

PoppyBrosJr::~PoppyBrosJr()
{
}




void PoppyBrosJr::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러 생성에 실패했습니다.");
		return;
	}

	GlobalContents::SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	GlobalContents::SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);


	MainRenderer->CreateAnimation("Left_AppleRun", "Left_NormalEnemy.bmp", 16, 17, 0.2f, true);
	MainRenderer->CreateAnimation("Right_AppleRun", "Right_NormalEnemy.bmp", 16, 17, 0.2f, true);

	MainRenderer->CreateAnimation("Left_Escape", "Left_NormalEnemy.bmp", 17, 17, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Escape", "Right_NormalEnemy.bmp", 17, 17, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 16, 16, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 16, 16, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Jump", "Left_NormalEnemy.bmp", 17, 17, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Jump", "Right_NormalEnemy.bmp", 17, 17, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Fall", "Left_NormalEnemy.bmp", 17, 17, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Fall", "Right_NormalEnemy.bmp", 17, 17, 0.5f, false);


	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(NormalState::Idle);


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);


	// 사운드 재생
	GlobalContents::SoundFileLoad("Jr_Sound.wav", "Resources\\SoundResources\\EffectVoice");
}

void PoppyBrosJr::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}




void PoppyBrosJr::AppleRunStart()
{
	SetCheckPoint(float4{ 48.0f , 96.0f });

	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("AppleRun");
}



void PoppyBrosJr::AppleRunUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= POPPYBROSJRCHANGETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Jump);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}




void PoppyBrosJr::EscapeStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Idle");
}

void PoppyBrosJr::EscapeUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= POPPYBROSJRCHANGETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Jump);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}



void PoppyBrosJr::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Idle");
}

void PoppyBrosJr::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= POPPYBROSJRCHANGETIME)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Jump);
		return;
	}

	EnemyCollisionCheck();

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void PoppyBrosJr::JumpStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();

	// 사운드 재생
	GameEngineSound::SoundPlay("Jr_Sound.wav");

	ChangeAnimationState("Jump");
}

void PoppyBrosJr::JumpUpdate(float _Delta)
{
	if (0.0f < GetGravityVector().Y)
	{
		ChangeState(NormalState::Fall);
		return;
	}

	EnemyCollisionCheck();

	float JumpPower = POPPYBROSJRJUMPDISTANCE / POPPYBROSJRJUMPTIME;
	CurrentJumpDistance += JumpPower * _Delta;

	if (CurrentJumpDistance > POPPYBROSJRJUMPDISTANCE)
	{
		AbleJump = false;
	}

	if (CurrentJumpDistance < POPPYBROSJRJUMPDISTANCE && true == AbleJump)
	{
		SetGravityVector(float4::UP * JumpPower);
	}

	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Right_Jump");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Left_Jump");
	}

	if (ActorDir::Left == Dir)
	{
		AddPos(float4::LEFT * POPPYBROSJRSPEED * _Delta);
	}

	if (ActorDir::Right == Dir)
	{
		AddPos(float4::RIGHT * POPPYBROSJRSPEED * _Delta);
	}


	BlockedByGround();
	BlockedByWall();

	if (false == AbleJump)
	{
		Gravity(_Delta);
	}
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}


void PoppyBrosJr::FallStart()
{
	StateTime = 0.0f;
	AbleJump = true;
	CurrentJumpDistance = 0.0f;
	GravityReset();
	ChangeAnimationState("Fall");
}

void PoppyBrosJr::FallUpdate(float _Delta)
{
	if (true == GetGroundState())
	{
		ChangeState(NormalState::Idle);
		return;
	}

	EnemyCollisionCheck();

	if (true == CheckLeftWall())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Right_Fall");
	}
	else if (true == CheckRightWall())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;
		MainRenderer->ChangeAnimation("Left_Fall");
	}

	if (ActorDir::Left == Dir)
	{
		AddPos(float4::LEFT * POPPYBROSJRSPEED * _Delta);
	}

	if (ActorDir::Right == Dir)
	{
		AddPos(float4::RIGHT * POPPYBROSJRSPEED * _Delta);
	}


	BlockedByGround();
	BlockedByWall();

	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);
}




void PoppyBrosJr::Render(float _Delta)
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


void PoppyBrosJr::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	{
		std::string Text = "";
		Text += "사과 없엉";
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}

