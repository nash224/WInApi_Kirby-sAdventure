#pragma once
#include "PowerEnemies.h"


enum class PengiState
{
	Idle,
	BeInhaled,
	Max,
};

// 설명 : 공벌레처럼 굴러다니는 파워몹 고슴도치입니다.
class Pengi : public PowerEnemies
{
public:
	// constrcuter destructer
	Pengi();
	~Pengi();

	// delete Function
	Pengi(const Pengi& _Other) = delete;
	Pengi(Pengi&& _Other) noexcept = delete;
	Pengi& operator=(const Pengi& _Other) = delete;
	Pengi& operator=(Pengi&& _Other) noexcept = delete;

	void init(const std::string& _FileName, PengiState _State, const float4& _Pos);


protected:
	// 상태패턴 함수
	PengiState State = PengiState::Max;
	PengiState RespawnState = PengiState::Max;


	void StateUpdate(float _Delta) override;
	void ChangeState(PengiState _State);



	void IdleStart();

	void IdleUpdate(float _Delta);



	void EnemyCollisionCheck();

private:
	void Start() override;
	void Update(float _Delta) override;

};

