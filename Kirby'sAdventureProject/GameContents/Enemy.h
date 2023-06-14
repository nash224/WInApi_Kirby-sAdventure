#pragma once
#include "ActorUtils.h"

#define INHALETIME 0.3f



// ���� :
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

	void SetDirectionAndFirstAnimation(const std::string& _StateName);
	void RespawnTrigger();

protected:
	std::string CurState = "";
	std::string StringRespawnState = "";

	// ���� �Լ�
	virtual void StateUpdate(float _Delta) {}
	void ChangeAnimationState(const std::string& _StateName);

	float4 InhaleTargetPos = float4::ZERO;
	float InhaleTargetPosYDistance = 0.0f;
	float InhaleTargetPosXDistance = 0.0f;
	bool IsInhaleCollision();

	// ���� �Լ�
	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();

	void GetKirbyDirection();
	float4 GetKirbyUnitVector();
	float4 GetKirbyOpponentDistance();

	// ������ �Լ�
	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	virtual void CheckOverScreen();
	virtual void ChangeRespawnState() {}
	void RespawnLocationOverCamera();



private:

};

