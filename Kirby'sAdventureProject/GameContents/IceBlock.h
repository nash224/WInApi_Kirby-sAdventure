#pragma once
#include "SkillEffect.h"

#define SMALLSTARFIREEFFECTSPEED 600.0f


enum class IceBlockState 
{
	Idle,
	Wing,
	Max,
};


// 설명 :
class IceBlock : public SkillEffect
{
public:
	// constrcuter destructer
	IceBlock();
	~IceBlock();

	// delete Function
	IceBlock(const IceBlock& _Other) = delete;
	IceBlock(IceBlock&& _Other) noexcept = delete;
	IceBlock& operator=(const IceBlock& _Other) = delete;
	IceBlock& operator=(IceBlock&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MasterPos);

protected:

	// Level override
private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;



	// skillEffect override
	void SkillDeathEffect() override;
	void DataStructRelease() override;



	// this
	// 상태 패턴
	IceBlockState State = IceBlockState::Max;
	void StateUpdate(float _Delta);
	void ChangeState(IceBlockState _State);


	void IdleStart();
	void WingStart();

	void IdleUpdate(float _Delta);
	void WingUpdate(float _Delta);



	// Wing 패턴
	const float LiveTime = 3.0f;





	// Collision
	GameEngineCollision* BlockBodyCollision = nullptr;

	void BlockToPlayerCollisionCheck();


	// 상태 최적화 
	void ReleaseThisList();
};

