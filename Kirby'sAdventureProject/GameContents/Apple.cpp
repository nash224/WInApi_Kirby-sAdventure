#include "Apple.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "Kirby.h"



Apple::Apple()
{
}

Apple::~Apple()
{
}




void Apple::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	// 텍스처 로드
	GlobalContents::SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	GlobalContents::SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);


	// 애니메이션 생성
	MainRenderer->CreateAnimationToFrame("Left_Idle", "Left_NormalEnemy.bmp", { 8 , 19 }, 0.1f, true);
	MainRenderer->CreateAnimationToFrame("Right_Idle", "Right_NormalEnemy.bmp", { 8 , 19 }, 0.1f, true);

	MainRenderer->CreateAnimation("Left_Fall", "Left_NormalEnemy.bmp", 8, 8, 0.1f, false);
	MainRenderer->CreateAnimation("Right_Fall", "Right_NormalEnemy.bmp", 8, 8, 0.1f, false);

	MainRenderer->CreateAnimation("Left_Bounce", "Left_NormalEnemy.bmp", 8, 8, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Bounce", "Right_NormalEnemy.bmp", 8, 8, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Roll", "Left_NormalEnemy.bmp", 8, 11, 0.1f, true);
	MainRenderer->CreateAnimation("Right_Roll", "Right_NormalEnemy.bmp", 8, 11, 0.1f, true);

	MainRenderer->CreateAnimation("Left_BounceMove", "Left_NormalEnemy.bmp", 8, 11, 0.1f, true);
	MainRenderer->CreateAnimation("Right_BounceMove", "Right_NormalEnemy.bmp", 8, 11, 0.1f, true);

	// 배율 조정
	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	// 기타 적용
	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(NormalState::Idle);



	// 충돌체 생성 및 적용
	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Null 일리가 없어");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->Off();
}


void Apple::init(const float4& _SummonPos)
{
	SetPos(_SummonPos);
}





void Apple::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}



void Apple::IdleStart()
{
	TwinkilingCount = 0;

	GetKirbyDirection();
	ChangeAnimationState("Idle");
}

void Apple::IdleUpdate(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		++TwinkilingCount;
	}


	if (6 == TwinkilingCount)
	{
		ChangeState(NormalState::Fall);
		return;
	}

	EnemyCollisionCheck();

}


void Apple::FallStart()
{
	IsChangeState = false;

	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Null 일리가 없어");
		return;
	}

	BodyCollision->On();

	ChangeAnimationState("Fall");
}

void Apple::FallUpdate(float _Delta)
{
	if (true == GetGroundState())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Bounce);
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


void Apple::BounceStart()
{
	IsChangeState = false;

	SetGravityVector(float4::UP * 300.0f);

	GravityReset();
	ChangeAnimationState("Bounce");
}

void Apple::BounceUpdate(float _Delta)
{

	if (true == GetGroundState() && GetGravityVector().Y > 0.0f)
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Roll);
		return;
	}




	BlockedByGround();


	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);


	EnemyCollisionCheck(); 
}


void Apple::RollStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	GetKirbyDirection();

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -RollPower;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = RollPower;
	}

	GravityReset();
	ChangeAnimationState("Bounce");
}

void Apple::RollUpdate(float _Delta)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨의 정보를 불러오지 못했습니다.");
		return;
	}

	GameEngineCamera* MainLevelCamera = CurLevel->GetMainCamera();
	if (nullptr == MainLevelCamera)
	{
		MsgBoxAssert("카메라의 정보를 불러오지 못했습니다.");
		return;
	}


	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = MainLevelCamera->GetPos();
	float4 ApplePos = GetPos();

	if (ApplePos.X < CameraPos.X - OVERSCREEN_ADDITIONDISTANCE || ApplePos.X > CameraPos.X + WinScale.X + OVERSCREEN_ADDITIONDISTANCE)
	{
		Death();
		EnemyPointerRelease();
	}



	BlockedByGround();


	HorizontalUpdate(_Delta);


	EnemyCollisionCheck();
}



void Apple::BounceMoveStart()
{
	IsSecondBounce = false;

	GetKirbyDirection();

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -RollPower;
	}
	else if (ActorDir::Right == Dir)
	{
		CurrentSpeed = RollPower;
	}

	SetGravityVector(float4::UP * FirstBouncePower);

	ChangeAnimationState("BounceMove");
}

void Apple::BounceMoveUpdate(float _Delta)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨의 정보를 불러오지 못했습니다.");
		return;
	}

	GameEngineCamera* MainLevelCamera = CurLevel->GetMainCamera();
	if (nullptr == MainLevelCamera)
	{
		MsgBoxAssert("카메라의 정보를 불러오지 못했습니다.");
		return;
	}


	if (false == IsSecondBounce && true == GetGroundState() && GetGravityVector().Y > 0.0f)
	{
		IsSecondBounce = true;

		SetGravityVector(float4::UP * SecondBouncePower);
	}




	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = MainLevelCamera->GetPos();
	float4 ApplePos = GetPos();

	if (ApplePos.X < CameraPos.X - OVERSCREEN_ADDITIONDISTANCE || ApplePos.X > CameraPos.X + WinScale.X + OVERSCREEN_ADDITIONDISTANCE)
	{
		Death();
		EnemyPointerRelease();
	}

	
	BlockedByGround();



	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);


	HorizontalUpdate(_Delta);


	EnemyCollisionCheck();
}