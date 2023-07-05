#pragma once
#include "SkillEffect.h"




// 설명 : 몹이 충돌할 때 나타나는 십자형 사망 효과입니다.
class CrossDeathEffect : public SkillEffect
{
public:
	// constrcuter destructer
	CrossDeathEffect();
	~CrossDeathEffect();

	// delete Function
	CrossDeathEffect(const CrossDeathEffect& _Other) = delete;
	CrossDeathEffect(CrossDeathEffect&& _Other) noexcept = delete;
	CrossDeathEffect& operator=(const CrossDeathEffect& _Other) = delete;
	CrossDeathEffect& operator=(CrossDeathEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MasterScale);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;



	// this
	bool IsFrist = true;

	const int CreateCount = 4;
	int CreateStarNumber = 0;

	const float EndTime = 0.3f;

	float StarEffectCreateAngle = 0.0f;

};

