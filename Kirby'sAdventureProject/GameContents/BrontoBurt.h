#pragma once
#include "AerialEnemies.h"

#define BRONTORECOGNITIONRANGE 200.0f

#define BRONTORISEDISTANCE 130.0f
#define BRONTORISETIME 0.4f

#define BRONTOFLYSPEED 300.0f
#define BRONTOFLYSPEEDACCELERATIONTIME 0.3f
#define BRONTOFLYSPEEDLIMIT 300.0f

#define BRONTOWAVEFLIGHTSPEED 120.0f
#define BRONTOWAVEFLIGHTCHANGEHEIGHT 80.0f

#define BRONTOFLYPOWER 300.0f

enum class BrontoState
{
	Idle,
	Rise,
	Fly,
	WaveFlightRise,
	WaveFlightFall,
	BeInhaled,
	Max,
};

// 설명 :
class BrontoBurt : public AerialEnemies
{
public:
	// constrcuter destructer
	BrontoBurt();
	~BrontoBurt();

	// delete Function
	BrontoBurt(const BrontoBurt& _Other) = delete;
	BrontoBurt(BrontoBurt&& _Other) noexcept = delete;
	BrontoBurt& operator=(const BrontoBurt& _Other) = delete;
	BrontoBurt& operator=(BrontoBurt&& _Other) noexcept = delete;

	void init(const std::string& _FileName, BrontoState _State, const float4& _Pos);

protected:
	BrontoState State = BrontoState::Max;
	BrontoState RespawnState = BrontoState::Max;

	// 업데이트 및 리스폰
	void StateUpdate(float _Delta) override;
	void ChangeState(BrontoState _State);
	void ChangeRespawnState() override;


	// 상태패턴
	void IdleStart();
	void RiseStart();
	void FlyStart();
	void WaveFlightRiseStart();
	void WaveFlightFallStart();

	void IdleUpdate(float _Delta);
	void RiseUpdate(float _Delta);
	void FlyUpdate(float _Delta);
	void WaveFlightRiseUpdate(float _Delta);
	void WaveFlightFallUpdate(float _Delta);

	void EnemyCollisionCheck();


private:
	bool IsGoForward = false;
	bool StopRise = false;
	bool IsChangeGravityReverse = false;
	int WaveFlightCountBasedFall = 0;
	float RiseDistance = 0.0f;
	float ParabolicRiseStartDistance = 0.0f;


	void Start() override;
	void Update(float _Delta) override;

};

