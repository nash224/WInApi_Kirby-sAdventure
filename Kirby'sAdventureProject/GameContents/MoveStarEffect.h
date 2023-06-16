#pragma once
#include "SkillEffect.h"

#define STAREFFECTMOVETIME 0.16f
#define STAREFFECTSPEED 400.0f



// Ό³Έν :
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