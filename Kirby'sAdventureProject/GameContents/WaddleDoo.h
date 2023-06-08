#pragma once
#include "PowerEnemies.h"

#define WADDLEDOOSPEED 100.0f


#define WADDLEDOOGRAVITYTIMETOMAXSPEED 0.3f
#define WADDLEDOOGRAVITYLIMIT 450.0f
#define WADDLEDOOJUMPDISTANCE WADDLEDOOGRAVITYLIMIT

#define WADDLEDOOWALKINGCHANGESTATETIME 3.0f
#define WADDLEDOOWALKINGCHANGEANIMATIONTIME 0.2f
#define WADDLEDOOJUMPCHANGEANIMATIONTIME 0.1f

#define WADDLEDOOWOBBLETIME 0.08f

#define WADDLEDOOACTIVATEABILITYTIME 1.5f



enum class WaddleDooState
{
	Walk,
	Jump,
	Wobble,
	ActivateAbility,
	Max,
};

// Ό³Έν :
class WaddleDoo : public PowerEnemies
{
public:
	// constrcuter destructer
	WaddleDoo();
	~WaddleDoo();

	// delete Function
	WaddleDoo(const WaddleDoo& _Other) = delete;
	WaddleDoo(WaddleDoo&& _Other) noexcept = delete;
	WaddleDoo& operator=(const WaddleDoo& _Other) = delete;
	WaddleDoo& operator=(WaddleDoo&& _Other) noexcept = delete;

	void init(const std::string& _FileName, WaddleDooState _State, const float4& _Pos);

protected:
	WaddleDooState State = WaddleDooState::Max;
	WaddleDooState RespawnState = WaddleDooState::Max;

	int WobbleCount = 0;
	size_t WobbleFrame = -1;
	int BombCount = -1;
	int EndCount = -1;
	float CurrentJumpDistance = 0.0f;

	void StateUpdate(float _Delta) override;
	void ChangeState(WaddleDooState _State);
	void ChangeRespawnState() override;

	void WalkStart();
	void JumpStart();
	void WobbleStart();
	void ActivateAbilityStart();

	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void WobbleUpdate(float _Delta);
	void ActivateAbilityUpdate(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

};

