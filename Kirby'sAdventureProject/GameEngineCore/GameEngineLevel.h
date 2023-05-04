#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include <list>
#include <map>

// ���� : ȭ�� �Ǵ� ���� ������
//        ex) Ÿ��Ʋ ���, �÷��� ���, ���� �忬
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


	// AllActors�� Ư�� ���� �׷��� �ҷ��ͼ� ���Ӱ� ���� ���� 
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		// �Ϲ����� ����ȯ�� �Ͼ�� (lvalue������ ����ȯ)
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		GroupList.push_back(NewActor);
	}

protected:

private:
	// ��, ������Ʈ, �÷��̾�, ����

	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorInit(GameEngineActor* _Actor);
	
	void ActorUpdate(float _Delta);
	void ActorRender();
};