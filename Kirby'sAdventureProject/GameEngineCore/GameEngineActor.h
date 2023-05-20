#pragma once
#include "GameEngineObject.h"

#include <GameEngineBase/GameEngineMath.h>

#include <list>
#include <string>

// 설명 : 위치가 있는 모든 객체들
//        ex) 플레이어, 에너미, UI, 오브젝트, 등등..
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineActor : public GameEngineObject
{
	friend class GameEngineLevel;
public:

	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	void ActorRelease();

	float4 GetPos() const
	{
		return Pos;
	}

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	float4 GetScale() const
	{
		return Scale;
	}

	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(EnumType _Order)
	{
		return CreateRenderer("", static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(int _Order = 0)
	{
		return CreateRenderer("", static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, EnumType _Order)
	{
		return CreateRenderer(_ImageName, static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, int _Order);
	GameEngineRenderer* CreateCollision(int _Order = 0);

protected:
	virtual void LevelStart() {}
	virtual void LevelEnd() {}

private:
	GameEngineLevel* Level = nullptr;
	float4 Pos = float4::ZERO;
	float4 Scale = float4::ZERO;

	std::list<GameEngineRenderer*> AllRenderer;
};