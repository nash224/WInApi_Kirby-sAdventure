#pragma once
#include "Enemy.h"

#define WaddleSpeed 100.0f

// Ό³Έν :
class WaddleDee : public Enemy
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

	void init(const std::string _FileName, float4 _Pos);

protected:
	void WaddleDeeMovement(float _Delta);

private:
	void Start() override;
	void SetDirectionAndFirstAnimation();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

};

