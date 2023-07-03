#pragma once
#include "PowerEnemies.h"

#define HOTHEADSPEED 60.0f

#define HOTHEADRANGEDETECTION 400.0f
#define HOTHEADFIREBALLRANGEDETECTION 150.0f


#define HOTHEADWALKINGCHANGESTATETIME 4.0f
#define HOTHEADWALKINGCHANGEANIMATIONTIME 0.3f


#define HOTHEADFIREBALLCHARGINGTIME 0.5f
#define HOTHEADFIREBALLTIME 0.8f 

#define HOTHEADFLAMEBREATHCHARGINGTIME 0.8f
#define HOTHEADFLAMEBREATHINGTIME 4.0f 

#define HOTHEADWOBBLETIME 0.08f



enum class HotHeadState
{
	Walk,
	FireBallCharging,
	FireBall,
	FlameBreathCharging,
	FlameBreath,
	BeInhaled,
	Hitted,
	Max,
};

// 설명 : 머리가 불꽃인 몬스터입니다. 
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



	// Level 상속
private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


protected:
	// 상태패턴 함수
	HotHeadState State = HotHeadState::Max;
	HotHeadState RespawnState = HotHeadState::Max;

	int WobbleCount = 0;


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

	void EnemyCollisionCheck();

	const float SemicircleAngle = 180.0f;
	const float FireBall_HighAngle = 18.0f;
	float DegToKirby = 0.0f;





};

