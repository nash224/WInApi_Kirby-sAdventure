#pragma once
#include "PowerEnemies.h"

#define SWORDKNIGHTSPEED 60.0f

#define SwordKnightRANGEDETECTION 300.0f

#define SWORDKNIGHTRAISESWORDTIME 0.2f
#define SWORDKNIGHTSLASHINSTANTANEOUSSPEED 300.0f

#define SWORDKNIGHTUNDERHANDTIME SWORDKNIGHTRAISESWORDTIME
#define SWORDKNIGHTUNDERHANDINSTANTANEOUSSPEED 200.0f


#define DEACELECTIONSPEED 800.0f




enum class SwordKnightState
{
	PendulumStride,
	RaiseSword,
	Slash,
	Underhand,
	ReversingSlash,
	Max,
};

// Ό³Έν :
class SwordKnight : public PowerEnemies
{
public:
	// constrcuter destructer
	SwordKnight();
	~SwordKnight();

	// delete Function
	SwordKnight(const SwordKnight& _Other) = delete;
	SwordKnight(SwordKnight&& _Other) noexcept = delete;
	SwordKnight& operator=(const SwordKnight& _Other) = delete;
	SwordKnight& operator=(SwordKnight&& _Other) noexcept = delete;

	void init(const std::string& _FileName, SwordKnightState _State, const float4& _Pos);

protected:
	SwordKnightState State = SwordKnightState::Max;
	SwordKnightState RespawnState = SwordKnightState::Max;

	bool IsRollingSpeedZero = false;
	float RollingSpeedZeroTime = 0.0f;
	int BounceCount = 0;

	void StateUpdate(float _Delta) override;
	void ChangeState(SwordKnightState _State);
	void ChangeRespawnState() override;

	void PendulumStrideStart();
	void RaiseSwordStart();
	void SlashStart();
	void UnderhandStart();
	void ReversingSlashStart();

	void PendulumStrideUpdate(float _Delta);
	void RaiseSwordUpdate(float _Delta);
	void SlashUpdate(float _Delta);
	void UnderhandUpdate(float _Delta);
	void ReversingSlashUpdate(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

};

