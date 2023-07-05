#include "BroomHatter.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "DustEffect.h"
#include "Kirby.h"



BroomHatter::BroomHatter() 
{
}

BroomHatter::~BroomHatter() 
{
}


void BroomHatter::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� Null �ϸ��� ����");
		return;
	}


	GlobalContents::SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	GlobalContents::SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);


	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 3, 3, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 3, 3, 0.5f, false);

	MainRenderer->CreateAnimation("Left_Sweep", "Left_NormalEnemy.bmp", 2, 2, 0.5f, false);
	MainRenderer->CreateAnimation("Right_Sweep", "Right_NormalEnemy.bmp", 2, 2, 0.5f, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);



	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	SetName("Broom Hatter");

	ChangeState(NormalState::Idle);



	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("Collision �� Null �ϸ��� ����");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);



	// ���� �ε�
	GlobalContents::SoundFileLoad("HatterSound.wav", "Resources\\SoundResources\\EffectVoice");
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void BroomHatter::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}




void BroomHatter::IdleStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("Idle");
}

void BroomHatter::IdleUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime >= BROOMHATTERCHANGETIME)
	{
		IsChangeState = true;
	} 

	if (true == IsChangeState)
	{
		ChangeState(NormalState::Sweep);
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


void BroomHatter::SweepStart() 
{
	StateTime = 0.0f;
	++SweepCount;
	GetKirbyDirection();

	if (3 == SweepCount)
	{
		SweepCount = 0;
	}

	if (Dir == ActorDir::Left)
	{
		CurrentSpeed = -BROOMHATTERSPEED;
	}
	else if (Dir == ActorDir::Right)
	{
		CurrentSpeed = BROOMHATTERSPEED;
	}

	if (2 == SweepCount)
	{
		if (Dir == ActorDir::Left)
		{
			Dir = ActorDir::Right;
		}
		else if (Dir == ActorDir::Right)
		{
			Dir = ActorDir::Left;
		}
		CurrentSpeed = -CurrentSpeed;
	}

	
	GameEngineSound::SoundPlay("HatterSound.wav");


	ChangeAnimationState("Sweep");
}

void BroomHatter::SweepUpdate(float _Delta) 
{
	if (CurrentSpeed == 0.0f)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}


		float4 EffectDir = GetDirUnitVector();
		DustEffect* DustEffectPtr = CurLevelPtr->CreateActor<DustEffect>(UpdateOrder::Ability);
		if (nullptr == DustEffectPtr)
		{
			MsgBoxAssert("Null �ϸ��� ����..");
			return;
		}

		DustEffectPtr->init(GetPos(), Scale, EffectDir);


		ChangeState(NormalState::Idle);
		return;
	}





	if (true == CheckLeftWall() || LeftGroundIsCliff())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = -CurrentSpeed;

		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
			return;
		}

		MainRenderer->ChangeAnimation("Right_Sweep");
	}
	else if (true == CheckRightWall() || RightGroundIsCliff())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -CurrentSpeed;

		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
			return;
		}

		MainRenderer->ChangeAnimation("Left_Sweep");
	}

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	DecelerationUpdate(BROOMHATTERDECELERATIONSPEED, _Delta);
	HorizontalSpeedLimit(BROOMHATTERMAXSPEED);
	HorizontalUpdate(_Delta);


	EnemyCollisionCheck();
}




/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void BroomHatter::Render(float _Delta)
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

}
