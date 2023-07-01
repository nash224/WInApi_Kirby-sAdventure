#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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
	GameEngineRenderer* MainRenderer = nullptr;

private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;



public:
	void RequestFadeOut();
	void RequestFadeIn();
	void Request_WhiteFadeIn();
	void Request_WhiteFadeOut();

	void RequestFadeScreen(int _AlphaCount = 0);



private:
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

