#include "Player.h"
#include "ContentsEnum.h"
#include "Projectile.h"

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

#include <Windows.h>



Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// 비트맵 파일이 없으면 하나 만들어줘야한다.
	if (false == ResourceManager::GetInst().IsLoadTexture("Kirby.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\KirbyTest");
		ResourceManager::GetInst().TextureLoad(FilePath.PlusFilePath("Kirby.bmp"));
	}

	GameEngineRenderer* KirbyRender = CreateRenderer("Kirby.bmp", RenderOrder::Play);
	//KirbyRender->SetRenderScale({ 200, 200 });
	//KirbyRender->SetTexture("Kirby.bmp");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.GetHalf());
}

void Player::Update(float _Delta)
{
	SetSpeed(600.0f);

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		//MovePos = { -GetSpeed() * _Delta, 0.0f };
		SetDir(float4::LEFT);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		//MovePos = { GetSpeed() * _Delta, 0.0f };
		SetDir(float4::RIGHT);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		//MovePos = { 0.0f ,-GetSpeed() * _Delta };
		SetDir(float4::UP);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		//MovePos = { 0.0f , GetSpeed() * _Delta };
		SetDir(float4::DOWN);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
		NewRazer->Renderer->SetTexture("Kirby.bmp");
		NewRazer->SetDir(float4::RIGHT);
		NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
		NewRazer->SetSpeed(300.0f);
	}


	if (0 != GetAsyncKeyState('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	SetMovePos(MovePos);
	AddPos(MovePos);
	//if (GetPos().iX() >= GameEngineWindow::MainWindow.GetScale().GetHalf().iX())
	//{
	//	GetLevel()->GetMainCamera()->AddPos(float4::XValue(MovePos));
	//}

	//if (GetPos().iY() >= GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
	//{
	//	GetLevel()->GetMainCamera()->AddPos(float4::YValue(MovePos));
	//}
}

void Player::Render() 
{
	//GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	//GameEngineWindowTexture* FindTexture = ResourceManager::GetInst().FindTexture("Kirby.bmp");
	//BackBuffer->TransCopy(FindTexture, GetPos(), { 100, 100 }, {0,0}, FindTexture->GetScale());
}

void Player::Release() 
{

}
