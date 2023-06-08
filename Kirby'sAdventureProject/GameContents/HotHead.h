#pragma once
#include "PowerEnemies.h"

#define HotHeadSPEED 120.0f


#define HotHeadWALKINGCHANGESTATETIME 3.0f
#define HotHeadWALKINGCHANGEANIMATIONTIME 0.2f
#define HotHeadJUMPCHANGEANIMATIONTIME 0.1f


#define HotHeadFireballChargingtime 0.5f
#define HotHeadFlameBreathingtime 0.8f 

#define HotHeadFlameBreathChargingtime 0.8f
#define HotHeadFlameBreathingtime 4.0f 

#define HotHeadWOBBLETIME 0.08f



enum class HotHeadState
{
	Walk,
	FireBallCharging,
	FireBall,
	FlameBreathCharging,
	FlameBreath,
	Max,
};

// Ό³Έν :
class HotHead : public PowerEnemies
{
public:
	// constrcuter destructer
	HotHead();
	~HotHead();

	// delete Function
	HotHead(const HotHead& _Other) = delete;
	HotHead(HotHead&& _Other) noexcept = delete;
	HotHead& operator=(const HotHead& _Other) = delete;
	HotHead& operator=(HotHead&& _Other) noexcept = delete;

	void init(const std::string& _FileName, HotHeadState _State, const float4& _Pos);

protected:
	HotHeadState State = HotHeadState::Max;
	HotHeadState RespawnState = HotHeadState::Max;

	bool IsGravityReverse = false;
	int WobbleCount = 0;
	int EndCount = -1;
	float CurrentJumpDistance = 0.0f;

	void StateUpdate(float _Delta) override;
	void ChangeState(HotHeadState _State);
	void ChangeRespawnState() override;

	void WalkStart();
	void FireBallChargingStart();
	void FireBallStart();
	void FlameBreathChargingStart();
	void FlameBreathStart();

	void WalkUpdate(float _Delta);
	void FireBallChargingUpdate(float _Delta);
	void FireBallUpdate(float _Delta);
	void FlameBreathChargingUpdate(float _Delta);
	void FlameBreathUpdate(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

};

