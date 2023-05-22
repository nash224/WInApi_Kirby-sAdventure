#include "Kirby.h"
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
#include <GameEngineCore/ResourceManager.h>

#include "Grunt.h"
#include "Projectile.h"

#include <Windows.h>


Kirby* Kirby::MainKirby = nullptr;


Kirby::Kirby()
{
}

Kirby::~Kirby()
{
}

void Kirby::Start()
{
	// 비트맵 파일이 없으면 하나 만들어줘야한다.
	{
		ResourceManager::GetInst().LoadSpriteFile("DebugPixel.bmp", "Resources\\Debug", 10, 10);
		ResourceManager::GetInst().LoadSpriteFile("SpitStar_1x4_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 4, 1);
	}

	ResourceManager::GetInst().LoadSpriteFile("Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	ResourceManager::GetInst().LoadSpriteFile("Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	MainRenderer = CreateRenderer(RenderOrder::Play);

	{
		GameEngineRenderer* DebugRendererBottomCenterPos = nullptr;
		DebugRendererBottomCenterPos = CreateRenderer(RenderOrder::HitEffect);
		DebugRendererBottomCenterPos->SetTexture("DebugPixel.bmp");
		DebugRendererBottomCenterPos->SetRenderPos(GetPos());

		GameEngineRenderer* DebugRendererBottomLeftPos = nullptr;
		DebugRendererBottomLeftPos = CreateRenderer(RenderOrder::HitEffect);
		DebugRendererBottomLeftPos->SetTexture("DebugPixel.bmp");
		DebugRendererBottomLeftPos->SetRenderPos(GetPos() + float4{ -21.0f, 0.0f });

		GameEngineRenderer* DebugRendererBottomRightPos = nullptr;
		DebugRendererBottomRightPos = CreateRenderer(RenderOrder::HitEffect);
		DebugRendererBottomRightPos->SetTexture("DebugPixel.bmp");
		DebugRendererBottomRightPos->SetRenderPos(GetPos());
		DebugRendererBottomRightPos->SetRenderPos(GetPos() + float4{ 21.0f, 0.0f });
	}

	{
		MainRenderer->CreateAnimation("KirbyExhaleStartAttack", "SpitStar_1x4_16x16.bmp", 0, 3, 0.2f, true);
	} 

	MainRenderer->CreateAnimation("Left_Idle", "Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Idle", "RIght_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Left_Run", "Left_Kirby.bmp", 2, 5, 0.15f, true);
	MainRenderer->CreateAnimation("Right_Run", "RIght_Kirby.bmp", 2, 5, 0.15f, true);

	MainRenderer->CreateAnimation("Left_Jump", "Left_Kirby.bmp", 9, 14, 0.05f, false);
	MainRenderer->CreateAnimation("Right_Jump", "Right_Kirby.bmp", 9, 14, 0.05f, false);

	MainRenderer->CreateAnimation("Right_Fall", "Right_Kirby.bmp", 14, 14, 0.05f, false);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	MainRenderer->FindAnimation("Left_Idle")->Inters = { 0.2f, 2.5f };
	MainRenderer->FindAnimation("Right_Idle")->Inters = { 0.2f, 2.5f };



	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.Half());

	ChangeState(KirbyState::Idle);
	Dir = KirbyDir::Right;
	BodyState = KirbyBodyState::Basic;


	BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
	BodyCollision->SetCollisionScale(GetKirbyScale());
}

void Kirby::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('L'))
	{
		Grunt::AllMonsterDeath();
	}

	StateUpdate(_Delta);

	CameraFocus();
}

void Kirby::StateUpdate(float _Delta)
{
	GroundCheck(GetKirbyScale().X);

	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::Run:
		return RunUpdate(_Delta);
	case KirbyState::Jump:
		return JumpUpdate(_Delta);
	case KirbyState::AerialMotion:
		return AerialMotionUpdate(_Delta);
	case KirbyState::Fall:
		return FallUpdate(_Delta);
	default:
		break;
	}
}

void Kirby::ChangeState(KirbyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case KirbyState::Idle:
			IdleStart();
			break;
		case KirbyState::Run:
			RunStart();
			break;
		case KirbyState::Jump:
			JumpStart();
			break;
		case KirbyState::AerialMotion:
			AerialMotionStart();
			break;
		case KirbyState::Fall:
			FallStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Kirby::DirCheck()
{
	KirbyDir CheckDir = KirbyDir::Max;

	if (true == GameEngineInput::IsPress('A') &&
		true == GameEngineInput::IsPress('D'))
	{
		return;
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		CheckDir = KirbyDir::Left;
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		CheckDir = KirbyDir::Right;
	}


	if (CheckDir != KirbyDir::Max)
	{
		Dir = CheckDir;
	}
}


void Kirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "";

	switch (Dir)
	{
	case KirbyDir::Right:
		AnimationName = "Right_";
		break;
	case KirbyDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}


// 발끝 중앙 기준
float4 Kirby::GetKirbyScale()
{
	if (BodyState == KirbyBodyState::Basic)
	{
		return float4{ 24.0f, 48.0f };
	}

	if (BodyState == KirbyBodyState::Fat)
	{
		return float4{ 33.0f, 63.0f };
	}

	return float4{ 0.0f, 0.0f };
}

void Kirby::LevelStart()
{
	MainKirby = this;
}
