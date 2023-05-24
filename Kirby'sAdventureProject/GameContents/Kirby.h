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
	AccelerateDown,
	Bounce,
	Landing,
	LowerPosture,
	LowerAttack,
	HittheWall,
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
	void AccelerateDownStart();
	void BounceStart();
	void LandingStart();
	void LowerPostureStart();
	void LowerAttackStart();
	void HittheWallStart();


	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void TurnUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void AerialMotionUpdate(float _Delta);
	void FallUpdate(float _Delta);
	void AccelerateDownUpdate(float _Delta);
	void BounceUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void LowerPostureUpdate(float _Delta);
	void LowerAttackUpdate(float _Delta);
	void HittheWallUpdate(float _Delta);


	void DirCheck();
	void MoveUpdate(float _Delta);

	float4 GetKirbyScale();




	void ChangeState(KirbyState State);
	void ChangeAnimationState(const std::string& _StateName);

private:
	KirbyBodyState BodyState = KirbyBodyState::Max;
	KirbyState State = KirbyState::Max;
	std::string CurState = "";

	bool IsAbleJump = false;
	bool IsChangeState = true;
	bool IsBounce = false;
	

	float CurrentSpeed = 0.0f;
	float MaxSpeed = 350.0f;
	float CurrentJumpPower = 0.0f;
	float StateTime = 0.0f;

	void Start() override;
	void Update(float _Delta) override;

	void LevelStart() override;
};