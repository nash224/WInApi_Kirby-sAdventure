#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}


void Player::IdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('W'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
	}
}

void Player::RunUpdate(float _Delta)
{
	DirCheck();

	float Speed = 600.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		MovePos = { 0.0f, -Speed * _Delta };
	}
	if (true == GameEngineInput::IsPress('S'))
	{
		MovePos = { 0.0f, Speed * _Delta };
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		//Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
		//NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
		//NewRazer->SetDir(float4::RIGHT);
		//NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
		//NewRazer->SetSpeed(300.0f);
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);
}