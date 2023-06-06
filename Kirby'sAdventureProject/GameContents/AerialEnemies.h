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

	virtual void init(const std::string _FileName, const float4& _Pos);

protected:
	std::string CurState = "";


	void ChangeAnimationState(const std::string& _StateName) override;

private:

};