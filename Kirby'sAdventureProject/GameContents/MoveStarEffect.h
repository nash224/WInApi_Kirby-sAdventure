#pragma once
#include "SkillEffect.h"

// 거리 및 시간
#define STAREFFECTMOVETIME 0.16f
#define STAREFFECTSPEED 400.0f



// 설명 : 단순히 별을 움직이기 위한 효과입니다.
class MoveStarEffect : public SkillEffect
{
public:
	// constrcuter destructer
	MoveStarEffect();
	~MoveStarEffect();

	// delete Function
	MoveStarEffect(const MoveStarEffect& _Other) = delete;
	MoveStarEffect(MoveStarEffect&& _Other) noexcept = delete;
	MoveStarEffect& operator=(const MoveStarEffect& _Other) = delete;
	MoveStarEffect& operator=(MoveStarEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _Dir);

protected:

private:

	void Start() override;
	void Update(float _Delta) override;
};