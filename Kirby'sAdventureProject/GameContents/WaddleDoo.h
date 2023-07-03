#pragma once
#include "PowerEnemies.h"

// �̵� �ӵ� ���
#define WADDLEDOOSPEED 100.0f

// ���� ���
#define WADDLEDOOGRAVITYTIMETOMAXSPEED 0.3f
#define WADDLEDOOGRAVITYLIMIT GRAVITYMAXVECTOR
#define WADDLEDOOJUMPDISTANCE 350.0f
#define WADDLEDOOJUMPCHANGEANIMATIONTIME 0.1f

// �ɾ�ٴϴ� ������ ������ ���� �ð�
#define WADDLEDOOWALKINGCHANGESTATETIME 3.0f
#define WADDLEDOOWALKINGCHANGEANIMATIONTIME 0.2f

// �ɷ��� ����ϱ� ���� ���� ���� �ð� 
#define WADDLEDOOWOBBLETIME 0.08f

// �ɷ� ���� �ð�
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

// ���� : Ŀ���� �Ŀ��� �ñ״�ó WaddleDee�� ������ �Ŀ����Դϴ�.
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
	// �������� �Լ�
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



	void EnemyCollisionCheck();

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



};

