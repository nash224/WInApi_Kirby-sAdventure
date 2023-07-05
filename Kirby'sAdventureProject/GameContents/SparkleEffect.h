#pragma once
#include "SkillEffect.h"



// 설명 : GetAbility에 사용될 이펙트입니다.
class SparkleEffect : public SkillEffect
{
public:
	// constrcuter destructer
	SparkleEffect();
	~SparkleEffect();

	// delete Function
	SparkleEffect(const SparkleEffect& _Other) = delete;
	SparkleEffect(SparkleEffect&& _Other) noexcept = delete;
	SparkleEffect& operator=(const SparkleEffect& _Other) = delete;
	SparkleEffect& operator=(SparkleEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos);


protected:

private:
	// GameEngineObject override;
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;


	// this
	const float ChangeEffectFramesInter = 0.02f;
};

