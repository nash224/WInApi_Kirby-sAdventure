#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
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
	float TIme = GameEngineTime::MainTimer.GetDeltaTime();

	AddPos({ 0.0001f , 0.0f });
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
