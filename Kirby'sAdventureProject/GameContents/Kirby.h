#pragma once
#include "ActorUtils.h"

#include <map>
#include <string>

#define FATTYPECOLLISIONSCALE float4{ 66.0f , 66.0f }
#define LOWERTYPECOLLISIONSCALE float4{ 48.0f , 27.0f }
#define LOWERATTACKCOLLISIONSCALE float4 { 30.0f , 18.0f }

#define WALKSPEED 500.0f
#define WALKMAXSPEED 200.0f
#define DECELERATIONSPEED  600.0f
#define BRAKESPEED 1000.0f

#define RUNSPEED 600.0f
#define RUNMAXSPEED 350.0f

#define JUMPTIME 0.3f
#define JUMPMAXDISTANCE 100.0f

#define FALLDISTANCE 170.0f

#define BOUNCEPOWER 250.0f


#define TAKEOFFTIME 0.4f

#define FLYPOWER 280.0f
#define FLYSPEED 500.0f
#define FLYMAXSPEED 200.0f

#define EXHALEATTACKTIME 0.08f


#define HITTHEMAPTIME 0.08f

#define LOWERATTACKDUSTOCCURRENCECYCLE 0.08f



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
	void ChangeAnimationState(const std::string& _StateName, int _StartFrame = 0);

	// 감지, 충돌 함수
	void KirbyDirCheck();
	void MoveHorizontal(float _Speed, float _Delta);
	void DecelerationUpdate(float _Delta);
	void HorizontalUpdate(float _Delta) override;
	float4 GetKirbyScale();
	void ChangeKirbyBodyState(KirbyBodyState _BodyState);


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

	void DropAbility();


private:
	GameEngineCollision* LittleCollision = nullptr;
	GameEngineCollision* LowerCollision = nullptr;
	GameEngineCollision* FatCollision = nullptr;
	GameEngineCollision* LowerAttackCollision = nullptr;
	KirbyBodyState BodyState = KirbyBodyState::Max;
	KirbyState State = KirbyState::Max;
	KirbyMode Mode = KirbyMode::Max;
	AbilityStar Star = AbilityStar::Max;
	std::string CurState = "";
	std::string CurMode = "";

	bool IstriggerOn = false;
	bool IsBounce = false;
	bool swallowedObject = false;


	float Duration = 0.0f;
	float DecelerationSpeed = 1.0f;
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
	void UseAbility(float _Delta);
	void AcquireAbility();
	void InhaleAbility(float _Delta);
	void SparkAbility(float _Delta);

private:

	class KirbyStar
	{
	public:
		bool IsStarBreak = true;
		bool IsSwallowedPowerEnemy = false;
		int SwallowedEnemyNumber = 0;
		int StarDamage = 0;

	};
};

