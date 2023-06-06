#pragma once
#include "AerialEnemies.h"

enum class ScarfyState
{
	Idle,
	Fly,
	WaveFlight,
	Exit,
	Max,
};

// Ό³Έν :
class Scarfy : public AerialEnemies
{
public:
	// constrcuter destructer
	Scarfy();
	~Scarfy();

	// delete Function
	Scarfy(const Scarfy& _Other) = delete;
	Scarfy(Scarfy&& _Other) noexcept = delete;
	Scarfy& operator=(const Scarfy& _Other) = delete;
	Scarfy& operator=(Scarfy&& _Other) noexcept = delete;

protected:
	ScarfyState State = ScarfyState::Max;

	void StateUpdate(float _Delta) override;
	void ChangeState(ScarfyState _State);

	void IdleStart();
	void FlyStart();
	void WaveFlightStart();
	void ExitStart();

	void IdleUpdate(float _Delta);
	void FlyUpdate(float _Delta);
	void WaveFlightUpdate(float _Delta);
	void ExitUpdate(float _Delta);


private:
	void Start() override;
	void Update(float _Delta) override;

};

