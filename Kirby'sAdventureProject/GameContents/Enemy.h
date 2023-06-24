#pragma once
#include "ActorUtils.h"

// ���� ���¿� ���� ���
#define INHALETIME 0.3f
#define INHALEXPOWER 200.0f


// Ŀ�� �� ����
#define KIRBYCENTERYPOINT 15.0f


#define CHECKOVERSCREENGAP 80.0f



// ���� : ������ �����̴� ���Ϳ� �ʿ��� ����� �����մϴ�. ������, �浹, ���� �Լ��� �����մϴ�.
class Enemy : public ActorUtils
{
public:
	// constrcuter destructer
	Enemy();
	~Enemy();

	// delete Function
	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;


	float4 Scale = float4::ZERO;

	// ������ �Լ�
	void SetDirectionAndFirstAnimation(const std::string& _StateName);
	void RespawnTrigger();

protected:

	// ���� �Լ�
	std::string CurState = "";

	virtual void StateUpdate(float _Delta) {}
	void ChangeAnimationState(const std::string& _StateName);



	float4 InhaleTargetPos = float4::ZERO;
	float InhaleTargetPosYDistance = 0.0f;
	float InhaleTargetPosXDistance = 0.0f;


	virtual void BeInhaledStart();
	virtual void HittedStart();

	virtual void BeInhaledUpdate(float _Delta);
	virtual void HittedUpdate(float _Delta);



	// ���� �Լ�
	float4 GetKirbyOpponentDistance();
	float4 GetKirbyUnitVector();
	void GetKirbyDirection();

	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();


	// ������ �Լ�
	std::string StringRespawnState = "";
	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	virtual void ChangeRespawnState() {}
	void RespawnLocationOverCamera();
	virtual void CheckOverScreen();



public:
	// ����ȭ 
	void EnemyPointerRelease();
};

