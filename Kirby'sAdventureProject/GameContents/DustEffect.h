#pragma once
#include "SkillEffect.h"

#define DUSTEFFECTFRAMECHANGETIME 0.05f
#define DUSTEFFECTSPEED 400.0f


// Ό³Έν :
class DustEffect : public SkillEffect
{
public:
	// constrcuter destructer
	DustEffect();
	~DustEffect();

	// delete Function
	DustEffect(const DustEffect& _Other) = delete;
	DustEffect(DustEffect&& _Other) noexcept = delete;
	DustEffect& operator=(const DustEffect& _Other) = delete;
	DustEffect& operator=(DustEffect&& _Other) noexcept = delete;

	void init(const float4& _MasterPos, const float4& _MasterScale, const float4& _Dir);

protected:

private:

	void Start() override;
	void Update(float _Delta) override;
};

