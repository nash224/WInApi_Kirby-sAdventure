#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"

std::string GameEngineCore::WindowTitle = "";
std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}



// C2511 : 선언을 안해서 오버로드된 멤버 함수를 찾음
void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeckCheck();

	Process = _Ptr;
	WindowTitle = _Title;

	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}



void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	// 창의 띄운다
    GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

	// 구조를 생성한다
	Process->Start();
}

void GameEngineCore::CoreUpdate()
{

}

void GameEngineCore::CoreEnd()
{

}


void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}