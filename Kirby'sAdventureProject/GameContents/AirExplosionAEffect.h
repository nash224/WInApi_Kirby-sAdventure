#pragma once
#include "SkillEffect.h"

#define AIREXPLOSIONAEFFECTFRAMECHANGETIME 0.1f

// ���� : ���� ȿ���� �ִ� �༮�Դϴ�. AirExplosionEffect �� �����˴ϴ�. 
//		  �׳� ���ڸ��� ��Ÿ���� ���� �༮���� CommonEffect�� �Ȱ��� �ൿ�� �մϴ�.
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

