#pragma once
#include "ActorUtils.h"

#define ACCELERATIONSPEED 2.0f
#define MAXWALKSPEED 300.0f

enum class KirbyBodyState
{
	Little,
	Fat,
	Max,
};

enum class KirbyState
{
	Idle,
	Walk,
	Run,
	Turn,
	Jump,
	AerialMotion,
	Fall,
	Landing,
	LowerPosture,
	LowerAttack,
	Max,
};

enum class KirbyDir
{
	Right,
	Left,
	Max,
};

class Kirby : public ActorUtils
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



	void StateUpdate(float _Delta);
	void IdleStart();
	void WalkStart();
	void RunStart();
	void TurnStart();
	void JumpStart();
	void AerialMotionStart();
	void FallStart();
	void LandingStart();
	void LowerPostureStart();
	void LowerAttackStart();

	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void TurnUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void AerialMotionUpdate(float _Delta);
	void FallUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void LowerPostureUpdate(float _Delta);
	void LowerAttackUpdate(float _Delta);

	void DirCheck();
	void MoveUpdate(float _Delta);
	void GrivityUpdate(float _Delta);

	float4 GetKirbyScale();




	void ChangeState(KirbyState State);
	void ChangeAnimationState(const std::string& _StateName);

private:
	KirbyBodyState BodyState = KirbyBodyState::Max;
	KirbyState State = KirbyState::Max;
	std::string CurState = "";

	bool IsAbleJump = false;
	bool IsChangeState = true;
	

	float CurrentSpeed = 0.0f;
	float CurrentFallSpeed = 0.0f;
	float CurrentJumpPower = 0.0f;
	float FallTime = 0.0f;

	void Start() override;
	void Update(float _Delta) override;

	void LevelStart() override;
};