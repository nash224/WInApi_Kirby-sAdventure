#pragma once
#include "Enemy.h"

// Ό³Έν :
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

private:

};

