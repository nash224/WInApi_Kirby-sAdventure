#pragma once
#include "PowerEnemies.h"

// 이동 속도 상수
#define WADDLEDOOSPEED 100.0f

// 점프 상수
#define WADDLEDOOGRAVITYTIMETOMAXSPEED 0.3f
#define WADDLEDOOGRAVITYLIMIT GRAVITYMAXVECTOR
#define WADDLEDOOJUMPDISTANCE 350.0f
#define WADDLEDOOJUMPCHANGEANIMATIONTIME 0.1f

// 걸어다니는 상태의 프레임 간격 시간
#define WADDLEDOOWALKINGCHANGESTATETIME 3.0f
#define WADDLEDOOWALKINGCHANGEANIMATIONTIME 0.2f

// 능력을 사용하기 위해 몸을 떠는 시간 
#define WADDLEDOOWOBBLETIME 0.08f

// 능력 발현 시간
#define WADDLEDOOACTIVATEABILITYTIME 1.5f



enum class WaddleDooState
{
	Walk,
	Jump,
	Wobble,
	ActivateAbility,
	BeInhaled,
	Hitted,
	Max,
};

// 설명 : 커비의 파워몹 시그니처 WaddleDee의 형제인 파워몹입니다.
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

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// Enemy 상속
	void ChangeRespawnState() override;


	// FSM
	WaddleDooState State = WaddleDooState::Max;
	WaddleDooState RespawnState = WaddleDooState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(WaddleDooState _State);


	// 상태
	int WobbleCount = 0;
	size_t WobbleFrame = -1;
	int BombCount = -1;
	int EndCount = -1;
	float CurrentJumpDistance = 0.0f;


	void WalkStart();
	void WalkUpdate(float _Delta);
	void JumpStart();
	void JumpUpdate(float _Delta);

	void WobbleStart();
	void WobbleUpdate(float _Delta);

	void ActivateAbilityStart();
	void ActivateAbilityUpdate(float _Delta);



	void EnemyCollisionCheck();




};

