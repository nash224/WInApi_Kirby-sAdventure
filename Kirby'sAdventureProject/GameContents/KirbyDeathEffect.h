#pragma once
#include "SkillEffect.h"



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
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;



	// this
	float StarEffectMoveDuration = 1.8f;
	const float Target_Distance = 700.0f;
	float4 Target_TotalDecelection_UnitVector = float4::ZERO;


};