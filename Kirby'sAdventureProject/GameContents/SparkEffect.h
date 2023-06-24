#pragma once
#include "SkillEffect.h"

#define SPARKEFFECTDISTANCE 39.0f
#define SPARKEFFECTTIME 0.15f


// Ό³Έν :
class SparkEffect : public SkillEffect
{
public:
	// constrcuter destructer
	SparkEffect();
	~SparkEffect();

	// delete Function
	SparkEffect(const SparkEffect& _Other) = delete;
	SparkEffect(SparkEffect&& _Other) noexcept = delete;
	SparkEffect& operator=(const SparkEffect& _Other) = delete;
	SparkEffect& operator=(SparkEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	float CurrentEffectDistance = 0.0f;


	void Start() override;
	void Update(float _Delta) override;
};

