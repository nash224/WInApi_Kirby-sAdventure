#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FadeObject : public GameEngineActor
{
public:
	static bool IsFadeScreenRelease;
	static bool IsFadeDone;


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


	bool IsFadeEnd()
	{
		if (false == IsChangeFade)
		{
			return true;
		}
		
		return false;
	}




private:
	// Fade In & Out 
	bool IsFadeOut = false;
	bool IsChangeFade = false;
	bool IsChangeWhiteFade = false;
	int FadeNumber = -1;
	float ChangeFadeAlphaTime = 0.0f;
	const float ChangeFadeAlphaDuration = 0.12f;
	int AlphaCount = 0;


	void FadeOut(float _Delta);
	void FadeIn(float _Delta);

	void White_FadeOut(float _Delta);
	void White_FadeIn(float _Delta);


	// FadeScreen
	bool IsFadeScreen = false;

	void FadeScreen(float _Delta);

};

