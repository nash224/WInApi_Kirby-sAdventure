#pragma once
#include "SkillEffect.h"

#define EXHALEEFFECTTIME 0.5f
#define EXHALEEFFECTFORWARDTIME 0.3f
#define EXHALEEFFECTDISTANCE 400.0f


// Ό³Έν :
class ExhaleEffect : public SkillEffect
{
public:
	// constrcuter destructer
	ExhaleEffect();
	~ExhaleEffect();

	// delete Function
	ExhaleEffect(const ExhaleEffect& _Other) = delete;
	ExhaleEffect(ExhaleEffect&& _Other) noexcept = delete;
	ExhaleEffect& operator=(const ExhaleEffect& _Other) = delete;
	ExhaleEffect& operator=(ExhaleEffect&& _Other) noexcept = delete;

	void init(const float4& _MasterPos, const float4& _MasterScale, const float4& _EffectDir);

protected:

private:

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

