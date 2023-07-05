#pragma once
#include "SkillEffect.h"



// 설명 : 커비의 Ice 능력입니다. 아주 꽁꽁얼려서 순식간에 얼음 덩어리를 만들어 냅니다.
class IceBreathEffect : public SkillEffect
{
public:
	// constrcuter destructer
	IceBreathEffect();
	~IceBreathEffect();

	// delete Function
	IceBreathEffect(const IceBreathEffect& _Other) = delete;
	IceBreathEffect(IceBreathEffect&& _Other) noexcept = delete;
	IceBreathEffect& operator=(const IceBreathEffect& _Other) = delete;
	IceBreathEffect& operator=(IceBreathEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);



protected:


private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// SkilEffect override
	void AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol, bool _IsDeath = false) override;


	// this
	float Total_Effect_FrameTime = 0.4f;
	const float Effect_FrameDistance = 150.f;


};

