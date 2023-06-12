#pragma once
#include "SkillEffect.h"

#define BeamEffectTIME 0.8f
#define BeamEffectDISTANCE 0.3f
#define BeamEffectFRAMECHANGETIME 0.1f


// Ό³Έν :
class BeamEffect : public SkillEffect
{
public:
	// constrcuter destructer
	BeamEffect();
	~BeamEffect();

	// delete Function
	BeamEffect(const BeamEffect& _Other) = delete;
	BeamEffect(BeamEffect&& _Other) noexcept = delete;
	BeamEffect& operator=(const BeamEffect& _Other) = delete;
	BeamEffect& operator=(BeamEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale);

protected:

private:
	int ImagePosNumber = 0;
	float ImageFrameChangeTime = 0.0f;


	void Start() override;
	void Update(float _Delta) override;
};

