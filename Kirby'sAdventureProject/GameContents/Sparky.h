#pragma once
#include "PowerEnemies.h"

#define SPARKYSPEED 100.0f

#define SPARKYIDLETIME 0.2f


#define SPARKYFRONTJUMPDISTANCE 21.0f
#define SPARKYFRONTJUMPTIME 0.2f

#define SPARKYLONGJUMPDISTANCE 48.0f
#define SPARKYLONGJUMPTIME 0.25f

#define SPARKYGRAVITYTIMETOMAXSPEED 0.3f
#define SPARKYGRAVITYLIMIT 450.0f
#define SPARKYJUMPDISTANCE SparkyGRAVITYLIMIT

#define SPARKYABILITYTIME 3.0f
#define SPARKYSPARKCHANGEFRAMETIME 0.08f

#define SPARKYLANDINGTIME 0.2f




enum class SparkyState
{
	Idle,
	FrontJump,
	StanceJump,
	LongJump,
	Landing,
	Spark,
	Max,
};

// Ό³Έν :
class Sparky : public PowerEnemies
{
public:
	// constrcuter destructer
	Sparky();
	~Sparky();

	// delete Function
	Sparky(const Sparky& _Other) = delete;
	Sparky(Sparky&& _Other) noexcept = delete;
	Sparky& operator=(const Sparky& _Other) = delete;
	Sparky& operator=(Sparky&& _Other) noexcept = delete;

	void init(const std::string& _FileName, SparkyState _State, const float4& _Pos);

protected:
	SparkyState State = SparkyState::Max;
	SparkyState RespawnState = SparkyState::Max;

	bool IsTurn = false;
	int RemainStanceJumpCount = 0;
	float CurrentJumpDistance = 0.0f;

	void StateUpdate(float _Delta) override;
	void ChangeState(SparkyState _State);
	void ChangeRespawnState() override;


	bool IsLeftStair();
	bool IsRightStair();


	void IdleStart();
	void FrontJumpStart();
	void StanceJumpStart();
	void LongJumpStart();
	void LandingStart();
	void SparkStart();

	void IdleUpdate(float _Delta);
	void FrontJumpUpdate(float _Delta);
	void StanceJumpUpdate(float _Delta);
	void LongJumpUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void SparkUpdate(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

};

