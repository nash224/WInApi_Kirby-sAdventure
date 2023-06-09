#pragma once
#include "PowerEnemies.h"

#define TogezoSPEED 60.0f

#define TogezoRANGEDETECTION 300.0f
#define TogezoFIREBALLRANGEDETECTION 100.0f


#define TogezoWALKINGCHANGESTATETIME 4.0f
#define TogezoWALKINGCHANGEANIMATIONTIME 0.3f


#define TogezoFIREBALLCHARGINGTIME 0.5f
#define TogezoFIREBALLTIME 0.8f 

#define TogezoFLAMEBREATHCHARGINGTIME 0.8f
#define TogezoFLAMEBREATHINGTIME 4.0f 

#define TogezoWOBBLETIME 0.08f



enum class TogezoState
{
	Walk,
	Jump,
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

	int WobbleCount = 0;

	void StateUpdate(float _Delta) override;
	void ChangeState(TogezoState _State);
	void ChangeRespawnState() override;

	void WalkStart();
	void JumpStart();
	void BounceStart();
	void RollStart();

	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void BounceUpdate(float _Delta);
	void RollUpdate(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

};

