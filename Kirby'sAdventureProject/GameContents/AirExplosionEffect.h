#pragma once
#include "SkillEffect.h"

#define AIREXPLOSIONEFFECTTIME 0.8f
#define AIREXPLOSIONEFFECTFRAMECHANGETIME 0.1f

#define AIREXPLOSIONEFFECTADISTANCE 12.0f
#define AIREXPLOSIONEFFECTBDISTANCE AIREXPLOSIONEFFECTADISTANCE + 224.0f
#define AIREXPLOSIONEFFECTDISTANCE AIREXPLOSIONEFFECTADISTANCE + 48.0f


// Ό³Έν :
class AirExplosionEffect : public SkillEffect
{
public:
	// constrcuter destructer
	AirExplosionEffect();
	~AirExplosionEffect();

	// delete Function
	AirExplosionEffect(const AirExplosionEffect& _Other) = delete;
	AirExplosionEffect(AirExplosionEffect&& _Other) noexcept = delete;
	AirExplosionEffect& operator=(const AirExplosionEffect& _Other) = delete;
	AirExplosionEffect& operator=(AirExplosionEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale);

protected:

private:
	int ImagePosNumber = 0;
	float ImageFrameChangeTime = 0.0f;


	void Start() override;
	void Update(float _Delta) override;
};

