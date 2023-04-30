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
	// constructor desstructor
	GameEngineCore();
	~GameEngineCore();

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
			// C2664 : �Լ��� ���޵� ���� Ÿ���� ����� �ٸ� ��쳪, ���� ������ ������� �ٸ� ��
			MsgBoxAssert(Upper + "�� �̸��� ���� GameEngineLevel�� �̹� �����մϴ�.");
			return;
		}

		// C2240 : �ʱ�ȭ �� �ڽĿ��� �θ�� ��ȯ�� �� �����ϴ�.
		//		   => �ڽ� Ŭ������ ����� ���� �ʾ���
		// �ڽ��� ��ü�� ���ɽ����Ͽ� ��ü�� ������
		GameEngineLevel* NewLevel = new LevelType();

		LevelInit(NewLevel);

		AllLevel.insert(std::make_pair(Upper, NewLevel));

		//std::pair<std::map<std::string, class GameEngineLevel*>::iterator, bool> Pair
		//	= AllLevel.insert(std::make_pair(_Name, nullptr));
	}

protected:

private:
	static CoreProcess* Process;


	static std::string WindowTitle;
	static std::map<std::string, GameEngineLevel*> AllLevel;


	static void EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr);

	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();

	static void LevelInit(GameEngineLevel* _Level);
};