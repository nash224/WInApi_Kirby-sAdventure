#include "Player.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
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
		// 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		//FilePath = {Path=L"C:\\C\\WInApi_Kirby-sAdventure\\Kirby'sAdventureProject\\Kirby'sAdventure" }

		// Resources의 폴더가 있는 위치로 이동한다.
		FilePath.MoveParentToExistsChild("Resources");

		// Kirby.bmp가 있는 폴더에 접근한다.
		FilePath.MoveChild("Resources\\KirbyTest\\");

		// 텍스쳐를 받는다.
		ResourceManager::GetInst().TextureLoad(FilePath.PlusFilePath("Kirby.bmp"));
	}

	GameEngineRenderer* KirbyRender = CreateRenderer("Kirby.bmp", RenderOrder::Play);
	KirbyRender->SetRenderScale({ 200, 200 });
	KirbyRender->SetTexture("Kirby.bmp");

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
