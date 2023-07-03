#pragma once
#include "Enemy.h"

// 설명 : 파워 몬스터의 부모 클래스입니다. 능력에 관한 기능이 있습니다.
class PowerEnemies : public Enemy
{
public:
	// constrcuter destructer
	PowerEnemies();
	~PowerEnemies();

	// delete Function
	PowerEnemies(const PowerEnemies& _Other) = delete;
	PowerEnemies(PowerEnemies&& _Other) noexcept = delete;
	PowerEnemies& operator=(const PowerEnemies& _Other) = delete;
	PowerEnemies& operator=(PowerEnemies&& _Other) noexcept = delete;


	//this
protected:
	// 상태 및 방향
	float AbilityStartDeltaTime = 0.0f;
	float4 GetAbilityDir();



	// 충돌
	GameEngineCollision* AbilityCollision = nullptr;
	void EnemyAbilityAttack();

	// 디버깅
	void PowerEnemyDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);

private:

};

