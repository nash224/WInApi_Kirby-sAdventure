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



// C2511 : ������ ���ؼ� �����ε�� ��� �Լ��� ã��
void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeckCheck();

	Process = _Ptr;
	WindowTitle = _Title;

	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}



void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	// â�� ����
    GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

	// ������ �����Ѵ�
	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	CurLevel->Update();
	// �ٸ� Ŭ�����ӿ��� �ұ��ϰ� GameEngineLevel�� �Լ��� ����� �� �ִ� ����
	// => GameEngineLevel���� �����带 ������ ����� �� �ְ� ����
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