#pragma once
#include "ActorUtils.h"

#include <GameEnginePlatform/GameEngineSound.h>

#include <map>
#include <list>
#include <string>




// 커비 몸통 및 스킬 충돌체 크기
#define FATTYPECOLLISIONSCALE float4{ 66.0f , 66.0f }
#define LOWERTYPECOLLISIONSCALE float4{ 48.0f , 27.0f }
#define LOWERATTACKCOLLISIONSCALE float4 { 30.0f , 18.0f }
#define INHALEEFFECTCOLLISIONSCALE float4 { 132.0f , 66.0f }
#define SPARKEFFECTCOLLISIONSCALE float4 { 112.0f , 112.0f }
#define SWORDEFFECTCOLLISIONSCALE float4 { 182.0f , 100.0f }
#define AERIALSWORDEFFECTCOLLISIONSCALE float4 { 96.0f , 96.0f }

// 커비 이동 상수
#define WALKSPEED 500.0f
#define WALKMAXSPEED 200.0f
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
#define KIRBYICEBREATH_EFFECTCREATECYCLE 0.15f

// 커비 데미지 상태 지속시간
#define KirbyDamagedDuration 0.2f

// 커비 무적시간
#define KIRBYIMMUNEDURATION 2.0f

// 커비 튕겨나가는 거리
#define BOUNCINGOFF_XPOWER 200.0f
#define BOUNCINGOFF_YPOWER -200.0f

// 커비 데미지 상태 시간
#define KIRBY_DAMAGED_STATETIME 0.2f

// 커비 Miss
#define KIRBY_MISS_STATETIME 2.0f


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
	AerialUseSpecialAbility,
	ReleaseSpecialAbility,
	Enter,
	OpenDoorAndRaiseFlag,
	OpenDoorAndRaiseFlagAfter,
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
	StageClearWalk,
	StageClear,
	Performance,
	Miss,
	MissRaiseUp,
	Max,
};



class IceBlock;
class Kirby : public ActorUtils
{
	friend class UIManager;
	friend class VegetableValleyPlayLevel;
	friend class Item;

public:
	static Kirby* GetMainKirby()
	{
		return MainKirby;
	}

	float4 GetKirbyMovePos() const
	{
		return KirbyMovePos;
	}


	bool IsReachedStarStick = false;


private:
	static Kirby* MainKirby;


	// 레벨관련
	float4 CurrentBackGroundScale = float4::ZERO;
	std::string CurrentLevelBitMapFileName = "";
	float4 CurrentUIScale = float4::ZERO;
	size_t CurrentLevelEnemiesCount = 0;

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


	float4 GetKirbyScale();

	AbilityStar Mode = AbilityStar::Max;

	int m_KirbyHp = 0;


protected:


private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Detla) override;


	// GameEngineLevel 상속
	void LevelStart() override;
	void LevelEnd() override;


private:
	class UIManager* UIManagerPtr = nullptr;



	// 리소스 로드
	void Contain_StateResourceLoad();
	void Normal_StateResourceLoad();
	void Spark_StateResourceLoad();
	void Laser_StateResourceLoad();
	void Beam_StateResourceLoad();
	void Fire_StateResourceLoad();
	void Thorn_StateResourceLoad();
	void Sword_StateResourceLoad();
	void Ice_StateResourceLoad();
	void MoveLevel_StateResourceLoad();




	// 감지, 비트맵
	void KirbyDirCheck();
	void MoveHorizontal(float _Speed, float _Delta);
	void DecelerationUpdate(float _Delta);
	void HorizontalUpdate(float _Delta) override;
	void VerticalUpdate(float _Delta) override;
	void ChangeKirbyBodyState(KirbyBodyState _BodyState);
	bool IsEnterPixel();




	// FSM
	void StateUpdate(float _Delta);
	void ChangeState(KirbyState _State);
	void ChangeAnimationState(const std::string& _StateName, int _StartFrame = 0);


	KirbyState State = KirbyState::Max;
	KirbyBodyState BodyState = KirbyBodyState::Max;
	std::string CurState = "";
	std::string CurMode = "";

	const float DecelerationSpeed = 600.0f;
	float Duration = 0.0f;



	// Basic Pattern
	void IdleStart();
	void IdleUpdate(float _Delta);


	void WalkStart();
	void WalkUpdate(float _Delta);


	void RunStart();
	void RunUpdate(float _Delta);


	void TurnStart();
	void TurnUpdate(float _Delta);


	void JumpStart();
	void JumpUpdate(float _Delta);


	void AerialMotionStart();
	void AerialMotionUpdate(float _Delta);


	void FallStart();
	void FallUpdate(float _Delta);

	float FallDistance = 0.0f;



	void AccelerateDownStart();
	void AccelerateDownUpdate(float _Delta);


	void BounceStart();
	void BounceUpdate(float _Delta);

	bool IsBounce = false;



	void LandingStart();
	void LandingUpdate(float _Delta);

	void LowerPostureStart();
	void LowerPostureUpdate(float _Delta);

	void LowerAttackStart();
	void LowerAttackUpdate(float _Delta);

	void HittheWallStart();
	void HittheWallUpdate(float _Delta);

	void HittheCeilingStart();
	void HittheCeilingUpdate(float _Delta);

	void TakeOffStart();
	void TakeOffUpdate(float _Delta);

	void FlyStart();
	void FlyUpdate(float _Delta);

	void ExhaleAttackStart();
	void ExhaleAttackUpdate(float _Delta); 

	void DamagedStart();
	void DamagedUpdate(float _Delta);

	AbilityStar KeepMode = AbilityStar::Max;
	KirbyState KeepDamagedState = KirbyState::Max;

	// Damaged Pattern :: Immune
	bool ImmuneState = false;
	float ImmuneTime = 0.0f;

	void ImmuneFunc(float _Delta);



	// GetAbility Pattern
	void GetAbilityStart();
	void GetAbilityUpdate(float _Delta);

	const float GetABilityStateEndTime = 1.0f;
	bool GettingAbility = false;
	class GetAbilityEffect* GetAbilityEffectPtr = nullptr;

	int FadeAlphaValue = 70;


	void TriggerOneTimeAbility();


	// GetAbility Pattern :: Mode
	void OneTimeSpark();
	void OneTimeLaser();
	void OneTimeBeam();
	void OneTimeThorn();



	void TriggerMultiTimeAbility(float _Delta);

	void TriggerFireAbilityAfterProcess(float _Delta);
	void TriggerSparkAbilityAfterProcess(float _Delta);
	void TriggerIceAbilityAfterProcess(float _Delta);




	// Ability Pattern
	void UseSpecialAbilityStart(); 
	void UseSpecialAbilityUpdate(float _Delta);


	void AerialUseSpecialAbilityStart();
	void AerialUseSpecialAbilityUpdate(float _Delta);

	void UseSpecialAbilityShorCut();


	// Ability Pattern :: Attack
	void UseAbilityStart();
	void UseAbilityUpdate(float _Delta);

	const float AbilityMinDuration = 1.0f;


	void InhaleAbilityStart();
	void InhaleAbilityUpdate(float _Delta);

	GameEngineSoundPlayer InhaleSound;


	// 커비의 별 변수 
	class KirbyStar
	{
	public:
		int SwallowedEnemyNumber = 0;
		int SwallowedPowerEnemyNumber = 0;
	};

	KirbyStar Star;

	ActorUtils* SwallingEnemy = nullptr;
	const float Swallowed_Distance = 5.0f;




	void SparkAbilityStart();
	void SparkAbilityUpdate(float _Delta);

	float SparkTime = 0.0f;


	void LaserAbilityStart();
	void LaserAbilityUpdate(float _Delta);


	void BeamAbilityStart();
	void BeamAbilityUpdate(float _Delta);


	void FireAbilityStart();
	void FireAbilityUpdate(float _Delta);

	float FrameTime = 0.0f;


	void ThornAbilityStart();
	void ThornAbilityUpdate(float _Delta);


	void SwordAbilityStart();
	void SwordAbilityUpdate(float _Delta);


	void IceAbilityStart();
	void IceAbilityUpdate(float _Delta);

	float IceTime = 0.0f;
	float IceSoundTime = 0.0f;
	const float IceSoundCycle = 0.6f;

	std::list<IceBlock*> IceBlockPtr_list;

public:
	std::list<IceBlock*>& GetIceList()
	{
		return IceBlockPtr_list;
	}


private:

	void ReleaseSpecialAbilityStart();
	void ReleaseSpecialAbilityUpdate(float _Delta);


	void DropAbility();



	// Enter And Event Pettern
	void EnterStart();
	void EnterUpdate(float _Delta);

	bool IsEnterCheck = false;
	bool IsNextLevelTriggerOn = false;


	void OpenDoorAndRaiseFlagStart();
	void OpenDoorAndRaiseFlagUpdate(float _Delta);

	bool IsKirbyOpenedDoor = false;
	bool IsKirbyClosedDoor = false;
	bool IsCheckRaiseUpWithFlag = false;

public:
	// OpenDoorAndRaiseFlag 상태 관련
	static bool IsKirbyOpenDoorToLevel;
	static bool IsKirbyCloseDoorToLevel;


private:
	void OpenDoorAndRaiseFlagAfterStart();
	void OpenDoorAndRaiseFlagAfterUpdate(float _Delta);


	void StageClearWalkStart();
	void StageClearWalkUpdate(float _Delta);


	const float StageClear_WalkingScalar = 100.0f;
	float StageClear_X_CenterPos = 0.0f;



	void StageClearStart();
	void StageClearUpdate(float _Delta);

	GameEngineRenderer* Left_KirbyRenderer = nullptr;
	GameEngineRenderer* Right_KirbyRenderer = nullptr;

	const float StageClear_KirbyBackUpDancer_RenderInter = 120.0f;



	void PerformanceStart();
	void PerformanceUpdate(float _Delta);

	float Kirby_Performance_StartXPos = 0.0f;

	const float Performance_0_7_Duration = 0.15f;
	const float Performance_15_17_MovePos = 200.0f;
	bool IsPerformance_17Frames_FallStartTime = false;

	float Kirby_SetFinishPos = 0.0f;
	bool IsKirby_FinishPosCheck = false;




	void MissStart();
	void MissUpdate(float _Delta);

	void MissRaiseUpStart();
	void MissRaiseUpUpdate(float _Delta);

	bool IsMissCheck = false;
	bool IsKirbyRevive = false;




	// Normal Contain Pattern
	void Contain_IdleStart();
	void Contain_IdleUpdate(float _Delta);


	void Contain_WalkStart();
	void Contain_WalkUpdate(float _Delta);


	void Contain_RunStart();
	void Contain_RunUpdate(float _Delta);


	void Contain_TurnStart();
	void Contain_TurnUpdate(float _Delta);


	void Contain_JumpStart();
	void Contain_JumpUpdate(float _Delta);


	void Contain_FallStart();
	void Contain_FallUpdate(float _Delta);


	void Contain_GulpStart();
	void Contain_GulpUpdate(float _Delta);

	AbilityStar CurrentAbilityStar = AbilityStar::Max;

	// Portrait Relation
	bool IsGulpEnemy = false;


	void Contain_DisgorgeStart();
	void Contain_DisgorgeUpdate(float _Delta);

	void StarAttack();


	void Contain_DamagedStart();
	void Contain_DamagedUpdate(float _Delta);




private:
	// 충돌
	GameEngineCollision* LittleCollision = nullptr;
	GameEngineCollision* LowerCollision = nullptr;
	GameEngineCollision* FatCollision = nullptr;
	GameEngineCollision* ImmuneCollision = nullptr;

	GameEngineCollision* LowerAttackCollision = nullptr;
	GameEngineCollision* InhaleEffectCollision = nullptr;

	GameEngineCollision* SparkEffectCollision = nullptr;
	GameEngineCollision* ThornEffectCollision = nullptr;
	GameEngineCollision* SwordEffectCollision = nullptr;
	GameEngineCollision* AerialSwordEffectCollision = nullptr;


	GameEngineCollision* GetKirbyCollison();
	void KirbyBodyCollisonOn();
	void KirbyBodyCollisonOff();

	void CheckKirbyCollision();
	void CheckKirbyAbilityCollision(GameEngineCollision* _CheckCol, int _Damage = 1);
	void CheckKirbyAbilityToBossCollision(GameEngineCollision* _CheckCol, int _Damage = 1);



	// 커비 숏컷
	void KirbysDebugShortcut(float _Delta);


	// 디버깅
	void KirbyDebugRender(HDC _dc);
	void ThisDebugRender(HDC _dc);
	void KeyDownRender(HDC _dc);

	float4 KeyDownPos = float4{ 360.0f , 470.0f };
	
	// 치트
	bool Cheat_Invincibility = false;
	bool Cheat_NoneBodyCollision = false;

	void SwitchNoneBodyCollision();

};

