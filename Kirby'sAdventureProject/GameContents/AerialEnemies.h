#pragma once
#include "Enemy.h"

// Ό³Έν :
class AerialEnemies : public Enemy
{
public:
	// constrcuter destructer
	AerialEnemies();
	~AerialEnemies();

	// delete Function
	AerialEnemies(const AerialEnemies& _Other) = delete;
	AerialEnemies(AerialEnemies&& _Other) noexcept = delete;
	AerialEnemies& operator=(const AerialEnemies& _Other) = delete;
	AerialEnemies& operator=(AerialEnemies&& _Other) noexcept = delete;

protected:
	float ChangeGravityDistance = 0.0f;

private:

};