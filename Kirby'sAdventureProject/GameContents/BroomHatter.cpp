#include "BroomHatter.h"
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

BroomHatter::BroomHatter() 
{
}

BroomHatter::~BroomHatter() 
{
}


void BroomHatter::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);

	ResourcesManager::GetInst().SpriteFileLoad("Left_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);
	ResourcesManager::GetInst().SpriteFileLoad("Right_NormalEnemy.bmp", "Resources\\Unit\\Grunt", 4, 5);

	MainRenderer->CreateAnimation("Left_Idle", "Left_NormalEnemy.bmp", 2, 3, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Idle", "Right_NormalEnemy.bmp", 2, 3, 0.5f, true);

	MainRenderer->CreateAnimation("Left_Sweep", "Left_NormalEnemy.bmp", 2, 3, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Sweep", "Right_NormalEnemy.bmp", 2, 3, 0.5f, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;
	ChangeState(NormalState::Idle);

	BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void BroomHatter::init(const std::string _FileName, const float4& _Pos)
{
	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	SetPos(RespawnLocation);
	SetDirectionAndFirstAnimation();
}


void BroomHatter::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);

	CheckOverScreen();
}



void BroomHatter::IdleStart() 
{
	
}

void BroomHatter::IdleUpdate(float _Delta) 
{

}


void BroomHatter::SweepStart() 
{

}

void BroomHatter::SweepUpdate(float _Delta) 
{

}