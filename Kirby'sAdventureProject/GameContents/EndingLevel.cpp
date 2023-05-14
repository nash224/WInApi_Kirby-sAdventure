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
	LevelBackGround->init("MrShineMrBright.bmp", float4{ 4 , 4 }, float4{ 248 , 176 });

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
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.GetHalf());
}

void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel) { }