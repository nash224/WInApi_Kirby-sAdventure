#pragma once
#include "GameEngineObject.h"

#include <GameEngineBase/GameEngineMath.h>

#include <list>
#include <string>

// ���� : ��ġ�� �ִ� ��� ��ü��
//        ex) �÷��̾�, ���ʹ�, UI, ������Ʈ, ���..
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineActor : public GameEngineObject
{
public:
	friend class GameEngineLevel;

	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

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

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

protected:

private:
	GameEngineLevel* Level;
	float4 Pos = float4::Zero;
	float4 Scale = float4::Zero; // ������� ��ġ�� �ʿ��ϴ� ��ü���� scale�� �ʿ� ���� ���� �ִ�.

	std::list<GameEngineRenderer*> AllRenderer;


};