#include "Kirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourceManager.h>




void Kirby::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Kirby::WalkStart()
{
	DirCheck();
	ChangeAnimationState("Walk");
}

void Kirby::RunStart()
{
	DirCheck();
	ChangeAnimationState("Run");
}

void Kirby::TurnStart()
{

	ChangeAnimationState("Turn");
}

void Kirby::JumpStart()
{
	IsAbleJump = false;
	ChangeAnimationState("Jump");
}

void Kirby::AerialMotionStart()
{
	ChangeAnimationState("AerialMotion");
}

void Kirby::FallStart()
{
	ChangeAnimationState("Fall");
}

void Kirby::LandingStart()
{
	ChangeAnimationState("Landing");
}

// =============================================//

void Kirby::IdleUpdate(float _Delta)
{
	MoveUpdate(_Delta);
	// 서있는 위치에 발판이 있는가
	if(false == GetGroundState())
	{
		Gravity(_Delta);
	}
	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);
			AddPos(float4::UP*3);
		}

		GravityReset();
	}

	if (true == (GameEngineInput::IsDown('X')))
	{
		ChangeState(KirbyState::Jump);
		return;
	}

	if (true == (GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D')) &&
		false == (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D')))
	{
		ChangeState(KirbyState::Run);
	}
}


void Kirby::WalkUpdate(float _Delta)
{

}

// RunUpdate중에 A와 D가 프레임사이로 연속적으로 입력됐을 경우
// 좌우 애니메이션이 전환되지 않는 버그가 있음
void Kirby::RunUpdate(float _Delta)
{
	if (false == GetGroundState())
	{
		Gravity(_Delta);
	}
	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP * 3);
			AddPos(float4::UP * 3);
		}

		GravityReset();
	}


	float Speed = 600.0f;
	float4 CheckPos = float4::ZERO;

	if (GameEngineInput::IsPress('A') && GameEngineInput::IsPress('D'))
	{
		//MovePos = { 0.0f, MovePos.Y };
	}
	else if (true == GameEngineInput::IsPress('A'))
	{
		CheckPos = { -18.0f , -30.0f };
		//MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		CheckPos = { 18.0f , -30.0f };
		//MovePos = { Speed * _Delta, 0.0f };
	}

	MoveUpdate(_Delta);

	if (CurrentSpeed == 0.0f)
	{
		ChangeState(KirbyState::Idle);
	}

	
	//unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
	//if (Color == RGB(255,255,255))
	//{
	//	AddPos(MovePos);
	//}
	

}


void Kirby::TurnUpdate(float _Delta)
{

}

void Kirby::JumpUpdate(float _Delta)
{

	float4 MovePos = float4::ZERO;
	float JumpPower = 600.0f;


	if (GameEngineInput::IsPress('X') && 3.0f >= GameEngineInput::GetPressTime('X'))
	{
		IsAbleJump = true;
		MovePos = { 0.0f, - JumpPower * _Delta };
	}


	AddPos(MovePos);

	if (false == GetGroundState() && false == IsAbleJump)
	{
		Gravity(_Delta);
	}

	if (true == GetGroundState() && false == IsAbleJump)
	{
		ChangeState(KirbyState::Idle);
	}


}


void Kirby::AerialMotionUpdate(float _Delta)
{

}

void Kirby::FallUpdate(float _Delta)
{

}


void Kirby::LandingUpdate(float _Delta)
{

}


// ============================================








//Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
//NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
//NewRazer->SetDir(float4::RIGHT);
//NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
//NewRazer->SetSpeed(300.0f);