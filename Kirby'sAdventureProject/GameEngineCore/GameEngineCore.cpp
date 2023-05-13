#include "GameEngineCore.h"
#include "GameEngineLevel.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameEngineCamera.h"

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
    GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);
	GameEngineInput::InputInit();

	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel);
		}

		NextLevel->LevelStart(NextLevel);

		CurLevel = NextLevel;
		NextLevel = nullptr;
		GameEngineTime::MainTimer.Reset();
	}

	GameEngineTime::MainTimer.Update();
	float Delta = GameEngineTime::MainTimer.GetDeltaTime();

	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(Delta);
	}
	else
	{
		GameEngineInput::Reset();
	}

	CurLevel->Update(Delta);
	CurLevel->ActorUpdate(Delta);
	GameEngineWindow::MainWindow.ClearBackBuffer();
	CurLevel->ActorRender();
	CurLevel->Render();
	GameEngineWindow::MainWindow.DoubleBuffering();

	CurLevel->ActorRelease();
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
