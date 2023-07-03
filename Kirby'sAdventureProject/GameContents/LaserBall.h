#pragma once
#include "PowerEnemies.h"

#define LASERBALLZEROTOTOPSPEEDTIME 1.0f
#define LAZERBALLLIMITSPEED 200.0f
#define LASERBALLACELECTIONSPEED LAZERBALLLIMITSPEED / LASERBALLZEROTOTOPSPEEDTIME

#define LASERBALLSHOOTDETECTMINRANGE 200.0f
#define LASERBALLRUNAWAYDETECTRANGE LASERBALLSHOOTDETECTMINRANGE + 100.0f
#define LASERBALLSHOOTDETECTMAXRANGE LASERBALLSHOOTDETECTMINRANGE + 150.0f
#define LASERBALLSHOOTVERTICALDETECTRANGE 30.0f
#define LASERBALLVERTICALDETECTRANGE LASERBALLSHOOTVERTICALDETECTRANGE + 30.0f

#define LASERBALLSHOOTCHANGEFRAMETIME 0.06f

#define LASERBALLRUNAWAYSPEED 100.0f





enum class LaserBallState
{
	Fly,
	Charging,
	Shoot,
	RunAway,
	BeInhaled,
	Hitted,
	Max,
};

// 설명 : 구체이고 날아다니면서 레이저를 쏘는 귀찮은 파워 몬스터입니다.
class LaserBall : public PowerEnemies
{
public:
	// constrcuter destructer
	LaserBall();
	~LaserBall();

	// delete Function
	LaserBall(const LaserBall& _Other) = delete;
	LaserBall(LaserBall&& _Other) noexcept = delete;
	LaserBall& operator=(const LaserBall& _Other) = delete;
	LaserBall& operator=(LaserBall&& _Other) noexcept = delete;

	void init(const std::string& _FileName, LaserBallState _State, const float4& _Pos);


	// 레벨 상속
private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



	// Enemy 상속
private:
	void StateUpdate(float _Delta) override;
	void ChangeRespawnState() override;



	// this
private:
	// 상태패턴
	LaserBallState State = LaserBallState::Max;
	LaserBallState RespawnState = LaserBallState::Max;

	void ChangeState(LaserBallState _State);


	void FlyStart();
	void ChargingStart();
	void ShootStart();
	void RunAwayStart();

	void FlyUpdate(float _Delta);
	void ChargingUpdate(float _Delta);
	void ShootUpdate(float _Delta);
	void RunAwayUpdate(float _Delta);



	// Shoot 패턴
	int ChargingCount = -1;
	int ShootCount = 0;


	// 충돌
	void EnemyCollisionCheck();




	// 디버깅
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
	void ThisDebugTriggerRender(HDC _dc);

};


