#pragma once
#include "SkillEffect.h"


// 설명 : Hot Head 가 일정거리에서 커비를 요격합니다. 하지만 고도가 제한되어 있어 맞추기 힘들어 합니다.
class FireBallEffect : public SkillEffect
{
public:
	// constrcuter destructer
	FireBallEffect();
	~FireBallEffect();

	// delete Function
	FireBallEffect(const FireBallEffect& _Other) = delete;
	FireBallEffect(FireBallEffect&& _Other) noexcept = delete;
	FireBallEffect& operator=(const FireBallEffect& _Other) = delete;
	FireBallEffect& operator=(FireBallEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float EffectSpeed = 400.0f;
};

