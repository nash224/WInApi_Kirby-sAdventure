#pragma once
#include "SkillEffect.h"


// 설명 : 커비가 입으로 벹은 유리 대포알입니다. 맞으면 생각보다 아픕니다.
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
	// GameEngineObject override;
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override;
	void LevelEnd() override;


	// SkillEffect override;
	void SkillDeathEffect() override;



	// this
	const float FramesInter = 0.12f;
	const float EffectSpeed = 600.0f;



};

