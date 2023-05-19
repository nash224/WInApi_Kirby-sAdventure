#include "EndingLevel.h"

#include "Player.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{

}


void EndingLevel::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("MrShineMrBright.bmp", "Resources\\KirbyTest\\");

	LevelPlayer = GameEngineLevel::CreateActor<Player>();
}

void EndingLevel::Update(float _Delta)
{
	if (20.0f <= GetLiveTime())
	{
		GameEngineWindow::MainWindow.WIndowOff();
	}
}

void EndingLevel::Render()
{

}

void EndingLevel::Release()
{

}

void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Player::GetMainPlayer();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}


void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel) { }