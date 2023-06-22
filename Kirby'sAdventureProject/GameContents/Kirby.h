#pragma once
#include "ActorUtils.h"

#include <map>
#include <vector>
#include <string>


// 커비 몸통 및 스킬 충돌체 크기
#define FATTYPECOLLISIONSCALE float4{ 66.0f , 66.0f }
#define LOWERTYPECOLLISIONSCALE float4{ 48.0f , 27.0f }
#define LOWERATTACKCOLLISIONSCALE float4 { 30.0f , 18.0f }
#define INHALEEFFECTCOLLISIONSCALE float4 { 132.0f , 66.0f }
#define SPARKEFFECTCOLLISIONSCALE float4 { 112.0f , 112.0f }

// 커비 이동 상수
#define WALKSPEED 500.0f
#define WALKMAXSPEED 200.0f
#define DECELERATIONSPEED  600.0f
#define BRAKESPEED 1000.0f

#define RUNSPEED 600.0f
#define RUNMAXSPEED 350.0f

// 커비 점프 상수
#define JUMPTIME 0.3f
#define JUMPMAXDISTANCE 100.0f

#define FALLDISTANCE 170.0f

#define BOUNCEPOWER 250.0f


// 커비 Fly 상수
#define TAKEOFFTIME 0.4f

#define FLYPOWER 280.0f
#define FLYSPEED 500.0f
#define FLYMAXSPEED 200.0f

#define EXHALEATTACKTIME 0.08f

// 커비 벽에 부딪혔는 시간
#define HITTHEMAPTIME 0.08f

// 슬라이딩 먼지 생성 시간 간격
#define LOWERATTACKDUSTOCCURRENCECYCLE 0.08f
// 슬라이딩 감속 시작 시간
#define LOWERATTACKDECELECTIONSTARTTIME 0.3f

// 커비 능력별 쿨타임
#define KIRBYSPARKEFFECTCREATECYCLE 0.1f
#define KIRBYFRAMEEFFECTCREATECYCLE 0.1f

// 커비 데미지 상태 지속시간
#define KirbyDamagedDuration 0.2f

// 커비 무적시간
#define KIRBYIMMUNEDURATION 3.0f

// 커비 튕겨나가는 거리
#define BOUNCINGOFF_XPOWER 200.0f
#define BOUNCINGOFF_YPOWER -200.0f

// 커비 데미지 상태 시간
#define KIRBY_DAMAGED_STATETIME 0.2f


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
	ReleaseSpecialAbility,
	Enter,
	Contain_Idle,
	Contain_Walk,
	Contain_Run,
	Contain_Turn,
	Contain_Jump,
	Contain_Fall,
	Contain_Gulp,
	Contain_Disgorge,
	Contain_Damaged,
	GetAbility,
	Damaged,
	StageClear,
	StageClearAfter,
	Max,
};



class Kirby : public ActorUtils
{
	friend class UIManager;
	friend class VegetableValleyPlayLevel;

private:
	// 레벨관련
	bool IsLevelChange = true;
	size_t CurrentLevelEnemiesCount = 0;
	float4 CurrentBackGroundScale = float4::ZERO;
	std::string CurrentLevelBitMapFileName = "";
	float4 CurrentUIScale = float4::ZERO;
	float4 CameraFrontCheckPos = float4::ZERO;
	float4 CameraBackCheckPos = float4::ZERO;
	float4 PrevKirbyMovePos = float4::ZERO;
	float4 KirbyMovePos = float4::ZERO;

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

	float4 GetKirbyMovePos() const
	{
		return KirbyMovePos;
	}

	float4 GetKirbyScale();


	AbilityStar Mode = AbilityStar::Max;


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
	void VerticalUpdate(float _Delta) override;
	void ChangeKirbyBodyState(KirbyBodyState _BodyState);

	bool IsEnterPixel();



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
	void ReleaseSpecialAbilityStart();
	void GetAbilityStart();
	void DamagedStart();
	void EnterStart();
	void StageClearStart();
	void StageClearAfterStart();

	void Contain_IdleStart();
	void Contain_WalkStart();
	void Contain_RunStart();
	void Contain_TurnStart();
	void Contain_JumpStart();
	void Contain_FallStart();
	void Contain_GulpStart();
	void Contain_DisgorgeStart();
	void Contain_DamagedStart();


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
	void ReleaseSpecialAbilityUpdate(float _Delta);
	void GetAbilityUpdate(float _Delta);
	void DamagedUpdate(float _Delta);
	void EnterUpdate(float _Delta);
	void StageClearUpdate(float _Delta);
	void StageClearAfterUpdate(float _Delta);

	void Contain_IdleUpdate(float _Delta);
	void Contain_WalkUpdate(float _Delta);
	void Contain_RunUpdate(float _Delta);
	void Contain_TurnUpdate(float _Delta);
	void Contain_JumpUpdate(float _Delta);
	void Contain_FallUpdate(float _Delta);
	void Contain_GulpUpdate(float _Delta);
	void Contain_DisgorgeUpdate(float _Delta);
	void Contain_DamagedUpdate(float _Delta);


	void DropAbility();
	void CheckKirbyCollision();
	void CheckKirbyAbilityCollision(GameEngineCollision* _CheckCol);


private:
	const float GetABilityStateEndTime = 1.0f;


private:

	// 충돌체 
	GameEngineCollision* LittleCollision = nullptr;
	GameEngineCollision* LowerCollision = nullptr;
	GameEngineCollision* FatCollision = nullptr;
	GameEngineCollision* ImmuneCollision = nullptr;

	GameEngineCollision* LowerAttackCollision = nullptr;
	GameEngineCollision* InhaleEffectCollision = nullptr;

	GameEngineCollision* SparkEffectCollision = nullptr;
	GameEngineCollision* ThornEffectCollision = nullptr;


	GameEngineCollision* GetKirbyCollison();
	void KirbyBodyCollisonOn();
	void KirbyBodyCollisonOff();




	// 상태 함수
	KirbyBodyState BodyState = KirbyBodyState::Max;	
	AbilityStar CurrentAbilityStar = AbilityStar::Max;
	KirbyState State = KirbyState::Max;
	KirbyState KeepDamagedState = KirbyState::Max;
	std::string CurState = "";
	std::string CurMode = "";

	// 바운스 상태 변수
	bool IsBounce = false;


	// 상태 변수
	const float AbilityMinDuration = 1.0f;
	float Duration = 0.0f;
	float FallDistance = 0.0f; 
	float DecelerationSpeed = 1.0f;

	float FrameTime = 0.0f;




	// 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Detla) override;

	void LevelStart() override;


	// 카메라
	void CameraFocus();


	// 리소스 로드
	void Contain_StateResourceLoad();
	void Normal_StateResourceLoad();
	void Spark_StateResourceLoad();
	void Laser_StateResourceLoad();
	void Beam_StateResourceLoad();
	void Fire_StateResourceLoad();
	void Thorn_StateResourceLoad();
	//void Sword_StateResourceLoad();

	// 모드별 공격 함수
	void UseAbilityStart();
	void UseAbilityUpdate(float _Delta);


	void StarAttack();

	void InhaleAbilityStart();
	void SparkAbilityStart();
	void LaserAbilityStart();
	void BeamAbilityStart();
	void FireAbilityStart();
	void ThornAbilityStart();
	void SwordAbilityStart() {}

	void InhaleAbilityUpdate(float _Delta);
	void SparkAbilityUpdate(float _Delta);
	void LaserAbilityUpdate(float _Delta);
	void BeamAbilityUpdate(float _Delta);
	void FireAbilityUpdate(float _Delta);
	void ThornAbilityUpdate(float _Delta);
	void SwordAbilityUpdate(float _Delta) {}


	// GetAbility 함수 관련
	void TriggerOneTimeAbility();
	void TriggerMultiTimeAbility(float _Delta);

	void OneTimeSpark();
	void OneTimeLaser();
	void OneTimeBeam();
	void OneTimeThorn();


	void TriggerFireAbilityAfterProcess(float _Delta);

private:
	// 능력획득 변수
	class GetAbilityEffect* GetAbilityEffectPtr = nullptr;
	const float ContainGulpChangeStateTime = 0.6f;

	// 커비의 별 변수 
	class KirbyStar
	{
	public:
		int SwallowedEnemyNumber = 0;
		int SwallowedPowerEnemyNumber = 0;
	};

	KirbyStar Star;


	// 삼킴 상태
	ActorUtils* SwallingEnemy = nullptr;
	bool IsSwallowedtriggerOn = false;
	bool swallowedObject = false;

	bool IsGulpEnemy = false;




	// 면역 변수
	bool ImmuneState = false;
	float ImmuneTime = 0.0f; 
	
	
	void ImmuneFunc(float _Delta);


	// 레벨 이동 변수
	bool IsNextLevelTriggerOn = false;


public:
	int m_KirbyHp = 0;


private:
	// 부활
	bool IsKirbyRevive = false;



	// Fade
	const float FadeOutDuration = 0.6f;
	float FadeOutTime = 0.0f;
	bool IsFadeOut = false;
};

