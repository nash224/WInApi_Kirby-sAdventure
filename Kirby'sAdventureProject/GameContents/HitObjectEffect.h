#pragma once
#include "SkillEffect.h"

#define HITOBJECTTIME 0.15f
#define HITOJECTDEATHTIME 0.3f
#define HITOBJECTSPEED 400.0f



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

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

