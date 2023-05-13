#pragma once
#include <Windows.h>

// ���� :
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

	void Update();
	void Reset();

	float GetDeltaTime() const
	{
		return FloatDelta;
	}

protected:

private:
	LARGE_INTEGER Count = { 0 };
	LARGE_INTEGER Cur = { 0 };
	LARGE_INTEGER Prev = { 0 };
	__int64 Tick = 0;
	float FloatDelta = 0.0f;
	double DoubleDelta = 0.0;
};
