#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <list>


enum class BannerState
{
	WaveHand,
	BlinkEyes,
	Max,
};


// 설명 : TitleLevel 에서 사용되는 커비 배너입니다.
class KirbyBanner : public GameEngineActor
{
public:
	// constrcuter destructer
	KirbyBanner();
	~KirbyBanner();

	// delete Function
	KirbyBanner(const KirbyBanner& _Other) = delete;
	KirbyBanner(KirbyBanner&& _Other) noexcept = delete;
	KirbyBanner& operator=(const KirbyBanner& _Other) = delete;
	KirbyBanner& operator=(KirbyBanner&& _Other) noexcept = delete;


	void init(const float4& _Pos);

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	// this
	std::string CurName = "";

	// 렌더
	GameEngineRenderer* KirbyRenderer = nullptr;



	// 상태
	BannerState CurState = BannerState::Max;

	float StateTime = 0.0f;
	bool IsStateDone = false;

	void StateUpdate(float _Delta);
	void ChangeStateAndAnimation(const std::string& _StateName);

	// State 큐
	std::list<int> StateData;
	float NextStateStart = 0.0f;

	const float StateStart_MinTime = 0.0f;
	const float StateStart_MaxTime = 1.0f;

	void State_Queue(float _Delta);


	// 손인사 패턴
	void WaveHandStart();
	void WaveHandUpdate(float _Delta);

	// 눈 깜빡 패턴
	void BlinkEyesStart();
	void BlinkEyesUpdate(float _Delta);
};

