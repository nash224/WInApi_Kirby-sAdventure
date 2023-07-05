#pragma once
#include "SkillEffect.h"



// ���� : ������ Hot Head���� Ŀ�� �ɷ��� ����ϴ�. 
// Tmi ) Ŀ���� �Ա����� �츮�� ��İ� �ٸ��� ������ ȭ���� ���� �ʽ��ϴ�.
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

