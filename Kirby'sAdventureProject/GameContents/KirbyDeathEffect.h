#pragma once
#include "SkillEffect.h"

// �Ÿ� �� �ð�
#define STAREFFECTMOVETIME 0.16f
#define STAREFFECTSPEED 400.0f



// ���� : �ܼ��� ���� �����̱� ���� ȿ���Դϴ�.
class KirbyDeathEffect : public SkillEffect
{
public:
	// constrcuter destructer
	KirbyDeathEffect();
	~KirbyDeathEffect();

	// delete Function
	KirbyDeathEffect(const KirbyDeathEffect& _Other) = delete;
	KirbyDeathEffect(KirbyDeathEffect&& _Other) noexcept = delete;
	KirbyDeathEffect& operator=(const KirbyDeathEffect& _Other) = delete;
	KirbyDeathEffect& operator=(KirbyDeathEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _Dir);

protected:

private:
	float StarEffectMoveDuration = 1.8f;

	float MovePower = 0.0f;
	const float Target_Distance = 700.0f;
	float4 Target_TotalDecelection_UnitVector = float4::ZERO;



	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};