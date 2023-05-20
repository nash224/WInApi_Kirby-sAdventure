#include "Kirby.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourceManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

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
		ResourceManager::GetInst().LoadSpriteFile("SpitStar_1x4_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 4, 1);
	}

	ResourceManager::GetInst().LoadSpriteFile("Left_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);
	ResourceManager::GetInst().LoadSpriteFile("Right_Kirby.bmp", "Resources\\Unit\\Kirby", 10, 10);

	MainRenderer = CreateRenderer(RenderOrder::Play);

	{
		MainRenderer->CreateAnimation("KirbyExhaleStartAttack", "SpitStar_1x4_16x16.bmp", 0, 3, 0.2f, true);
	}

	MainRenderer->CreateAnimation("Left_Idle", "Left_Kirby.bmp", 0, 1, 0.5f, true);
	MainRenderer->CreateAnimation("Right_Idle", "RIght_Kirby.bmp", 0, 1, 0.5f, true);

	MainRenderer->CreateAnimation("Left_Run", "Left_Kirby.bmp", 2, 5, 0.15f, true);
	MainRenderer->CreateAnimation("Right_Run", "RIght_Kirby.bmp", 2, 5, 0.15f, true);

	MainRenderer->SetRenderScaleToTexture();
	MainRenderer->SetScaleRatio(3.0f);

	MainRenderer->FindAnimation("Left_Idle")->Inters = { 0.2f, 2.5f };
	MainRenderer->FindAnimation("Right_Idle")->Inters = { 0.2f, 2.5f };


	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.GetHalf());

	ChangeState(KirbyState::Idle);
	Dir = KirbyDir::Right;
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
	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::Run:
		return RunUpdate(_Delta);
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

void Kirby::LevelStart()
{
	MainKirby = this;
}
