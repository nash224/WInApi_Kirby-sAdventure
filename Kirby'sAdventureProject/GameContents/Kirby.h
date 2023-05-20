#pragma once
#include "ContentUtils.h"

enum class KirbyState
{
	Idle,
	Run,
	Max,
};

enum class KirbyDir
{
	Right,
	Left,
	Max,
};

class Kirby : public ContentUtils
{
public:
	// constructor desstructor
	Kirby();
	~Kirby();

	// delete Function
	Kirby(const Kirby& _Other) = delete;
	Kirby(Kirby&& _Other) noexcept = delete;
	Kirby& operator=(const Kirby& _Other) = delete;
	Kirby& operator=(Kirby&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	static Kirby* GetMainKirby()
	{
		return MainKirby;
	}

protected:
	static Kirby* MainKirby;

	KirbyState State = KirbyState::Max;
	KirbyDir Dir = KirbyDir::Right;
	std::string CurState = "";


	void StateUpdate(float _Delta);
	void IdleStart();
	void RunStart();

	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);

	void DirCheck();
	void ChangeState(KirbyState State);
	void ChangeAnimationState(const std::string& _StateName);

private:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart() override;

};