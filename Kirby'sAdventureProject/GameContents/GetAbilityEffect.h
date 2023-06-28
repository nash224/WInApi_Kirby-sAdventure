#pragma once
#include "SkillEffect.h"

#define SPARKLEEFFECTCREATEMINDISTANCE 5.0f
#define SPARKLEEFFECTCREATEMAXDISTANCE 50.0f

// Ό³Έν :
class GetAbilityEffect : public SkillEffect
{
public:
	// constrcuter destructer
	GetAbilityEffect();
	~GetAbilityEffect();

	// delete Function
	GetAbilityEffect(const GetAbilityEffect& _Other) = delete;
	GetAbilityEffect(GetAbilityEffect&& _Other) noexcept = delete;
	GetAbilityEffect& operator=(const GetAbilityEffect& _Other) = delete;
	GetAbilityEffect& operator=(GetAbilityEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MasterScale);

protected:

private:
	float DurationTime = 0.0f;
	const float EffectCreateTime = 0.06f;

	int EffectCreateCount = 0;


	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

