#pragma once
#include "PowerEnemies.h"

#define TOGEZOSPEED 60.0f

#define TOGEZORANGEDETECTION 300.0f


#define TogezoWALKINGCHANGESTATETIME 4.0f
#define TogezoWALKINGCHANGEANIMATIONTIME 0.3f

#define TOGEZOJUMPDISTANCE 400.0f
#define TOGEZOJUMPTIME 0.5f

#define TOGEZOROLLINGSPEED 280.0f
#define TOGEZOROLLINGCHANGEFRAMETIME 0.05f
#define TOGEZOROLLINGCOOLDOWN 4.0f
#define TOGEZOROLLINGTIME 6.0f
#define TOGEZOCLIFFSTOPTIME 1.0f


enum class TogezoState
{
	Walk,
	Bounce,
	Roll,
	Max,
};

// Ό³Έν :
class Togezo : public PowerEnemies
{
public:
	// constrcuter destructer
	Togezo();
	~Togezo();

	// delete Function
	Togezo(const Togezo& _Other) = delete;
	Togezo(Togezo&& _Other) noexcept = delete;
	Togezo& operator=(const Togezo& _Other) = delete;
	Togezo& operator=(Togezo&& _Other) noexcept = delete;

	void init(const std::string& _FileName, TogezoState _State, const float4& _Pos);

protected:
	TogezoState State = TogezoState::Max;
	TogezoState RespawnState = TogezoState::Max;
	GameEngineCollision* AbilityCollision = nullptr;

	bool IsRollingSpeedZero = false;
	float RollingSpeedZeroTime = 0.0f;
	int BounceCount = 0;

	void StateUpdate(float _Delta) override;
	void ChangeState(TogezoState _State);
	void ChangeRespawnState() override;

	void WalkStart();
	void BounceStart();
	void RollStart();

	void WalkUpdate(float _Delta);
	void BounceUpdate(float _Delta);
	void RollUpdate(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

};

