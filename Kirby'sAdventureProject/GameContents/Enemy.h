#pragma once
#include "ActorUtils.h"

// 커비 입 높이
#define Enemy_KIRBYCENTERYPOINT 19.0f


#define CHECKOVERSCREENGAP 120.0f



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

	// IceBlock에서 요구
	float4 Scale = float4::ZERO;


	// 리스폰 함수
	void SetDirectionAndFirstAnimation(const std::string& _StateName);
	void RespawnTrigger();

protected:
	// FSM
	std::string CurState = "";

	virtual void ChangeAnimationState(const std::string& _StateName);



	// 감지, 비트맵
	void GetKirbyDirection();
	float4 GetKirbyUnitVector();
	float4 GetKirbyOpponentDistance();
	float4 KirbyActorCameraPos();

	bool LeftGroundIsCliff();
	bool RightGroundIsCliff();



	// 상태 상속
	virtual void HittedStart();
	virtual void HittedUpdate(float _Delta);

	virtual void BeInhaledStart();
	virtual void BeInhaledUpdate(float _Delta);

	const float InhaledTime = 0.3f;
	float4 MyInhaledStartPos = float4::ZERO;
	float4 InhaleTargetPos = float4::ZERO;
	float Inhaled_Initial_YDistance = 0.0f;
	float InhaleTargetPosYDistance = 0.0f;
	float InhaleTargetPosXDistance = 0.0f;

	float YDecelationSpeed = 0.0f;
	float InhaleXSpeed = 0.0f;

	virtual void BeInhaledRelease();



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

protected:
	// 디버그
	void EnemyDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
	bool Gravitational_Influence = true;
};

