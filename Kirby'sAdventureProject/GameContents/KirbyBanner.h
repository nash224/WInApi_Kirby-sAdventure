#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <list>


enum class BannerState
{
	WaveHand,
	BlinkEyes,
	Max,
};


// ���� : TitleLevel ���� ���Ǵ� Ŀ�� ����Դϴ�.
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
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


private:
	// this
	std::string CurName = "";

	// ����
	GameEngineRenderer* KirbyRenderer = nullptr;



	// ����
	BannerState CurState = BannerState::Max;

	float StateTime = 0.0f;
	bool IsStateDone = false;

	void StateUpdate(float _Delta);
	void ChangeStateAndAnimation(const std::string& _StateName);

	// State ť
	std::list<int> StateData;
	float NextStateStart = 0.0f;

	const float StateStart_MinTime = 0.0f;
	const float StateStart_MaxTime = 1.0f;

	void State_Queue(float _Delta);


	// ���λ� ����
	void WaveHandStart();
	void WaveHandUpdate(float _Delta);

	// �� ���� ����
	void BlinkEyesStart();
	void BlinkEyesUpdate(float _Delta);
};

