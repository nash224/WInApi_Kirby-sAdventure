#include "ContentsCore.h"

#include "TitleLevel.h"
#include "VegetableValley11.h"
#include "VegetableValley12.h"
#include "VegetableValley13.h"
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
	GameEngineCore::CreateLevel<VegetableValley11>("VegetableValley11");
	GameEngineCore::CreateLevel<VegetableValley12>("VegetableValley12");
	GameEngineCore::CreateLevel<VegetableValley13>("VegetableValley13");
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