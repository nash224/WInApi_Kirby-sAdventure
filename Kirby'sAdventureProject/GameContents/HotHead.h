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

// ���� : �Ӹ��� �Ҳ��� �����Դϴ�. 
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

private:
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// Enemy ���
	void ChangeRespawnState() override;



	// this
	// FSM
	HotHeadState State = HotHeadState::Max;
	HotHeadState RespawnState = HotHeadState::Max;


	void StateUpdate(float _Delta);
	void ChangeState(HotHeadState _State);






	void WalkStart();
	void WalkUpdate(float _Delta);

	void FireBallChargingStart();
	void FireBallChargingUpdate(float _Delta);

	void FireBallStart();
	void FireBallUpdate(float _Delta);

	int WobbleCount = 0;
	const float FireBall_HighAngle = 18.0f;
	const float SemicircleAngle = 180.0f;


	void FlameBreathChargingStart();
	void FlameBreathChargingUpdate(float _Delta);

	void FlameBreathStart();
	void FlameBreathUpdate(float _Delta);




	// �浹
	void EnemyCollisionCheck();



	// ����� 
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
	void ThisDebugTriggerRender(HDC _dc);

};

