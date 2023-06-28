#pragma once
#include "SkillEffect.h"



// 설명 : Effect 나 특정 오브젝트가 사라질 때 없어지는 효과 입니다.
class ObejctDisapearingEffect : public SkillEffect
{
public:
	// constrcuter destructer
	ObejctDisapearingEffect();
	~ObejctDisapearingEffect();

	// delete Function
	ObejctDisapearingEffect(const ObejctDisapearingEffect& _Other) = delete;
	ObejctDisapearingEffect(ObejctDisapearingEffect&& _Other) noexcept = delete;
	ObejctDisapearingEffect& operator=(const ObejctDisapearingEffect& _Other) = delete;
	ObejctDisapearingEffect& operator=(ObejctDisapearingEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos);


protected:

private:
	// 프레임 간격 시간
	const float ChangeEffectFramesInter = 0.1f;


	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

