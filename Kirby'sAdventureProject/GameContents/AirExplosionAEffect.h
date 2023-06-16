#pragma once
#include "SkillEffect.h"

#define AIREXPLOSIONAEFFECTFRAMECHANGETIME 0.1f

// 설명 : 폭발 효과를 주는 녀석입니다. AirExplosionEffect 로 생성됩니다. 
//		  그냥 제자리에 나타내기 위한 녀석으로 CommonEffect와 똑같은 행동을 합니다.
class AirExplosionAEffect : public SkillEffect
{
public:
	// constrcuter destructer
	AirExplosionAEffect();
	~AirExplosionAEffect();

	// delete Function
	AirExplosionAEffect(const AirExplosionAEffect& _Other) = delete;
	AirExplosionAEffect(AirExplosionAEffect&& _Other) noexcept = delete;
	AirExplosionAEffect& operator=(const AirExplosionAEffect& _Other) = delete;
	AirExplosionAEffect& operator=(AirExplosionAEffect&& _Other) noexcept = delete;

	void init(const float4& _ExplosionPos);

protected:

private:
	float CurrentEffectDistance = 0.0f;


	void Start() override;
	void Update(float _Delta) override;
};

