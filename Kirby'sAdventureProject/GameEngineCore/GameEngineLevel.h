#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include <list>
#include <map>

// 설명 : 화면 또는 씬을 포현함
//        ex) 타이틀 장면, 플레이 장면, 엔딩 장연
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


	// AllActors의 특정 액터 그룹을 불러와서 새롭게 만들 액터 
	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		// 암묵적인 형변환이 일어났음 (lvalue참조로 형변환)
		std::list<GameEngineActor*>& GroupList = AllActors[_Order];
		GameEngineActor* NewActor = new ActorType();
		ActorInit(NewActor);
		GroupList.push_back(NewActor);
	}

protected:

private:
	// 맵, 오브젝트, 플레이어, 몬스터

	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorInit(GameEngineActor* _Actor);
	
	void ActorUpdate(float _Delta);
	void ActorRender();
};