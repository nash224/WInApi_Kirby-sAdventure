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

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Detla) override;


	// Enemy 상속
	void ChangeRespawnState() override;



	// this
	// FSM
	SparkyState State = SparkyState::Max;
	SparkyState RespawnState = SparkyState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(SparkyState _State);


	// 비트맵 감지
	void SetCheckPoint(const float4& _ScaleSize) override;

	float4 StairLeftBottomCheckPoint = float4::ZERO;
	float4 StairLeftTopCheckPoint = float4::ZERO;

	float4 StairRightBottomCheckPoint = float4::ZERO;
	float4 StairRightTopCheckPoint = float4::ZERO;






	// 감지 함수 
	bool IsLeftStair();
	bool IsRightStair();


	void IdleStart();
	void IdleUpdate(float _Delta);

	float CurrentJumpDistance = 0.0f;


	void FrontJumpStart();
	void FrontJumpUpdate(float _Delta);

	void StanceJumpStart();
	void StanceJumpUpdate(float _Delta);

	int RemainStanceJumpCount = 0;


	void LongJumpStart();
	void LongJumpUpdate(float _Delta);

	void LandingStart();
	void LandingUpdate(float _Delta);

	void SparkStart();
	void SparkUpdate(float _Delta);

	float SparkCoolDown = 0.0f;


	// 충돌
	void EnemyCollisionCheck();




	// 디버깅
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
	void ActorCollisionDetectionPointRender() override;

};

