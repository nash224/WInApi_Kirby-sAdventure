#pragma once
#include "SkillEffect.h"

#define SPARKLEEFFECTFRAMECHANGETIME 0.02f


// Ό³Έν :
class SparkleEffect : public SkillEffect
{
public:
	// constrcuter destructer
	SparkleEffect();
	~SparkleEffect();

	// delete Function
	SparkleEffect(const SparkleEffect& _Other) = delete;
	SparkleEffect(SparkleEffect&& _Other) noexcept = delete;
	SparkleEffect& operator=(const SparkleEffect& _Other) = delete;
	SparkleEffect& operator=(SparkleEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos);


protected:

private:
	const float ChangeEffectFramesInter = 0.02f;


	void Start() override;
	void Update(float _Delta) override;
};

