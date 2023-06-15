#pragma once
#include "SkillEffect.h"


#define KIRBYSPARKCHANGEFRAMESTIME 0.05f
#define KIRBYSPARKEFFECTSPEED 150.0f


// Ό³Έν :
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
	int ImagePosNumber = 0;
	float ImageFrameChangeTime = 0.0f;

	const float StartDistance = 10.0f;

	void Start() override;
	void Update(float _Delta) override;
};

