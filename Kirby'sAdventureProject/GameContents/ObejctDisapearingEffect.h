#pragma once
#include "SkillEffect.h"



// ���� : Effect �� Ư�� ������Ʈ�� ����� �� �������� ȿ�� �Դϴ�.
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

	void init(const float4& _Pos, bool _Sound = true);


protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float ChangeEffectFramesInter = 0.1f;


};

