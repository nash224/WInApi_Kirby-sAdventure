#pragma once
#include "ActorUtils.h"

enum class AttributeType
{
	None,
	Fire,
	Electricity,
	Ice,
	Max,
};


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


	AttributeType Attribute = AttributeType::Max;

	void SetDirectionAndFirstAnimation(const std::string& _StateName);
	void RespawnTrigger(const std::string& _StateName);

protected:
	float4 Scale = float4::ZERO;

	// ���� �Լ�
	virtual void StateUpdate(float _Delta) {}
	virtual void ChangeAnimationState(const std::string& _StateName) {}

	// ���� �Լ�
	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();
	void GetKirbyDirection();

	// ������ �Լ�
	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	void CheckOverScreen();
	void RespawnLocationOverCamera();


private:

};

