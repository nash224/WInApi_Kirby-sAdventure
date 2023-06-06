#pragma once
#include "AerialEnemies.h"

enum class BrontoState
{
	Idle,
	Rise,
	Fly,
	WaveFlight,
	Fall,
	Exit,
	Max,
};

// Ό³Έν :
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

protected:
	BrontoState State = BrontoState::Max;

	void StateUpdate(float _Delta) override;
	void ChangeState(BrontoState _State);

	void IdleStart();
	void RiseStart();
	void FlyStart();
	void WaveFlightStart();
	void ExitStart();
	void FallStart();

	void IdleUpdate(float _Delta);
	void RiseUpdate(float _Delta);
	void FlyUpdate(float _Delta);
	void WaveFlightUpdate(float _Delta);
	void ExitUpdate(float _Delta);
	void FallUpdate(float _Delta);


private:
	void Start() override;
	void Update(float _Delta) override;

};

