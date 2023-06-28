#pragma once
#include "SkillEffect.h"


// 설명 : 단순히 지정위치에 Effect 를 띄우기 위한 녀석입니다.
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

