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


enum class WhispyWoodState
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

// 설명 : 검을 들고 항상 커비를 노리고 있는 파워몹 검사입니다.
class WhispyWood : public PowerEnemies
{
public:
	// constrcuter destructer
	WhispyWood();
	~WhispyWood();

	// delete Function
	WhispyWood(const WhispyWood& _Other) = delete;
	WhispyWood(WhispyWood&& _Other) noexcept = delete;
	WhispyWood& operator=(const WhispyWood& _Other) = delete;
	WhispyWood& operator=(WhispyWood&& _Other) noexcept = delete;

	void init(const std::string& _FileName, WhispyWoodState _State, const float4& _Pos);

protected:
	// 상태패턴 함수
	WhispyWoodState State = WhispyWoodState::Max;
	WhispyWoodState RespawnState = WhispyWoodState::Max;


	void StateUpdate(float _Delta) override;
	void ChangeState(WhispyWoodState _State);
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

