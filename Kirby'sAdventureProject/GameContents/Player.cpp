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
	// 비트맵 파일이 없으면 하나 만들어줘야한다.
	if (false == ResourceManager::GetInst().IsLoadTexture("Kirby.bmp"))
	{
		// 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;

		FilePath.GetCurrentPath();
		//FilePath = {Path=L"C:\\C\\WInApi_Kirby-sAdventure\\Kirby'sAdventureProject\\Kirby'sAdventure" }

		//FilePath.MoveParent();
		//FilePath = {Path=L"C:\\C\\WInApi_Kirby-sAdventure\\Kirby'sAdventureProject" }

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
	HDC WindowHDC = GameEngineWindow::MainWindow.GetHDC();
	GameEngineTexture* FindTexture = ResourceManager::GetInst().FindTexture("Kirby.bmp");
	HDC ImageDC = FindTexture->GetImageDC();

	// hdcDest 출력 대상의 핸들
	// hdcSrc 출력할 비트맵이 저장된 핸들
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
