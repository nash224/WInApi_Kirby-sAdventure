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
	Hitted,
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

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// Enmey 상속
	void ChangeRespawnState() override;


	// FSM
	BrontoState State = BrontoState::Max;
	BrontoState RespawnState = BrontoState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(BrontoState _State);

	bool IsFlyVertically = false;


	// 상태
	void IdleStart();
	void IdleUpdate(float _Delta);


	void RiseStart();
	void RiseUpdate(float _Delta);

	bool StopRise = false;
	float RiseDistance = 0.0f;


	void FlyStart();
	void FlyUpdate(float _Delta);

	bool IsGoForward = false;


	void WaveFlightRiseStart();
	void WaveFlightRiseUpdate(float _Delta);

	bool IsChangeGravityReverse = false;
	int WaveFlightCountBasedFall = 0;
	float ParabolicRiseStartDistance = 0.0f;


	void WaveFlightFallStart();
	void WaveFlightFallUpdate(float _Delta);









	// 충돌
	void EnemyCollisionCheck();


	// 디버깅
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
	void ThisDebugTriggerRender(HDC _dc);

};

