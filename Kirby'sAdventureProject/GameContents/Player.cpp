#include "Player.h"
#include "ContentsEnum.h"
#include "Projectile.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourceManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

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
		FilePath.MoveChild("Resources\\KirbyTest\\");
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
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (0 != GetAsyncKeyState('A'))
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('D'))
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (0 != GetAsyncKeyState('W'))
	{
		MovePos = { 0.0f ,-Speed * _Delta };
	}

	if (0 != GetAsyncKeyState('S'))
	{
		MovePos = { 0.0f , Speed * _Delta };
	}

	if (0 != GetAsyncKeyState('F'))
	{
		Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
		NewRazer->Renderer->SetTexture("Kirby.bmp");
		NewRazer->SetDir(float4::RIGHT);
		NewRazer->SetPos(GetPos());
		NewRazer->SetSpeed(300.0f);
	}

	AddPos(MovePos);
	GetLevel()->GetMainCamera()->AddPos(MovePos);
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
