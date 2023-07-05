#pragma once
#include "SkillEffect.h"



// 설명 : GetAbility 함수입니다.
class GetAbilityEffect : public SkillEffect
{
public:
	// constrcuter destructer
	GetAbilityEffect();
	~GetAbilityEffect();

	// delete Function
	GetAbilityEffect(const GetAbilityEffect& _Other) = delete;
	GetAbilityEffect(GetAbilityEffect&& _Other) noexcept = delete;
	GetAbilityEffect& operator=(const GetAbilityEffect& _Other) = delete;
	GetAbilityEffect& operator=(GetAbilityEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MasterScale);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	int EffectCreateCount = 0;
	float DurationTime = 0.0f;
	const float EffectCreateTime = 0.06f;

	const float CreateMinDistance = 5.0f;
	const float CreateMaxDistance = 50.0f;

};

