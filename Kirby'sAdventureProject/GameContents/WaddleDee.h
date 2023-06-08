#pragma once
#include "NormalEnemies.h"

#define WaddleSpeed 100.0f

// Ό³Έν :
class WaddleDee : public NormalEnemies
{
public:
	// constrcuter destructer
	WaddleDee();
	~WaddleDee();

	// delete Function
	WaddleDee(const WaddleDee& _Other) = delete;
	WaddleDee(WaddleDee&& _Other) noexcept = delete;
	WaddleDee& operator=(const WaddleDee& _Other) = delete;
	WaddleDee& operator=(WaddleDee&& _Other) noexcept = delete;

protected:

	void WalkStart() override;
	void WalkUpdate(float _Delta) override;

private:
	void Start() override;
	void Update(float _Delta) override;

};

