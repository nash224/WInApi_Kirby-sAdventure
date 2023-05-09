#include "Player.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourceManager.h>

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
		FilePath.MoveChild("Resources\\KirbyTest\\Kirby.bmp");

		// 텍스쳐를 받는다.
		ResourceManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	SetPos({ 200, 300 });
	SetScale({ 100, 100 });
}

void Player::Update(float _Delta)
{
	AddPos({ 100.0f * _Delta , 0.0f });
}

void Player::Render() 
{
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourceManager::GetInst().FindTexture("Kirby.bmp");
	BackBuffer->TransCopy(FindTexture, GetPos(), { 100, 100 }, {0,0}, FindTexture->GetScale());
}

void Player::Release() 
{

}
