#pragma once
#include "Enemy.h"

enum class NormalState
{
	Idle,
	Walk,
	Sit,
	Jump,
	Fall,
	Sweep,
	StepOn,
	Bounce,
	Roll,
	BounceMove,
	AppleRun,
	Escape,
	BeInhaled,
	Hitted,
	Max,
};


// 설명 : 노말 몬스터의 상위 클래스입니다. 단순한 패턴이기 때문에 FSM 기능을 제공해줍니다. 
class NormalEnemies : public Enemy
{
public:
	// constrcuter destructer
	NormalEnemies();
	~NormalEnemies();

	// delete Function
	NormalEnemies(const NormalEnemies& _Other) = delete;
	NormalEnemies(NormalEnemies&& _Other) noexcept = delete;
	NormalEnemies& operator=(const NormalEnemies& _Other) = delete;
	NormalEnemies& operator=(NormalEnemies&& _Other) noexcept = delete;



	virtual void init(const std::string& _FileName, NormalState _State, const float4& _Pos);


protected:
	// Enemy 상속
	void ChangeRespawnState() override;


	// FSM
	NormalState State = NormalState::Max;
	NormalState RespawnState = NormalState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(NormalState _State);


	// 상태 패턴
	virtual void AppleRunStart() {}
	virtual void EscapeStart() {}
	virtual void IdleStart() {}
	virtual void WalkStart() {}
	virtual void SitStart() {}
	virtual void JumpStart() {}
	virtual void FallStart() {}
	virtual void BounceStart() {}
	virtual void RollStart() {}
	virtual void BounceMoveStart() {}
	virtual void SweepStart() {}



	virtual void AppleRunUpdate(float _Delta) {}
	virtual void EscapeUpdate(float _Delta) {}
	virtual void IdleUpdate(float _Delta) {}
	virtual void WalkUpdate(float _Delta) {}
	virtual void SitUpdate(float _Delta) {}
	virtual void JumpUpdate(float _Delta) {}
	virtual void FallUpdate(float _Delta) {}
	virtual void BounceUpdate(float _Delta) {}
	virtual void RollUpdate(float _Delta) {}
	virtual void BounceMoveUpdate(float _Delta) {}
	virtual void SweepUpdate(float _Delta) {}



	// 충돌
	void EnemyCollisionCheck();

private:

};

