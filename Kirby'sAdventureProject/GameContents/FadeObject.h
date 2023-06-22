#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class FadeObject : public GameEngineActor
{
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



public:
	void RequestFadeOut();
	void RequestFadeIn();

	bool IsFadeEnd()
	{
		if (false == IsChangeFade)
		{
			return true;
		}
		
		return false;
	}


private:
	bool IsFadeOut = false;
	bool IsChangeFade = false;
	int FadeNumber = -1;
	float ChangeFadeAlphaTime = 0.0f;
	const float ChangeFadeAlphaDuration = 0.1f;
	int AlphaCount = 0;

};

