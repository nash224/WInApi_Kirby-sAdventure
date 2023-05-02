#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"

std::string GameEngineCore::WindowTitle = "";
std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;

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
	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	// 만약 CurLevel의 타입이 부모 클래스 타입이라면 호출 시 부모 클래스의 Update함수()가 호출된다
	// 그러나 CurLevel이 자식 클래스 타입의 객체를 가리키고 있다면 자식클래스에서 오버라이드된 함수로 대체된다.
	CurLevel->Update();
	// 다른 클래스임에도 불구하고 GameEngineLevel의 함수를 사용할 수 있는 이유
	// => GameEngineLevel에서 프랜드를 선언해 사용할 수 있게 해줌
	CurLevel->ActorUpdate();
	CurLevel->Render();
	CurLevel->ActorRender();
}

void GameEngineCore::CoreEnd()
{
	Process->Release();

	if (nullptr != Process)
	{
		delete Process;
		Process = nullptr;
	}

	for (std::pair<std::string, GameEngineLevel*> _Ptr : AllLevel)
	{
		if (nullptr != _Ptr.second)
		{
			delete _Ptr.second;
			_Ptr.second = nullptr;
		}
	}
}


void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}