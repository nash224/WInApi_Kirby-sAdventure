#pragma once
#include "SkillEffect.h"

// 먼지 프레임 간격 시간
#define DUSTEFFECTFRAMECHANGETIME 0.05f
// 먼지가 날아가는 속도
#define DUSTEFFECTSPEED 400.0f


// 설명 : 달릴때나 특정 기믹에서의 먼지 효과 입니다.
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

