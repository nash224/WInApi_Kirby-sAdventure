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

	void init(const std::string _FileName, const float4& _Pos);

	void SetDirectionAndFirstAnimation() override;

protected:
	void WaddleDeeMovement(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;

};

