#pragma once
#include "PowerEnemies.h"

#define SPARKYSPEED 150.0f
#define SPARKYDECELERATIONSPEED 800.0f

#define SPARKYGRAVITYTIMETOMAXSPEED 0.3f
#define SPARKYGRAVITYLIMIT 800.0f
#define SPARKYJUMPDISTANCE SparkyGRAVITYLIMIT


#define SPARKYIDLETIME 0.2f

#define SPARKYFRONTJUMPDISTANCE 80.0f
#define SPARKYFRONTJUMPTIME 0.05f

#define SPARKYSTANCEJUMPDISTANCE SPARKYFRONTJUMPDISTANCE
#define SPARKYSTANCEJUMPTIME SPARKYFRONTJUMPTIME

#define SPARKYLONGJUMPDISTANCE 300.0f
#define SPARKYLONGJUMPTIME 0.06f
#define SPARKYLONGJUMPSTAIRCOGNIZANCE 60.0f

#define SPARKYLANDINGTIME 0.3f


#define SPARKYABILITYTIME 3.0f
#define SPARKYSPARKFREQUENCY 0.1f
#define SPARKYSPARKCHANGEFRAMETIME 0.05f


#define SPARKY_ABILITYCOLLISIONSCALE float4{ 144.0f , 144.0f }





enum class SparkyState
{
	Idle,
	FrontJump,
	StanceJump,
	LongJump,
	Landing,
	Spark,
	BeInhaled,
	Hitted,
	Max,
};

// 설명 : 전기를 방사하는 파워몹 슬라임입니다.
class Sparky : public PowerEnemies
{
public:
	// constrcuter destructer
	Sparky();
	~Sparky();

	// delete Function
	Sparky(const Sparky& _Other) = delete;
	Sparky(Sparky&& _Other) noexcept = delete;
	Sparky& operator=(const Sparky& _Other) = delete;
	Sparky& operator=(Sparky&& _Other) noexcept = delete;

	void init(const std::string& _FileName, SparkyState _State, const float4& _Pos);

protected:
	// 상태패턴 함수
	SparkyState State = SparkyState::Max;
	SparkyState RespawnState = SparkyState::Max;

	int RemainStanceJumpCount = 0;
	float CurrentJumpDistance = 0.0f;
	float SparkCoolDown = 0.0f;

	void StateUpdate(float _Delta) override;
	void ChangeState(SparkyState _State);
	void ChangeRespawnState() override;


	// 감지 함수 
	bool IsLeftStair();
	bool IsRightStair();


	void IdleStart();
	void FrontJumpStart();
	void StanceJumpStart();
	void LongJumpStart();
	void LandingStart();
	void SparkStart();

	void IdleUpdate(float _Delta);
	void FrontJumpUpdate(float _Delta);
	void StanceJumpUpdate(float _Delta);
	void LongJumpUpdate(float _Delta);
	void LandingUpdate(float _Delta);
	void SparkUpdate(float _Delta);



	void EnemyCollisionCheck();


private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Detla) override;


	// 계단을 점프해서 오르기 위한 추가 로직
	float4 StairLeftBottomCheckPoint = float4::ZERO;
	float4 StairLeftTopCheckPoint = float4::ZERO;

	float4 StairRightBottomCheckPoint = float4::ZERO;
	float4 StairRightTopCheckPoint = float4::ZERO;

	void SetCheckPoint(const float4& _ScaleSize) override;
	void ActorCollisionDetectionPointRender() override;


};

