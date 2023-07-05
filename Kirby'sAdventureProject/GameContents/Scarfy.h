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
	Hitted,
	Max,
};


// 설명 : 귀엽게 생긴 비행형 몬스터지만, 방심해서는 안됩니다. 
// TMI ) 이 몬스터는 다른 이면이 있습니다.
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

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// Enemy 상속
	void HittedStart() override;
	void HittedUpdate(float _Delta) override;


	// FSM
	ScarfyState State = ScarfyState::Max;
	ScarfyState RespawnState = ScarfyState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(ScarfyState _State);
	void ChangeRespawnState() override;


	// 상태
	void IdleStart();
	void IdleUpdate(float _Delta);

	bool IsGravityReverse = false;


	void TransFormingBeforeStart();
	void TransFormingBeforeUpdate(float _Delta);

	int WobbleCount = 0;


	void TransFormingAfterStart();
	void TransFormingAfterUpdate(float _Delta);

	void FollowingStart();
	void FollowingUpdate(float _Delta);

	void BombStart();
	void BombUpdate(float _Delta);

	int BombCount = -1;


	// 충돌
	void EnemyCollisionCheck();




	// 디버깅
	void ThisDebugTriggerRender(HDC _dc);
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);

};

