#include "WaddleDee.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

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

	ResourcesManager::GetInst().SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4,5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Walk", "Left_NormalEnemy.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Walk", "Right_NormalEnemy.bmp", 0, 1, 0.5f, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);


	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}


void WaddleDee::SetDirectionAndFirstAnimation()
{
	if (nullptr == Kirby::GetMainKirby())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_Walk");
		return;
	}

	float4 StartDir = Kirby::GetMainKirby()->GetPos() - GetPos();

	if (StartDir.X < 0.0f)
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_Walk");
	}
	else if (StartDir.X >= 0.0f)
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_Walk");
	}
	else
	{
		MsgBoxAssert("몬스터의 리스폰 위치가 잘못되었습니다.");
		return;
	}
}

void WaddleDee::Update(float _Delta) 
{
	GroundCheck();

	WaddleDeeMovement(_Delta);

	CheckOverScreen();
}



void WaddleDee::WaddleDeeMovement(float _Delta)
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
		MainRenderer->ChangeAnimation("Right_Walk");
	}
	else if (true == CheckRightWall() || RightGroundIsCliff())
	{
		Dir = ActorDir::Left;
		MainRenderer->ChangeAnimation("Left_Walk");
	}

	if (ActorDir::Left == Dir)
	{
		AddPos(float4::LEFT * WaddleSpeed * _Delta);
	}

	if (ActorDir::Right == Dir)
	{
		AddPos(float4::RIGHT * WaddleSpeed * _Delta);
	}

	BlockedByGround();
	BlockedByWall();
}