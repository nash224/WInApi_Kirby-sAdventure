#pragma once
#include "SkillEffect.h"


#define KIRBYSPARKEFFECTSPEED 150.0f


// ���� : Ŀ���� Spark �ɷ��Դϴ�. ���� Ŀ�� ���⿡ �鿪�Դϴ�.
// TMI) �ɷ��� ������ Sparky�� ������ �����˴ϴ�.
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

