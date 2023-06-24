#pragma once
#include "ActorUtils.h"

// 흡입 상태에 관한 상수
#define INHALETIME 0.3f
#define INHALEXPOWER 200.0f


// 커비 입 높이
#define KIRBYCENTERYPOINT 15.0f


#define CHECKOVERSCREENGAP 80.0f



// 설명 : 맵위를 움직이는 액터에 필요한 기능을 제공합니다. 리스폰, 충돌, 상태 함수를 제공합니다.
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

	// 리스폰 함수
	void SetDirectionAndFirstAnimation(const std::string& _StateName);
	void RespawnTrigger();

protected:

	// 상태 함수
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



	// 감지 함수
	float4 GetKirbyOpponentDistance();
	float4 GetKirbyUnitVector();
	void GetKirbyDirection();

	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();


	// 리스폰 함수
	std::string StringRespawnState = "";
	float4 RespawnLocation = float4::ZERO;
	bool IsRespawnLocationOverCamera = true;
	virtual void ChangeRespawnState() {}
	void RespawnLocationOverCamera();
	virtual void CheckOverScreen();



public:
	// 최적화 
	void EnemyPointerRelease();
};

