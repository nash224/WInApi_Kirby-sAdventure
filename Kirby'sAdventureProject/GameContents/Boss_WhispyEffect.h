#pragma once
#include "SkillEffect.h"



// 설명 :
class Boss_WhispyEffect : public SkillEffect
{
public:
	// constrcuter destructer
	Boss_WhispyEffect();
	~Boss_WhispyEffect();

	// delete Function
	Boss_WhispyEffect(const Boss_WhispyEffect& _Other) = delete;
	Boss_WhispyEffect(Boss_WhispyEffect&& _Other) noexcept = delete;
	Boss_WhispyEffect& operator=(const Boss_WhispyEffect& _Other) = delete;
	Boss_WhispyEffect& operator=(Boss_WhispyEffect&& _Other) noexcept = delete;

	void init(const float4& _MasterPos, const float4& _MaterScale);

protected:

private:
	// Level
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;


	// SkillEffect
	void DataStructRelease() override;



	// this
	const float WhispySpeed = 500.f;
	const float WhispyYSpeedRatio = 0.2f;
	float XSpeed = 0.0f;
	float YSpeed = 0.0f;
	float XOriginSpeed = 0.0f;

	const float Whispy_ChangeDir_XDistance = 200.0f;
	const float Whispy_DecelectionRatio = 4.0f;
	float Current_XDsitance = 0.0f;

	bool IsFirstinflectionPoint = false;

	bool IsSecondinflectionPoint = false;


	// 초기화
	void ReleaseThisList();
};

