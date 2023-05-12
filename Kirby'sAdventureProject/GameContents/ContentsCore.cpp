#include "ContentsCore.h"

#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "PauseLevel.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>


ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}


void ContentsCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 768, 720});

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");
	GameEngineCore::CreateLevel<PauseLevel>("PauseLevel");

	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Render()
{

}

void ContentsCore::Release()
{

}