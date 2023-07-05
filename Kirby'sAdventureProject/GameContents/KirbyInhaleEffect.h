#pragma once
#include "SkillEffect.h"


// 설명 : 사용하지 않는 기능입니다.
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
	const float EffectDuration = 10.0f;

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;

};

