#pragma once
#include "SkillEffect.h"



// ���� : �ʿ� ����� �� '��' ���� �ε����� ȿ�� �Դϴ�.
class HitObjectEffect : public SkillEffect
{
public:
	// constrcuter destructer
	HitObjectEffect();
	~HitObjectEffect();

	// delete Function
	HitObjectEffect(const HitObjectEffect& _Other) = delete;
	HitObjectEffect(HitObjectEffect&& _Other) noexcept = delete;
	HitObjectEffect& operator=(const HitObjectEffect& _Other) = delete;
	HitObjectEffect& operator=(HitObjectEffect&& _Other) noexcept = delete;

	void init(const float4& _MasterPos, const float4& _Pos);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float EffectTime = 0.15f;
	const float DeathTime = 0.3f;
	const float EffectSpeed = 400.0f;

};

