#pragma once
#include "SkillEffect.h"



// 설명 : 원조는 Hot Head지만 커비가 능력을 뺏어씁니다. 
// Tmi ) 커비의 입구조는 우리의 상식과 다르기 때문에 화상을 입지 않습니다.
class FrameBreathEffect : public SkillEffect
{
public:
	// constrcuter destructer
	FrameBreathEffect();
	~FrameBreathEffect();

	// delete Function
	FrameBreathEffect(const FrameBreathEffect& _Other) = delete;
	FrameBreathEffect(FrameBreathEffect&& _Other) noexcept = delete;
	FrameBreathEffect& operator=(const FrameBreathEffect& _Other) = delete;
	FrameBreathEffect& operator=(FrameBreathEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);


protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	void GroundPassUpdate(float _Delta);
	void GroundNotPassUpdate(float _Delta);


	const float EffectDistance = 100.0f;
	const float EffectDuration = 0.2f;
};

