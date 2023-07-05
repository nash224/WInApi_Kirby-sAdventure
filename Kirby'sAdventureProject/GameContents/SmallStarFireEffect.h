#pragma once
#include "SkillEffect.h"

#define SMALLSTARFIREEFFECTSPEED 600.0f


// Ό³Έν :
class SmallStarFireEffect : public SkillEffect
{
public:
	// constrcuter destructer
	SmallStarFireEffect();
	~SmallStarFireEffect();

	// delete Function
	SmallStarFireEffect(const SmallStarFireEffect& _Other) = delete;
	SmallStarFireEffect(SmallStarFireEffect&& _Other) noexcept = delete;
	SmallStarFireEffect& operator=(const SmallStarFireEffect& _Other) = delete;
	SmallStarFireEffect& operator=(SmallStarFireEffect&& _Other) noexcept = delete;

	void init(const std::string& _FileName, const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	const float FramesInter = 0.12f;

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;


	void SkillDeathEffect() override;


};

