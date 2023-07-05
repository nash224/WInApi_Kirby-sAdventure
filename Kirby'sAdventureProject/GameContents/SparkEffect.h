#pragma once
#include "SkillEffect.h"


// 설명 : Sparky의 전기입니다. 늘 짜릿합니다.
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
	// GameEngineObject override;
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;


	// this
	float CurrentEffectDistance = 0.0f;
	const float EffectDistance = 39.0f;
	const float EffectDurtion = 0.15f;


};

