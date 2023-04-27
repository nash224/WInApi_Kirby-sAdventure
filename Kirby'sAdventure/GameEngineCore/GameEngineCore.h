#pragma once
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <Windows.h>
#include <string>
#include <map>

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

	static void EngineStart(const std::string& _Title, HINSTANCE _Inst);

	template<typename LevelType>
	static void Create(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		if (AllLevel.end() != AllLevel.find(Upper))
		{
			// C2664 : �Լ��� ���޵� ���� Ÿ���� ����� �ٸ� ��쳪, ���� ������ ������� �ٸ� ��
			MsgBoxAssert(Upper + "�� �̸��� ���� GameEngineLevel�� �̹� �����մϴ�.");
			return;
		}

		GameEngineLevel* NewLevel = new LevelType();

		AllLevel.insert(std::make_pair(Upper, NewLevel));

		//std::pair<std::map<std::string, class GameEngineLevel*>::iterator, bool> Pair
		//	= AllLevel.insert(std::make_pair(_Name, nullptr));
	}

protected:

private:
	static std::string Title;
	static std::map<std::string, GameEngineLevel*> AllLevel;


	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();
};