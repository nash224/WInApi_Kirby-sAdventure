#pragma once
#include "PowerEnemies.h"


enum class PengiState
{
	Idle,
	BeInhaled,
	Max,
};

// 설명 : 전시용 펭귄입니다.
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


	// 레벨 상속
private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	

	// this
private:
	// 상태패턴 함수
	PengiState State = PengiState::Max;

	void ChangeState(PengiState _State);
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);


	// 충돌
	void EnemyCollisionCheck();


};

