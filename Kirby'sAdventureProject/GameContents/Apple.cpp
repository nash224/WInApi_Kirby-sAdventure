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
#include "CrossDeathEffect.h"



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
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}

	// �ؽ�ó �ε�
	GlobalContents::SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	GlobalContents::SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);


	// �ִϸ��̼� ����
	MainRenderer->CreateAnimationToFrame("Left_Idle", "Left_NormalEnemy.bmp", { 8 , 19 }, 0.1f, true);
	MainRenderer->CreateAnimationToFrame("Right_Idle", "Right_NormalEnemy.bmp", { 8 , 19 }, 0.1f, true);

	MainRenderer->CreateAnimation("Left_Fall", "Left_NormalEnemy.bmp", 8, 8, 0.2f, false);
	MainRenderer->CreateAnimation("Right_Fall", "Right_NormalEnemy.bmp", 8, 8, 0.2f, false);

	MainRenderer->CreateAnimation("Left_Bounce", "Left_NormalEnemy.bmp", 8, 8, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Bounce", "Right_NormalEnemy.bmp", 8, 8, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Roll", "Left_NormalEnemy.bmp", 8, 11, 0.2f, true);
	MainRenderer->CreateAnimation("Right_Roll", "Right_NormalEnemy.bmp", 8, 11, 0.2f, true);

	MainRenderer->CreateAnimation("Left_BounceMove", "Left_NormalEnemy.bmp", 8, 11, 0.2f, true);
	MainRenderer->CreateAnimation("Right_BounceMove", "Right_NormalEnemy.bmp", 8, 11, 0.2f, true);

	// ���� ����
	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);


	// ��Ÿ ����
	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(NormalState::Idle);


	Ability = AbilityStar::Normal;



	// �浹ü ���� �� ����
	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Null �ϸ��� ����");
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
		MsgBoxAssert("�������� Null �Դϴ�.");
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
}


void Apple::FallStart()
{
	IsChangeState = false;

	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Null �ϸ��� ����");
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
		int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, 2);

		switch (RandomValue)
		{
		case 1:
			ChangeState(NormalState::Bounce);
			break;
		case 2:
			ChangeState(NormalState::BounceMove);
			break;
		default:
			break;
		}
		
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
	ChangeAnimationState("Roll");
}

void Apple::RollUpdate(float _Delta)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ ������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	GameEngineCamera* MainLevelCamera = CurLevel->GetMainCamera();
	if (nullptr == MainLevelCamera)
	{
		MsgBoxAssert("ī�޶��� ������ �ҷ����� ���߽��ϴ�.");
		return;
	}


	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = MainLevelCamera->GetPos();
	float4 ApplePos = GetPos();

	if (ApplePos.X < CameraPos.X - OVERSCREEN_ADDITIONDISTANCE || ApplePos.X > CameraPos.X + WinScale.X + OVERSCREEN_ADDITIONDISTANCE)
	{
		Death();
		EnemyPointerRelease();
		return;
	}



	BlockedByGround();


	HorizontalUpdate(_Delta);


	EnemyCollisionCheck();
}



void Apple::BounceMoveStart()
{
	IsSecondBounce = false;
	StopBounce = false;

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
		MsgBoxAssert("������ ������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	GameEngineCamera* MainLevelCamera = CurLevel->GetMainCamera();
	if (nullptr == MainLevelCamera)
	{
		MsgBoxAssert("ī�޶��� ������ �ҷ����� ���߽��ϴ�.");
		return;
	}


	if (false == IsSecondBounce && true == GetGroundState() && GetGravityVector().Y > 0.0f)
	{
		IsSecondBounce = true;

		SetGravityVector(float4::UP * SecondBouncePower);
	}

	if (true == IsSecondBounce && true == GetGroundState() && GetGravityVector().Y > 0.0f)
	{
		StopBounce = true;
	}




	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = MainLevelCamera->GetPos();
	float4 ApplePos = GetPos();

	if (ApplePos.X < CameraPos.X - OVERSCREEN_ADDITIONDISTANCE || ApplePos.X > CameraPos.X + WinScale.X + OVERSCREEN_ADDITIONDISTANCE)
	{
		Death();
		EnemyPointerRelease();
		return;
	}

	
	BlockedByGround();


	if (false == StopBounce)
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}



	HorizontalUpdate(_Delta);


	EnemyCollisionCheck();
}




// Ŀ�񿡰� �������� ��������
void Apple::BeInhaledStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	CurrentSpeed = 0.0f;
	IsInhaledStateOn = false;
	BodyCollision->Off();
	ActorDirUnitVector = GetKirbyOpponentDistance();
}

void Apple::BeInhaledUpdate(float _Delta)
{
	StateTime += _Delta;

	InhaleTargetPos = GetKirbyOpponentDistance();
	InhaleTargetPosYDistance = InhaleTargetPos.Y - KIRBYCENTERYPOINT;
	InhaleTargetPosXDistance = InhaleTargetPos.X;
	CurentVerticalSpeed += InhaleTargetPosYDistance / INHALETIME * _Delta;

	float4 KirbyPos = Kirby::GetMainKirby()->GetPos();


	if (ActorDirUnitVector.X < 0.0f)
	{
		float InhaleXSpeed = InhaleTargetPosXDistance / INHALETIME * _Delta;
		CurrentSpeed += InhaleXSpeed;

		if (GetPos().X < KirbyPos.X)
		{
			Death();
			EnemyPointerRelease();
			return;
		}
	}
	else if (ActorDirUnitVector.X > 0.0f)
	{
		float InhaleXSpeed = InhaleTargetPosXDistance / INHALETIME * _Delta;
		CurrentSpeed += InhaleXSpeed;

		if (GetPos().X > KirbyPos.X)
		{
			Death();
			EnemyPointerRelease();
			return;
		}
	}


	VerticalUpdateBasedlevitation(_Delta);

	HorizontalUpdate(_Delta);
}




// ���ظ� ���� ��������
void Apple::HittedStart()
{
	StateTime = 0.0f;
	IsChangeState = false;


	CrossDeathEffect* CrossDeathEffectPtr = GetLevel()->CreateActor<CrossDeathEffect>(UpdateOrder::Ability);
	if (nullptr == CrossDeathEffectPtr)
	{
		MsgBoxAssert("���Ͱ� Null �ϸ��� ����..");
		return;
	}

	CrossDeathEffectPtr->init(GetPos(), Scale);

}

void Apple::HittedUpdate(float _Delta)
{
	Death();
	EnemyPointerRelease();
}