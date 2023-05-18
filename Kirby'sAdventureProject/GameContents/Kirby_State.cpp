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
	if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) &&
		false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
	}
}

void Player::RunUpdate(float _Delta)
{
	//DirCheck();

	// RunUpdate중에 A와 D가 프레임사이로 연속적으로 입력됐을 경우
	// 좌우 애니메이션이 전환되지 않는 버그가 있음


	float Speed = 600.0f;

	float4 MovePos = float4::ZERO;


	if (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D'))
	{
		MovePos = { 0.0f, MovePos.Y };
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D'))
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

	if (MovePos.X == 0.0f)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
	}


	AddPos(MovePos);
	//GetLevel()->GetMainCamera()->AddPos(MovePos);
}



	//Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
	//NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
	//NewRazer->SetDir(float4::RIGHT);
	//NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
	//NewRazer->SetSpeed(300.0f);