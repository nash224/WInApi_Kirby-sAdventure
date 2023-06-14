#pragma once
#include "ActorUtils.h"

#define INHALETIME 0.3f



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


	float4 Scale = float4::ZERO;

	void SetDirectionAndFirstAnimation(const std::string& _StateName);
	void RespawnTrigger();

protected:
	std::string CurState = "";
	std::string StringRespawnState = "";

	// 상태 함수
	virtual void StateUpdate(float _Delta) {}
	void ChangeAnimationState(const std::string& _StateName);

	float4 InhaleTargetPos = float4::ZERO;
	float InhaleTargetPosYDistance = 0.0f;
	float InhaleTargetPosXDistance = 0.0f;
	bool IsInhaleCollision();

	// 판정 함수
	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();

	void GetKirbyDirection();
	float4 GetKirbyUnitVector();
	float4 GetKirbyOpponentDistance();

	// 리스폰 함수
	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	virtual void CheckOverScreen();
	virtual void ChangeRespawnState() {}
	void RespawnLocationOverCamera();



private:

};

