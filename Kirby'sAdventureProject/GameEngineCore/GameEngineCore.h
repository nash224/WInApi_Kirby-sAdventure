#pragma once
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <Windows.h>
#include <string>
#include <map>
#include "GameEngineObject.h"

class CoreProcess : public GameEngineObject
{

};

class GameEngineLevel;
class GameEngineCore
{
public:
	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	template<typename CoreProcessType>
	static void EngineStart(const std::string& _Title, HINSTANCE _Inst)
	{
		EngineStart(_Title, _Inst, new CoreProcessType());
	}

	template<typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		if (AllLevel.end() != AllLevel.find(Upper))
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 이미 존재합니다.");
			return;
		}

		GameEngineLevel* NewLevel = new LevelType();

		LevelInit(NewLevel);

		AllLevel.insert(std::make_pair(Upper, NewLevel));
	}

	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);
		
		std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel.find(Upper);

		if (AllLevel.end() == FindIter)
		{
			MsgBoxAssert(_Name + "의 이름을 가진 GameEngineLevel은 존재하지 않습니다.");
			return;
		}

		NextLevel = FindIter->second;
	}

protected:

private:
	static CoreProcess* Process;

	static std::string WindowTitle;
	static std::map<std::string, GameEngineLevel*> AllLevel;

	static GameEngineLevel* NextLevel;
	static GameEngineLevel* CurLevel;


	// constructor desstructor
	GameEngineCore();
	~GameEngineCore();

	static void EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr);

	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();

	static void LevelInit(GameEngineLevel* _Level);
};