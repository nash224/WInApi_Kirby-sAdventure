#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>

// 설명 : 위치가 있는 모든 객체들
//        ex) 플레이어, 에너미, UI, 오브젝트, 등등..
class GameEngineActor : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	void SetPos(const float4 _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4 _Pos)
	{
		Pos += _Pos;
	}

	float4 GetPos() const
	{
		return Pos;
	}


	void SetScale(const float4 _Scale)
	{
		Scale = _Scale;
	}

	float4 GetScale() const
	{
		return Scale;
	}

protected:

private:
	float4 Pos = { 0 , 0 };
	float4 Scale = { 0 , 0 }; // 상대적인 위치만 필요하는 객체들은 scale이 필요 없을 수도 있다.
};