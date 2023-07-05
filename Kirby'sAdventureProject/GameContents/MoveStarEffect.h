#pragma once
#include "SkillEffect.h"


// ���� : �ܼ��� ���� �����̱� ���� ȿ���Դϴ�.
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
	void SetSpeedAndDuration(float _Speed, float _Duration);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	float StarEffectSpeed = 400.0f;
	float StarEffectMoveDuration = 0.16f;


};