#pragma once
#include "SkillEffect.h"

#define KirbyInhaleEffectTIME 0.15f


// Ό³Έν :
class KirbyInhaleEffect : public SkillEffect
{
public:
	// constrcuter destructer
	KirbyInhaleEffect();
	~KirbyInhaleEffect();

	// delete Function
	KirbyInhaleEffect(const KirbyInhaleEffect& _Other) = delete;
	KirbyInhaleEffect(KirbyInhaleEffect&& _Other) noexcept = delete;
	KirbyInhaleEffect& operator=(const KirbyInhaleEffect& _Other) = delete;
	KirbyInhaleEffect& operator=(KirbyInhaleEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _EffectDir);

protected:

private:

	void Start() override;
	void Update(float _Delta) override;

};

