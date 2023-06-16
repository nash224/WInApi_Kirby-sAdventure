#pragma once
#include "PowerEnemies.h"

#define SWORDKNIGHTSPEED 80.0f
#define SWORDKNIGHTSLASHCOOLDOWN 2.0f

#define SWORDKNIGHTRANGEDETECTION 200.0f

#define SWORDKNIGHTRAISESWORDTIME 0.2f
#define SWORDKNIGHTSLASHINSTANTANEOUSSPEED 800.0f
#define SWORDKNIGHTSLASHTIME 0.35f
#define SWORDKNIGHTSLASHFRAMETIME 0.05f

#define SWORDKNIGHTUNDERHANDTIME SWORDKNIGHTRAISESWORDTIME
#define SWORDKNIGHTUNDERHANDINSTANTANEOUSSPEED 600.0f
#define SWORDKNIGHTUNDERSLASHTIME SWORDKNIGHTSLASHTIME
#define SWORDKNIGHTUNDERSLASHFRAMETIME SWORDKNIGHTSLASHFRAMETIME


#define SWORDKNIGHTDEACELECTIONSPEED SWORDKNIGHTSLASHINSTANTANEOUSSPEED / SWORDKNIGHTSLASHTIME


enum class SwordKnightState
{
	PendulumStride,
	RaiseSword,
	Slash,
	Underhand,
	ReversingSlash,
	BeInhaled,
	Hitted,
	Max,
};

// Ό³Έν :
class SwordKnight : public PowerEnemies
{
public:
	// constrcuter destructer
	SwordKnight();
	~SwordKnight();

	// delete Function
	SwordKnight(const SwordKnight& _Other) = delete;
	SwordKnight(SwordKnight&& _Other) noexcept = delete;
	SwordKnight& operator=(const SwordKnight& _Other) = delete;
	SwordKnight& operator=(SwordKnight&& _Other) noexcept = delete;

	void init(const std::string& _FileName, SwordKnightState _State, const float4& _Pos);

protected:
	SwordKnightState State = SwordKnightState::Max;
	SwordKnightState RespawnState = SwordKnightState::Max;

	void StateUpdate(float _Delta) override;
	void ChangeState(SwordKnightState _State);
	void ChangeRespawnState() override;

	void PendulumStrideStart();
	void RaiseSwordStart();
	void SlashStart();
	void UnderhandStart();
	void ReversingSlashStart();

	void PendulumStrideUpdate(float _Delta);
	void RaiseSwordUpdate(float _Delta);
	void SlashUpdate(float _Delta);
	void UnderhandUpdate(float _Delta);
	void ReversingSlashUpdate(float _Delta);

	void EnemyCollisionCheck();

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

};

