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
	// ��Ʈ�� ������ ������ �ϳ� ���������Ѵ�.
	if (false == ResourceManager::GetInst().IsLoadTexture("Kirby.bmp"))
	{
		// ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		//FilePath = {Path=L"C:\\C\\WInApi_Kirby-sAdventure\\Kirby'sAdventureProject\\Kirby'sAdventure" }

		// Resources�� ������ �ִ� ��ġ�� �̵��Ѵ�.
		FilePath.MoveParentToExistsChild("Resources");

		// Kirby.bmp�� �ִ� ������ �����Ѵ�.
		FilePath.MoveChild("Resources\\KirbyTest\\Kirby.bmp");

		// �ؽ��ĸ� �޴´�.
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
