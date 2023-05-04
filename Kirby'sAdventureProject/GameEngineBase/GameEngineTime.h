#pragma once
#include <Windows.h>

// 설명 :
class GameEngineTime
{
public:
	static GameEngineTime MainTimer;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	float GetDeltaTime() const
	{
		return FloatDelta;
	}

	void Reset();

	void Update();

protected:

private:
	// LARGE_INTEGER 타입은 초기화 할때,  = {}로 초기화를 하는 이유
	// =>
	LARGE_INTEGER Count = { 0 };
	LARGE_INTEGER Cur = { 0 };
	LARGE_INTEGER Prev = { 0 };
	__int64 Tick = 0;
	double DoubleDelta;
	float FloatDelta = 0.0f;
};
