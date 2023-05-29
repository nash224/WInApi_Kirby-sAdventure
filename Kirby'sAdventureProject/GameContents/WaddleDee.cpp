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
	float4 StartDir = Kirby::GetMainKirby()->GetPos() - GetPos();

	if (StartDir.X < Kirby::GetMainKirby()->GetPos().X)
	{
		Dir = ActorDir::Right;
		MainRenderer->ChangeAnimation("Right_Walk");
	}
	else if (StartDir.X > Kirby::GetMainKirby()->GetPos().X)
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
}


void WaddleDee::Render(float _Delta) 
{

}

void WaddleDee::init(const std::string _FileName, float4 _Pos)
{
	SetGroundTexture(_FileName);
	SetPos(_Pos);
	RespawnLocation = _Pos;
	// 수정
	//SetDirectionAndFirstAnimation();
	Off();
}

void WaddleDee::WaddleDeeMovement(float _Delta)
{
	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate();
	}

	if (true == CheckLeftWall())
	{
		MainRenderer->ChangeAnimation("Right_Walk");
		Dir = ActorDir::Right;
	}
	else if (true == CheckRightWall())
	{
		MainRenderer->ChangeAnimation("Left_Walk");
		Dir = ActorDir::Left;
	}

	if (ActorDir::Left == Dir)
	{
		AddPos(float4::LEFT * WaddleSpeed * _Delta);
	}

	if (ActorDir::Right == Dir)
	{
		AddPos(float4::LEFT * WaddleSpeed * _Delta);
	}

	BlockedByGround();
	BlockedByWall();
}