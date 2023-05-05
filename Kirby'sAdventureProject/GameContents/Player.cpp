#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourceManager.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <Windows.h>
#include "Player.h"



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

		//FilePath.MoveParent();
		//FilePath = {Path=L"C:\\C\\WInApi_Kirby-sAdventure\\Kirby'sAdventureProject" }

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
	HDC WindowHDC = GameEngineWindow::MainWindow.GetHDC();
	GameEngineTexture* FindTexture = ResourceManager::GetInst().FindTexture("Kirby.bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	// hdcDest ��� ����� �ڵ�
	// hdcSrc ����� ��Ʈ���� ����� �ڵ�
	BitBlt(WindowHDC, 100, 100, 500, 500, ImageDC, 0, 0, SRCCOPY);

	//Rectangle(WindowHDC,
	//	GetPos().iX() - GetScale().ihX(),
	//	GetPos().iY() - GetScale().ihY(),
	//	GetPos().iX() + GetScale().ihX(),
	//	GetPos().iY() + GetScale().ihY()
	//);
}

void Player::Release() 
{

}
