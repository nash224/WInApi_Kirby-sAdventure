#pragma once
#include "ActorUtils.h"

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

	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	void RespawnTrigger();

	virtual void SetDirectionAndFirstAnimation() {}

protected:
	float4 Scale = float4::ZERO;

	// ���� �Լ�
	virtual void StateUpdate(float _Delta) {}
	virtual void ChangeAnimationState(const std::string& _StateName) {}

	// �̵��Լ�
	void MoveHorizontal(float _Speed, float _Delta);
	void DecelerationUpdate(float _Speed, float _Delta);
	void MoveUpdate(float _MaxSpeed, float _Delta);

	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();

	void CheckOverScreen();
	void RespawnLocationOverCamera();


private:

};

