#pragma once
#include "SkillEffect.h"


// 설명 : Waddle Doo 만이 허가된 빔 공격입니다. 하지만 걸어다니다 커비에게 봉변을 당합니다.
class BeamEffect : public SkillEffect
{
public:
	static bool BeamEndValue;

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
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;




	// this
	float4 MasterScale = float4::ZERO;

	int BeamChangePosCount = 0;
	int EffectPosNumber = 7;

	const float EffectDuration = 0.15f;
	const float FrameChangeTime  = 0.03f;
	float EffectFrameChangeTime = 0.0f;

	const float ShortDistance = 48.0f;
	const float MiddleDistance = 96.0f;
	const float LongDistance = 144.0f;


	// Collision
	CollisionType BeamType = CollisionType::Max;
	CollisionOrder BeamOrder = CollisionOrder::Max;

};

