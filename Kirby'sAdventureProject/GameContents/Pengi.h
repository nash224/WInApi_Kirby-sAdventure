#pragma once
#include "PowerEnemies.h"


enum class PengiState
{
	Idle,
	BeInhaled,
	Max,
};

// ���� : ������ó�� �����ٴϴ� �Ŀ��� ����ġ�Դϴ�.
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
	// �������� �Լ�
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

