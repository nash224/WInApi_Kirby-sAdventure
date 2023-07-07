#include "WaddleDee.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"




WaddleDee::WaddleDee() 
{
}

WaddleDee::~WaddleDee() 
{
}


void WaddleDee::Start() 
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}


	GlobalContents::SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4,5);
	GlobalContents::SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_NormalEnemy.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_NormalEnemy.bmp", 0, 1, 0.5f, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;

	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -SMALLTYPECOLLISIONSCALE.hY() });
	BodyCollision->SetCollisionScale(SMALLTYPECOLLISIONSCALE);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */



void WaddleDee::Update(float _Delta) 
{
	GroundCheck();

	StateUpdate(_Delta);
}



void WaddleDee::WalkStart()
{
	StateTime = 0.0f;
	ChangeAnimationState("Walk");
}

void WaddleDee::WalkUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	if (true == CheckLeftWall() || LeftGroundIsCliff())
	{
		Dir = ActorDir::Right;

		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
			return;
		}

		MainRenderer->ChangeAnimation("Right_Walk");
	}
	else if (true == CheckRightWall() || RightGroundIsCliff())
	{
		Dir = ActorDir::Left;

		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
			return;
		}

		MainRenderer->ChangeAnimation("Left_Walk");
	}

	if (ActorDir::Left == Dir)
	{
		CurrentSpeed = -WaddleSpeed;
		AddPos(float4::LEFT * WaddleSpeed * _Delta);
	}

	if (ActorDir::Right == Dir)
	{
		CurrentSpeed = WaddleSpeed;
		AddPos(float4::RIGHT * WaddleSpeed * _Delta);
	}

	BlockedByGround();
	BlockedByWall();

	EnemyCollisionCheck();
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void WaddleDee::Render(float _Delta)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("����۸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();
	if (nullptr == dc)
	{
		MsgBoxAssert("�ڵ��� �ҷ����� ���߽��ϴ�.");
		return;
	}

	int TextRenderNum = 0;


	float4 ActorScenePos = ActorCameraPos();

	int TextXPos = ActorScenePos.iX() - Scale.Half().iX();
	int TextYPos = ActorScenePos.iY() - (Scale * 2.0f).iY();


	EnemyDebugRender(dc, TextRenderNum, TextXPos, TextYPos);
}