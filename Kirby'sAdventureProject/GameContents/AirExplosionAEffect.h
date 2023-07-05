#pragma once
#include "SkillEffect.h"


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
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float FrameChangeTime = 0.1f;
	float CurrentEffectDistance = 0.0f;

};

