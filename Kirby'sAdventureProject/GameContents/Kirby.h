#pragma once
#include "ActorUtils.h"

#include <map>
#include <string>

#define WALKMAXSPEED 300.0f
#define RUNMAXSPEED 425.0f
#define FLYMAXSPEED 200.0f

#define WALKSPEED 0.8f
#define RUNSPEED 1.2f
#define FLYSPEED 0.6f

#define JUMPPOWER 310.0f
#define FLYPOWER 280.0f

#define DECELERATIONSPEED 0.8f
#define BRAKESPEED 2.0f

#define HITTHEMAPTIME 0.08f
#define EXHALEATTACKTIME 0.08f
#define TAKEOFFTIME 0.4f
#define JUMPTIME 0.4f



enum class KirbyBodyState
{
	Little,
	Fat,
	Lower,
	Max,
};

enum class KirbyState
{
	Idle,
	Walk,
	Run,
	Turn,
	Jump,
	AerialMotion,
	Fall,
	AccelerateDown,
	Bounce,
	Landing,
	LowerPosture,
	LowerAttack,
	HittheWall,
	HittheCeiling,
	TakeOff,
	Fly,
	ExhaleAttack,
	UseSpecialAbility,
	ReleaseAbility,
	Contain_Idle,
	Contain_Walk,
	Contain_Run,
	Contain_Turn,
	Contain_Jump,
	Contain_Fall,
	Contain_Gulp,
	Contain_Disgorge,
	GetAbility,
	Max,
};

enum class KirbyMode
{
	Normal,
	Needle,
	Spark,
	Beam,
	Laser,
	UFO,
	Fire,
	Freeze,
	Sword,
	Max,
};

enum class AbilityStar
{
	None,
	Spark,
	Beam,
	Laser,
	UFO,
	Fire,
	Freeze,
	Sword,
	Max,
};


class Kirby : public ActorUtils
{
public:
	// constructor desstructor
	Kirby();
	~Kirby();

	// delete Function
	Kirby(const Kirby& _Other) = delete;
	Kirby(Kirby&& _Other) noexcept = delete;
	Kirby& operator=(const Kirby& _Other) = delete;
	Kirby& operator=(Kirby&& _Other) noexcept = delete;


	static Kirby* GetMainKirby()
	{
		return MainKirby;
	}

protected:
	static Kirby* MainKirby;


	// 상태변경 함수
	void StateUpdate(float _Delta);
	void ChangeState(KirbyState _State);
	void ChangeAnimationState(const std::string& _StateName);

	// 판정, 충돌 함수
	void KirbyDirCheck();
	void MoveHorizontal(float _Speed, float _Delta);
	void DecelerationUpdate(float _Delta);
	void DecelerationUpdate(float _Delta, float _Speed);
	void MoveUpdate(float _Delta);
	float4 GetKirbyScale();


	// 행동 시작전 함수
	void IdleStart();
	void WalkStart();
	void RunStart();
	void TurnStart();
	void JumpStart();
	void AerialMotionStart();
	void FallStart();
	void AccelerateDownStart();
	void BounceStart();
	void LandingStart();
	void LowerPostureStart();
	void LowerAttackStart();
	void HittheWallStart();
	void HittheCeilingStart();
	void TakeOffStart();
	void FlyStart();
	void ExhaleAttackStart();
	void UseSpecialAbilityStart();
	void ReleaseAbilityStart();
	void GetAbilityStart();

	void Contain_IdleStart();
	void Contain_WalkStart();
	void Contain_RunStart();
	void Contain_TurnStart();
	void Contain_JumpStart();
	void Contain_FallStart();
	void Contain_GulpStart();
	void Contain_DisgorgeStart();


	// 행동 함수
	void IdleUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void TurnUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void AerialMotionUpdate(float _Delta);
	void FallUpdate(float _Delta);
	void AccelerateDownUpdate(float _Delta);
	void BounceUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void LowerPostureUpdate(float _Delta);
	void LowerAttackUpdate(float _Delta);
	void HittheWallUpdate(float _Delta);
	void HittheCeilingUpdate(float _Delta);
	void TakeOffUpdate(float _Delta);
	void FlyUpdate(float _Delta);
	void ExhaleAttackUpdate(float _Delta);
	void UseSpecialAbilityUpdate(float _Delta);
	void ReleaseAbilityUpdate(float _Delta);
	void GetAbilityUpdate(float _Delta);

	void Contain_IdleUpdate(float _Delta);
	void Contain_WalkUpdate(float _Delta);
	void Contain_RunUpdate(float _Delta);
	void Contain_TurnUpdate(float _Delta);
	void Contain_JumpUpdate(float _Delta);
	void Contain_FallUpdate(float _Delta);
	void Contain_GulpUpdate(float _Delta);
	void Contain_DisgorgeUpdate(float _Delta);


private:
	KirbyBodyState BodyState = KirbyBodyState::Max;
	KirbyState State = KirbyState::Max;
	KirbyMode Mode = KirbyMode::Max;
	AbilityStar Star = AbilityStar::Max;
	std::string CurState = "";
	std::string CurMode = "";

	bool IsChangeState = true;
	bool IstriggerOn = false;
	bool IsBounce = false;
	bool AbleJump = true;
	bool swallowedObject = false;


	float StateTime = 0.0f;
	float Duration = 0.0f;
	float DecelerationSpeed = 1.0f;
	float CurrentJumpPower = 0.0f;
	float FallDistance = 0.0f; 
	int StarPower = 0;


	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Detla) override;

	void LevelStart() override;

	// 리소스 로드
	void Contain_StateResourceLoad();
	void Normal_StateResourceLoad();

	// 모드별 공격 함수
	void StarAttack();
	void UseAbility();
	void AcquireAbility();
	void InhaleAbility();
	void SparkAbility();

};

