#pragma once
#include "SkillEffect.h"



// 설명 : 커비가 한숨?로 공격합니다. 몬스터가 피해를 입고 죽는 것을 보면 역시 강한 것 같습니다.
class ExhaleEffect : public SkillEffect
{
public:
	// constrcuter destructer
	ExhaleEffect();
	~ExhaleEffect();

	// delete Function
	ExhaleEffect(const ExhaleEffect& _Other) = delete;
	ExhaleEffect(ExhaleEffect&& _Other) noexcept = delete;
	ExhaleEffect& operator=(const ExhaleEffect& _Other) = delete;
	ExhaleEffect& operator=(ExhaleEffect&& _Other) noexcept = delete;

	void init(const float4& _MasterPos, const float4& _MasterScale, const float4& _EffectDir);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;




	// this
	const float EffectTime = 0.5f;
	const float ForwardTime = 0.3f;
	const float EffectDistance = 400.0f;

};

