#pragma once
#include "ContentUtils.h"

enum class PlayerState
{
	Idle,
	Run,
	Max,
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};

class Player : public ContentUtils
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

	GameEngineRenderer* MainRenderer = nullptr;

	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

protected:
	static Player* MainPlayer;

	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Right;
	std::string CurState = "";


	void StateUpdate(float _Delta);
	void IdleStart();
	void RunStart();

	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void DirCheck();
	void ChangeState(PlayerState State);
	void ChangeAnimationState(const std::string& _StateName);

private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
};