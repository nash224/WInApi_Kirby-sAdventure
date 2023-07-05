#pragma once
#include "SkillEffect.h"



// ���� : GetAbility�� ���� ����Ʈ�Դϴ�.
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

