#pragma once
#include "Enemy.h"

// ���� : �Ŀ� ������ �θ� Ŭ�����Դϴ�. �ɷ¿� ���� ����� �ֽ��ϴ�.
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

protected:
	GameEngineCollision* AbilityCollision = nullptr;
	float AbilityStartDeltaTime = 0.0f;
	void EnemyAbilityAttack();


	float4 GetAbilityDir();



private:

};

