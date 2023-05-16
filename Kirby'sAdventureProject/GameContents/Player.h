#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Player : public GameEngineActor
{
public:
	// constructor desstructor
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	float4 GetMovePos() const
	{
		return MovePos;
	}

	void SetMovePos(const float4& _MovePos)
	{
		MovePos = _MovePos;
	}

	GameEngineRenderer* MainRenderer = nullptr;

protected:

private:
	float4 MovePos = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;

};