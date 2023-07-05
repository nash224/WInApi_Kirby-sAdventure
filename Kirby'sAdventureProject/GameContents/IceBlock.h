#pragma once
#include "SkillEffect.h"



enum class IceBlockState 
{
	Idle,
	Wing,
	Max,
};


// 설명 : 커비가 만들어낸 Ice 블럭입니다. 커비와 매우 밀접한 연관성이 있어 커비의 List로 관리합니다.
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

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;



	// skillEffect override
	void SkillDeathEffect() override;
	void DataStructRelease() override;



	// this
	// FSM
	IceBlockState State = IceBlockState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(IceBlockState _State);


	// 상태
	void IdleStart();
	void IdleUpdate(float _Delta);

	const float LiveTime = 3.0f;


	void WingStart();
	void WingUpdate(float _Delta);

	const float EffectSpeed = 600.0f;





	// Collision
	GameEngineCollision* BlockBodyCollision = nullptr;

	void BlockToPlayerCollisionCheck();


	// 상태 최적화 
	void ReleaseThisList();


	// 디버깅
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);

};


