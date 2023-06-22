#pragma once
#include "NormalEnemies.h"

#define OVERSCREEN_ADDITIONDISTANCE 100.0f


// Ό³Έν :
class Apple : public NormalEnemies
{
public:
	// constrcuter destructer
	Apple();
	~Apple();

	// delete Function
	Apple(const Apple& _Other) = delete;
	Apple(Apple&& _Other) noexcept = delete;
	Apple& operator=(const Apple& _Other) = delete;
	Apple& operator=(Apple&& _Other) noexcept = delete;

	void init(const float4& _SummonPos);


protected:

	void IdleStart() override;
	void FallStart() override;
	void BounceStart() override;
	void RollStart() override;
	void BounceMoveStart() override;


	void IdleUpdate(float _Delta) override;
	void FallUpdate(float _Delta) override;
	void BounceUpdate(float _Delta) override;
	void RollUpdate(float _Delta) override;
	void BounceMoveUpdate(float _Delta) override;

private:
	int TwinkilingCount = 0;
	const float BouncePower = 300.0f;
	const float FirstBouncePower = 400.0f;
	const float SecondBouncePower = 300.0f;
	const float RollPower = 100.0f;

	bool IsSecondBounce = false;
	bool StopBounce = false;



	void Start() override;
	void Update(float _Delta) override;
};

