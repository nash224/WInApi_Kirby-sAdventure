#pragma once
#include "AerialEnemies.h"

#define SCARFYRECOGNITIONRANGE 80.0f

#define SCARFYWOBBLETIME 0.08f

#define SCARFYFLYSPEEDACCELERATIONTIME 0.3f
#define SCARFYFLYSPEEDLIMIT 300.0f
#define SCARFYFLIGHTCHANGRAVITYCONVERSIONPOINT 30.0f

#define SCARFYFOLLOWINGTIME 5.0f
#define SCARFYFOLLOWINGSPEED 120.0f
#define SCARFYMAXFOLLOWINGSPEEDTIME 0.2f

#define SCARFYVIBRATIONTIME 0.05f
#define SCARFYVIBRATIONDISTANCE 6.0f




enum class ScarfyState
{
	Idle,
	TransFormingBefore,
	TransFormingAfter,
	Following,
	Bomb,
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

	void init(const std::string& _FileName, ScarfyState _State, const float4& _Pos);

protected:
	ScarfyState State = ScarfyState::Max;

	bool IsGravityReverse = false;
	int WobbleCount = 0;
	int BombCount = -1;

	void StateUpdate(float _Delta) override;
	void ChangeState(ScarfyState _State);

	void IdleStart();
	void TransFormingBeforeStart();
	void TransFormingAfterStart();
	void FollowingStart();
	void BombStart();

	void IdleUpdate(float _Delta);
	void TransFormingBeforeUpdate(float _Delta);
	void TransFormingAfterUpdate(float _Delta);
	void FollowingUpdate(float _Delta);
	void BombUpdate(float _Delta);


private:
	void Start() override;
	void Update(float _Delta) override;

};

