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
	float4 Scale = float4::ZERO;

	void SetDirectionAndFirstAnimation(const std::string& _StateName);
	void RespawnTrigger(const std::string& _StateName);

protected:
	std::string CurState = "";

	// ���� �Լ�
	virtual void StateUpdate(float _Delta) {}
	void ChangeAnimationState(const std::string& _StateName);

	// ���� �Լ�
	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();
	void GetKirbyDirection();
	float4 GetKirbyUnitVector();

	// ������ �Լ�
	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	virtual void CheckOverScreen();
	void RespawnLocationOverCamera();


private:

};

