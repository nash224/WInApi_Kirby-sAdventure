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


	//this
protected:
	// ���� �� ����
	float AbilityStartDeltaTime = 0.0f;
	float4 GetAbilityDir();



	// �浹
	GameEngineCollision* AbilityCollision = nullptr;
	void EnemyAbilityAttack();

	// �����
	void PowerEnemyDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);

private:

};

