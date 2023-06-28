#pragma once
#include "ActorUtils.h"

#include <GameEnginePlatform/GameEngineSound.h>

#include <map>
#include <vector>
#include <string>


#define MAX_VOLUME_AMOUNT 1.0f


// Ŀ�� ���� �� ��ų �浹ü ũ��
#define FATTYPECOLLISIONSCALE float4{ 66.0f , 66.0f }
#define LOWERTYPECOLLISIONSCALE float4{ 48.0f , 27.0f }
#define LOWERATTACKCOLLISIONSCALE float4 { 30.0f , 18.0f }
#define INHALEEFFECTCOLLISIONSCALE float4 { 132.0f , 66.0f }
#define SPARKEFFECTCOLLISIONSCALE float4 { 112.0f , 112.0f }

// Ŀ�� �̵� ���
#define WALKSPEED 500.0f
#define WALKMAXSPEED 200.0f
#define DECELERATIONSPEED  600.0f
#define BRAKESPEED 1000.0f

#define RUNSPEED 600.0f
#define RUNMAXSPEED 350.0f

// Ŀ�� ���� ���
#define JUMPTIME 0.3f
#define JUMPMAXDISTANCE 100.0f

#define FALLDISTANCE 170.0f

#define BOUNCEPOWER 250.0f


// Ŀ�� Fly ���
#define TAKEOFFTIME 0.4f

#define FLYPOWER 280.0f
#define FLYSPEED 500.0f
#define FLYMAXSPEED 200.0f

#define EXHALEATTACKTIME 0.08f

// Ŀ�� ���� �ε����� �ð�
#define HITTHEMAPTIME 0.08f

// �����̵� ���� ���� �ð� ����
#define LOWERATTACKDUSTOCCURRENCECYCLE 0.08f
// �����̵� ���� ���� �ð�
#define LOWERATTACKDECELECTIONSTARTTIME 0.3f

// Ŀ�� �ɷº� ��Ÿ��
#define KIRBYSPARKEFFECTCREATECYCLE 0.1f
#define KIRBYFRAMEEFFECTCREATECYCLE 0.1f

// Ŀ�� ������ ���� ���ӽð�
#define KirbyDamagedDuration 0.2f

// Ŀ�� �����ð�
#define KIRBYIMMUNEDURATION 2.0f

// Ŀ�� ƨ�ܳ����� �Ÿ�
#define BOUNCINGOFF_XPOWER 200.0f
#define BOUNCINGOFF_YPOWER -200.0f

// Ŀ�� ������ ���� �ð�
#define KIRBY_DAMAGED_STATETIME 0.2f

// Ŀ�� Miss
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



class Kirby : public ActorUtils
{
	friend class UIManager;
	friend class VegetableValleyPlayLevel;
	friend class Item;

private:
	// ��������
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


	// Ŀ�� ����
	static float SoundVol;
	float SoundVolPressKeyTime = 0.0f;
	const float SoundVol_OneTime_AmountOfChange = 0.05f;
	const float SoundVol_KeyDownCycle = 0.2f;
	

	void KirbysDebugShortcut(float _Delta);



	// ���º��� �Լ�
	void StateUpdate(float _Delta);
	void ChangeState(KirbyState _State);
	void ChangeAnimationState(const std::string& _StateName, int _StartFrame = 0);

	// ����, �浹 �Լ�
	void KirbyDirCheck();
	void MoveHorizontal(float _Speed, float _Delta);
	void DecelerationUpdate(float _Delta);
	void HorizontalUpdate(float _Delta) override;
	void VerticalUpdate(float _Delta) override;
	void ChangeKirbyBodyState(KirbyBodyState _BodyState);

	bool IsEnterPixel();



	// �ൿ ������ �Լ�
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
	void OpenDoorAndRaiseFlagStart();
	void OpenDoorAndRaiseFlagAfterStart();
	void StageClearWalkStart();
	void StageClearStart();
	void PerformanceStart();
	void MissStart();
	void MissRaiseUpStart();

	void Contain_IdleStart();
	void Contain_WalkStart();
	void Contain_RunStart();
	void Contain_TurnStart();
	void Contain_JumpStart();
	void Contain_FallStart();
	void Contain_GulpStart();
	void Contain_DisgorgeStart();
	void Contain_DamagedStart();


	// �ൿ �Լ�
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
	void OpenDoorAndRaiseFlagUpdate(float _Delta);
	void OpenDoorAndRaiseFlagAfterUpdate(float _Delta);
	void StageClearWalkUpdate(float _Delta);
	void StageClearUpdate(float _Delta);
	void PerformanceUpdate(float _Delta);
	void MissUpdate(float _Delta);
	void MissRaiseUpUpdate(float _Delta);

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
	void CheckKirbyAbilityCollision(GameEngineCollision* _CheckCol, int _Damage = 1);
	void CheckKirbyAbilityToBossCollision(GameEngineCollision* _CheckCol, int _Damage = 1);


private:
	const float GetABilityStateEndTime = 1.0f;


private:

	// �浹ü ����
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




	// ���� �Լ�
	KirbyBodyState BodyState = KirbyBodyState::Max;	
	AbilityStar CurrentAbilityStar = AbilityStar::Max;
	KirbyState State = KirbyState::Max;
	KirbyState KeepDamagedState = KirbyState::Max;
	std::string CurState = "";
	std::string CurMode = "";

	// �ٿ ���� ����
	bool IsBounce = false;


	// ���� ����
	const float AbilityMinDuration = 1.0f;
	float Duration = 0.0f;
	float FallDistance = 0.0f; 
	float DecelerationSpeed = 1.0f;

	float FrameTime = 0.0f;
	float SparkTime = 0.0f;




	// ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Detla) override;

	void LevelStart() override;


	// ī�޶�
	static float Camera_ShakeMagnitude;
	static int Camera_ShakeCount;
	int Camera_ShakeNumber = 0;

	const float Camera_ShakeCycle = 0.04f;
	float Camera_ShakeTime = 0.0f;

public:
	static void RequestShakeCountToKirby(size_t _Value = 1)
	{
		for (size_t i = 0; i < _Value; i++)
		{
			++Camera_ShakeCount;
		}
	}

	static void RequestShakeMagnitudeToKirby(float _Value = 3.0f)
	{
		Camera_ShakeMagnitude = _Value;
	}

private:
	void CameraFocus(float _Delta);



	// ���ҽ� �ε�
	void Contain_StateResourceLoad();
	void Normal_StateResourceLoad();
	void Spark_StateResourceLoad();
	void Laser_StateResourceLoad();
	void Beam_StateResourceLoad();
	void Fire_StateResourceLoad();
	void Thorn_StateResourceLoad();
	//void Sword_StateResourceLoad();
	void MoveLevel_StateResourceLoad();

	// ��庰 ���� �Լ�
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


	// GetAbility �Լ� ����
	void TriggerOneTimeAbility();
	void TriggerMultiTimeAbility(float _Delta);

	void OneTimeSpark();
	void OneTimeLaser();
	void OneTimeBeam();
	void OneTimeThorn();


	void TriggerFireAbilityAfterProcess(float _Delta);
	void TriggerSparkAbilityAfterProcess(float _Delta);

private:
	// �ɷ�ȹ�� ����
	class GetAbilityEffect* GetAbilityEffectPtr = nullptr;
	const float ContainGulpChangeStateTime = 0.6f;

	// Ŀ���� �� ���� 
	class KirbyStar
	{
	public:
		int SwallowedEnemyNumber = 0;
		int SwallowedPowerEnemyNumber = 0;
	};

	KirbyStar Star;


	// ��Ŵ ����
	ActorUtils* SwallingEnemy = nullptr;
	bool IsSwallowedtriggerOn = false;
	bool swallowedObject = false;
	bool KirbySwalling = false;

	bool IsGulpEnemy = false;
	const float Swallowed_Distance = 10.0f;

	bool GettingAbility = false;




	// �鿪 ����
	bool ImmuneState = false;
	float ImmuneTime = 0.0f; 
	
	
	void ImmuneFunc(float _Delta);


	// ���� �̵� ����
	bool IsNextLevelTriggerOn = false;


public:
	int m_KirbyHp = 0;





private:
	// Death ���� ����


	// ��Ȱ
	bool IsKirbyRevive = false;



	// Fade
	const float FadeOutDuration = 0.6f;
	float FadeOutTime = 0.0f;



public:
	// Fade Out & In, FadeScreen ����
	bool IsFadeOut = false;
	bool IsKirby_FadeRequest = false;
	bool IsFadeScreenRelease = false;

	int FadeAlphaValue = 70;



	// ������ ����
	bool IsReachedStarStick = false;


	// OpenDoorAndRaiseFlag ���� ����
public:
	static bool IsKirbyOpenDoorToLevel;
	static bool IsKirbyCloseDoorToLevel;

private:
	bool IsKirbyOpenedDoor = false;
	bool IsKirbyClosedDoor = false;
	bool IsCheckRaiseUpWithFlag = false;



	// StageClear ���� ����
	const float StageClear_WalkingScalar = 100.0f;
	float StageClear_X_CenterPos = 0.0f;



	// Performance ���� ����
	GameEngineRenderer* Left_KirbyRenderer = nullptr;
	GameEngineRenderer* Right_KirbyRenderer = nullptr;

	const float KirbyAndEgo_Inter = 100.0f;

	bool IsPerformance_17Frames_FallStartTime = false;
	float Kirby_Performance_StartXPos = 0.0f;
	bool IsKirby_FinishPosCheck = false;
	float Kirby_SetFinishPos = 0.0f;



	// ���� ����
	GameEngineSoundPlayer InhaleSound;

	// ġƮ
	bool Cheat_Invincibility = false;
};

