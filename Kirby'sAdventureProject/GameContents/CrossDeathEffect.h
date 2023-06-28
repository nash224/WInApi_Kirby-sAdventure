#pragma once
#include "SkillEffect.h"

#define STAREFFECTENDTIME 0.3f
#define STAREFFECTCREATECOUNT 4



// ���� : ���� �浹�� �� ��Ÿ���� ������ ��� ȿ���Դϴ�.
class CrossDeathEffect : public SkillEffect
{
public:
	// constrcuter destructer
	CrossDeathEffect();
	~CrossDeathEffect();

	// delete Function
	CrossDeathEffect(const CrossDeathEffect& _Other) = delete;
	CrossDeathEffect(CrossDeathEffect&& _Other) noexcept = delete;
	CrossDeathEffect& operator=(const CrossDeathEffect& _Other) = delete;
	CrossDeathEffect& operator=(CrossDeathEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MasterScale);

protected:

private:
	bool IsFrist = true;
	int CreateStarNumber = 0;
	float StarEffectCreateAngle = 0.0f;

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

