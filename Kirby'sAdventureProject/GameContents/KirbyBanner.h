#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <list>


enum class BannerState
{
	WaveHand,
	BlinkEyes,
	Max,
};

// 설명 :
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
	GameEngineRenderer* KirbyRenderer = nullptr;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	BannerState CurState = BannerState::Max;
	std::string CurName = "";



	// 상태
	float StateTime = 0.0f;
	float NextStateStart = 0.0f;

	const float StateStart_MinTime = 0.0f;
	const float StateStart_MaxTime = 2.0f;



	// State 큐
	bool IsStateDone = false;
	std::list<int> StateData;

	void State_Queue(float _Delta);
	void ChangeStateAndAnimation(const std::string& _StateName);

	void WaveHandStart();
	void BlinkEyesStart();



	void StateUpdate(float _Delta);
	void WaveHandUpdate(float _Delta);
	void BlinkEyesUpdate(float _Delta);
};

