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


// 설명 :
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

	// 상태 함수
	virtual void StateUpdate(float _Delta) {}
	void ChangeAnimationState(const std::string& _StateName);

	// 판정 함수
	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();
	void GetKirbyDirection();
	float4 GetKirbyUnitVector();

	// 리스폰 함수
	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	virtual void CheckOverScreen();
	void RespawnLocationOverCamera();


private:

};

