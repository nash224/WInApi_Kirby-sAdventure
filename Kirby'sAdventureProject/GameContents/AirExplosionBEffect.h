#pragma once
#include "SkillEffect.h"

#define AIREXPLOSIONBEFFECTFRAMECHANGETIME 0.05f


// Ό³Έν :
class AirExplosionBEffect : public SkillEffect
{
public:
	// constrcuter destructer
	AirExplosionBEffect();
	~AirExplosionBEffect();

	// delete Function
	AirExplosionBEffect(const AirExplosionBEffect& _Other) = delete;
	AirExplosionBEffect(AirExplosionBEffect&& _Other) noexcept = delete;
	AirExplosionBEffect& operator=(const AirExplosionBEffect& _Other) = delete;
	AirExplosionBEffect& operator=(AirExplosionBEffect&& _Other) noexcept = delete;

	void init(const float4& _ExplosionPos);

protected:

private:
	float CurrentEffectDistance = 0.0f;


	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

