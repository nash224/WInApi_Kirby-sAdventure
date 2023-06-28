#pragma once
#include "SkillEffect.h"

// ���� ������ ���� �ð�
#define DUSTEFFECTFRAMECHANGETIME 0.05f
// ������ ���ư��� �ӵ�
#define DUSTEFFECTSPEED 400.0f


// ���� : �޸����� Ư�� ��Ϳ����� ���� ȿ�� �Դϴ�.
class DustEffect : public SkillEffect
{
public:
	// constrcuter destructer
	DustEffect();
	~DustEffect();

	// delete Function
	DustEffect(const DustEffect& _Other) = delete;
	DustEffect(DustEffect&& _Other) noexcept = delete;
	DustEffect& operator=(const DustEffect& _Other) = delete;
	DustEffect& operator=(DustEffect&& _Other) noexcept = delete;

	void init(const float4& _MasterPos, const float4& _MasterScale, const float4& _Dir, int _ItersCount = 1);

protected:

private:

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

