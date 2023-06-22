#pragma once
#include "Boss.h"

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
class WhispyWood : public Boss
{
	friend class BossUI;

	static WhispyWood* WhispyWoodPtr;
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
	// 상태패턴 함수
	WhispyWoodState State = WhispyWoodState::Max;




	void StateUpdate(float _Delta) override;
	void ChangeState(WhispyWoodState _State);


	void IdleStart();
	void SummonAppleStart();
	void WhispyStart();
	void FrownStart();
	void KaonashiStart();
	void CryingFaceStart();


	void IdleUpdate(float _Delta);
	void SummonAppleUpdate(float _Delta);
	void WhispyUpdate(float _Delta);
	void FrownUpdate(float _Delta);
	void KaonashiUpdate(float _Delta);
	void CryingFaceUpdate(float _Delta);


	void EnemyCollisionCheck();


private:
	class BossUI* BossUIPtr = nullptr;
	int m_BossHp = 28;

	bool IsBossFindKirby = false;
	const float BossFindPlayer_Y_Distance = 500.0f;


	static WhispyWood* GetWhispyWoodPtr()
	{
		return WhispyWoodPtr;
	}



private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void LevelStart() override;

};

