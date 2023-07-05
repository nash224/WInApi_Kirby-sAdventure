#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 전역 레벨에서 사용하는 Fade Object 입니다.
// 레벨 이동할 때 점점 사라지는 효과를 내거나, 화면 명도를 조절할 수 있습니다.
class FadeObject : public GameEngineActor
{
public:
	static bool IsFadeOutScreenRelease;
	static bool IsFadeScreenRelease;
	static bool IsFadeInDone;

private:
	static float TimeRaito;

public:
	static void SetTimeRaito(float _Ratio)
	{
		TimeRaito = _Ratio;
	}


public:
	// constrcuter destructer
	FadeObject();
	~FadeObject();

	// delete Function
	FadeObject(const FadeObject& _Other) = delete;
	FadeObject(FadeObject&& _Other) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;



protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;



public:
	// 요청
	void RequestFadeOut();
	void RequestFadeIn();
	void Request_WhiteFadeIn();
	void Request_WhiteFadeOut();

	void RequestFadeScreen(int _AlphaCount = 0);



private:
	// 렌더
	GameEngineRenderer* MainRenderer = nullptr;

	// Fade In & Out 
	bool IsFadeOut = false;
	bool IsChangeFade = false;
	bool IsChangeWhiteFade = false;
	int FadeNumber = -1;
	float ChangeFadeAlphaTime = 0.0f;
	const float ChangeFadeOutAlphaDuration = 0.12f;
	const float ChangeFadeInAlphaDuration = 0.2f;
	int AlphaCount = 0;


	void FadeOut(float _Delta);
	void FadeIn(float _Delta);



	// FadeScreen
	bool IsFadeScreen = false;

	void FadeScreen(float _Delta);

};

