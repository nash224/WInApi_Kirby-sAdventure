#pragma once
#include "SkillEffect.h"


// ���� : �ܼ��� ������ġ�� Effect �� ���� ���� �༮�Դϴ�.
class CommonSkillEffect : public SkillEffect
{
public:
	// constrcuter destructer
	CommonSkillEffect();
	~CommonSkillEffect();

	// delete Function
	CommonSkillEffect(const CommonSkillEffect& _Other) = delete;
	CommonSkillEffect(CommonSkillEffect&& _Other) noexcept = delete;
	CommonSkillEffect& operator=(const CommonSkillEffect& _Other) = delete;
	CommonSkillEffect& operator=(CommonSkillEffect&& _Other) noexcept = delete;

	void init(const std::string& _Path, const std::string& _FileName, const float4& _Pos);

	void SetExpressionTime(const float _Time)
	{
		ExpressionTime = _Time;
	}

	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

protected:

private:
	float ExpressionTime = 0.0f;

	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

