#pragma once
#include "SkillEffect.h"


#define KIRBYSPARKEFFECTSPEED 150.0f


// 설명 : 커비의 Spark 능력입니다. 이제 커비도 전기에 면역입니다.
// TMI) 능력이 있지만 Sparky에 닿으면 감전됩니다.
class KirbySparkEffect : public SkillEffect
{
public:
	// constrcuter destructer
	KirbySparkEffect();
	~KirbySparkEffect();

	// delete Function
	KirbySparkEffect(const KirbySparkEffect& _Other) = delete;
	KirbySparkEffect(KirbySparkEffect&& _Other) noexcept = delete;
	KirbySparkEffect& operator=(const KirbySparkEffect& _Other) = delete;
	KirbySparkEffect& operator=(KirbySparkEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float ChangeFrameInter = 0.05f;

	int ImagePosNumber = 0;
	float ImageFrameChangeTime = 0.0f;

	const float StartDistance = 10.0f;
	const float EffectSpeed = 150.0f;

};

