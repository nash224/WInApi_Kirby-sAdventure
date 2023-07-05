#pragma once
#include "Boss.h"


#include <list>


#define WHISPYWOOD_SCALE float4{ 144.0f , 264.0f }
#define WHISPYWOOD_RESPAWNLOCATION float4 { 600.0f , 621.0f }



enum class WhispyWoodState
{
	Idle,
	SummonApple,
	Whispy,
	Frown,
	Kaonashi,
	CryingFace,
	Max,
};


// 설명 : 1스테이지 마왕군단 초 정예병 휫파람 괴물 나무 보스입니다.
class Apple;
class Boss_WhispyEffect;
class WhispyWood : public Boss
{
	friend class BossUI;
	friend class Apple;
	friend class Boss_WhispyEffect;

private:
	static WhispyWood* WhispyWoodPtr;

public:
	static WhispyWood* GetWhispyWoodPtr()
	{
		return WhispyWoodPtr;
	}

private:
	std::list<Apple*> WhispyApple_list;
	std::list<Boss_WhispyEffect*> WhispyEffect_list;


	std::list<Apple*>& GetAppleList()
	{
		return WhispyApple_list;
	}

	std::list<Boss_WhispyEffect*>& GetWhispyList()
	{
		return WhispyEffect_list;
	}

public:
	// constrcuter destructer
	WhispyWood();
	~WhispyWood();

	// delete Function
	WhispyWood(const WhispyWood& _Other) = delete;
	WhispyWood(WhispyWood&& _Other) noexcept = delete;
	WhispyWood& operator=(const WhispyWood& _Other) = delete;
	WhispyWood& operator=(WhispyWood&& _Other) noexcept = delete;


private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// GameEngineLevel 상속
	void LevelStart() override;
	void LevelEnd() override;


	// this
	// FSM
	WhispyWoodState State = WhispyWoodState::Max;
	WhispyWoodState PrevState = WhispyWoodState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(WhispyWoodState _State);



	// 상태
	void IdleStart();
	void IdleUpdate(float _Delta);

	const float BossFindPlayer_Y_Distance = 500.0f;


	void SummonAppleStart();
	void SummonAppleUpdate(float _Delta);

	bool IsCharge_SummonAppleCount = false;
	bool IsReCharge_SummonAppleCount = false;
	int TwinkleCount = 0;
	int SummonAppleCount = 0;
	float SummonAppleTime = 0.0f;
	const float SummonAppleDuration = 1.2f;
	const float SummonApple_Height = 250.0f;
	const float SummonApple_Min_Width = 60.0f;
	const float SummonApple_Max_Width = 460.0f;


	void WhispyStart();
	void WhispyUpdate(float _Delta);

	int Whispy_RemainCount = -1;
	const float Whispy_FireCycle = 0.4f;
	float Whispy_ReChargeTime = 0.0f;


	void FrownStart();
	void FrownUpdate(float _Delta);

	bool IsImmune = false;

	void KaonashiStart();
	void KaonashiUpdate(float _Delta);

	void CryingFaceStart();
	void CryingFaceUpdate(float _Delta);

	const float4 StickTargetPos = float4{ 288.0f , 415.0f };


	// 충돌
	void EnemyCollisionCheck();





	// 디버깅
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);

	// 보스 숏컷
	void DebugShortcut();
};

