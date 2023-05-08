#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>

// ���� : ��ġ�� �ִ� ��� ��ü��
//        ex) �÷��̾�, ���ʹ�, UI, ������Ʈ, ���..
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

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	float4 GetPos() const
	{
		return Pos;
	}


	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	float4 GetScale() const
	{
		return Scale;
	}

protected:

private:
	float4 Pos = float4::Zero;
	float4 Scale = float4::Zero; // ������� ��ġ�� �ʿ��ϴ� ��ü���� scale�� �ʿ� ���� ���� �ִ�.
};