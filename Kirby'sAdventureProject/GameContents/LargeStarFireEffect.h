#pragma once
#include "SkillEffect.h"



// ���� : Ŀ�� ��� �������Դϴ�. ���ĺ�����? ������ ���Ŵϴ�.
class LargeStarFireEffect : public SkillEffect
{
public:
	// constrcuter destructer
	LargeStarFireEffect();
	~LargeStarFireEffect();

	// delete Function
	LargeStarFireEffect(const LargeStarFireEffect& _Other) = delete;
	LargeStarFireEffect(LargeStarFireEffect&& _Other) noexcept = delete;
	LargeStarFireEffect& operator=(const LargeStarFireEffect& _Other) = delete;
	LargeStarFireEffect& operator=(LargeStarFireEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float FramesInter = 0.12f;
	const float EffectSpeed = 600.0f;
};


