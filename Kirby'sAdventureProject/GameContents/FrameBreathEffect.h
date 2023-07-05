#pragma once
#include "SkillEffect.h"

#define FRAMEBREATHEFFECTDISTANCE 100.0f

#define FRAMEBREATHEFFECTDURATION 0.2f


// Ό³Έν :
class FrameBreathEffect : public SkillEffect
{
public:
	// constrcuter destructer
	FrameBreathEffect();
	~FrameBreathEffect();

	// delete Function
	FrameBreathEffect(const FrameBreathEffect& _Other) = delete;
	FrameBreathEffect(FrameBreathEffect&& _Other) noexcept = delete;
	FrameBreathEffect& operator=(const FrameBreathEffect& _Other) = delete;
	FrameBreathEffect& operator=(FrameBreathEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;

	void GroundPassUpdate(float _Delta);
	void GroundNotPassUpdate(float _Delta);
};

