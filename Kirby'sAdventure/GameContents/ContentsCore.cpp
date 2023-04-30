#include <GameEngineCore/GameEngineCore.h>
#include "ContentsCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}


void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");
}

void ContentsCore::Update()
{

}

void ContentsCore::Render()
{

}

void ContentsCore::Release()
{

}