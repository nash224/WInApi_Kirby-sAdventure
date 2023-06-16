#pragma once

// Ό³Έν :
class SpreadDeathEffect
{
public:
	// constrcuter destructer
	SpreadDeathEffect();
	~SpreadDeathEffect();

	// delete Function
	SpreadDeathEffect(const SpreadDeathEffect& _Other) = delete;
	SpreadDeathEffect(SpreadDeathEffect&& _Other) noexcept = delete;
	SpreadDeathEffect& operator=(const SpreadDeathEffect& _Other) = delete;
	SpreadDeathEffect& operator=(SpreadDeathEffect&& _Other) noexcept = delete;

protected:

private:

};

