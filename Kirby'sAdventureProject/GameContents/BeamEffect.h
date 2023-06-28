#pragma once
#include "SkillEffect.h"

#define BEAMEFFECTTIME 0.15f
#define BEAMEFFECTFRAMECHANGETIME 0.04f

#define BEAMEFFECTSHORTDISTANCE 48.0f
#define BEAMEFFECTMIDDLEDISTANCE 96.0f
#define BEAMEFFECTLONGDISTANCE 144.0f


// Ό³Έν :
class BeamEffect : public SkillEffect
{
public:
	// constrcuter destructer
	BeamEffect();
	~BeamEffect();

	// delete Function
	BeamEffect(const BeamEffect& _Other) = delete;
	BeamEffect(BeamEffect&& _Other) noexcept = delete;
	BeamEffect& operator=(const BeamEffect& _Other) = delete;
	BeamEffect& operator=(BeamEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _EffectDir);
	void SetActorCollision(CollisionOrder _Order, CollisionType _Type, const float4& _None = float4::ZERO) override;


protected:

private:
	CollisionType BeamType = CollisionType::Max;
	CollisionOrder BeamOrder = CollisionOrder::Max;

	class Kirby* EffectMaster = nullptr;
	
	int BeamChangePosCount = 0;
	int EffectPosNumber = 7;
	float EffectFrameChangeTime = 0.0f;


	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;


};

