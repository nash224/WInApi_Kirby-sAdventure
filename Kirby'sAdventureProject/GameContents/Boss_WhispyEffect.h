#pragma once
#include "SkillEffect.h"



// 설명 : WhispyWood가 한번씩 내뱉는 한숨입니다. 커비 한숨보다 빠르고 변화구가 있습니다.
// 보스가 클리어될 때 임펙트가 모두 삭제되는 효과를 주기 위해서 List를 사용했으며 메모리 해제되는 동시에 List에서도 해제해줍니다.
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
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// SkillEffect override
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

