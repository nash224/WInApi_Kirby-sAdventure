#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	SetPos({ 200, 300 });
	SetScale({ 100, 100 });
}

void Player::Update()
{
	AddPos({ 0.0f , 1.0f });
}

void Player::Render() 
{
	HDC WindowHDC = GameEngineWindow::MainWindow.GetHDC();

	Rectangle(WindowHDC,
		GetPos().iX() - GetScale().ihX(),
		GetPos().iY() - GetScale().ihY(),
		GetPos().iX() + GetScale().ihX(),
		GetPos().iY() + GetScale().ihY()
	);

}

void Player::Release() 
{

}
