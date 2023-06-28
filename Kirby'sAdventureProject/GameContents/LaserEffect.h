#pragma once
#include "SkillEffect.h"

#define LaserEffectSPEED 1200.0f


// 설명 :
class LaserEffect : public SkillEffect
{
public:
	// constrcuter destructer
	LaserEffect();
	~LaserEffect();

	// delete Function
	LaserEffect(const LaserEffect& _Other) = delete;
	LaserEffect(LaserEffect&& _Other) noexcept = delete;
	LaserEffect& operator=(const LaserEffect& _Other) = delete;
	LaserEffect& operator=(LaserEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);
	void Soundinit();

protected:
	// 사운드
	bool IsSoundinit = false;

private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;

	void SkillDeathEffect() override;


	void GroundPassUpdate(float _Delta) override;
	void GroundNotPassUpdate(float _Delta) override;
};

