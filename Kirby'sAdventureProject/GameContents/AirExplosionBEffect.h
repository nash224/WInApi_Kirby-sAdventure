#pragma once
#include "SkillEffect.h"


// 설명 : Bomb 효과 중 겉에 도는 이펙트입니다.
class AirExplosionBEffect : public SkillEffect
{
public:
	// constrcuter destructer
	AirExplosionBEffect();
	~AirExplosionBEffect();

	// delete Function
	AirExplosionBEffect(const AirExplosionBEffect& _Other) = delete;
	AirExplosionBEffect(AirExplosionBEffect&& _Other) noexcept = delete;
	AirExplosionBEffect& operator=(const AirExplosionBEffect& _Other) = delete;
	AirExplosionBEffect& operator=(AirExplosionBEffect&& _Other) noexcept = delete;

	void init(const float4& _ExplosionPos);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float FrameChangeTime = 0.05f;
	float CurrentEffectDistance = 0.0f;


};

