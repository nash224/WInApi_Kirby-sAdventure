#pragma once
#include <GameEngineCore/GameEngineActor.h>





// Ό³Έν :
class UIManager : public GameEngineActor
{
public:
	static UIManager* UI;


protected:
	class Kirby* KirbyPtr = nullptr;


public:
	// constrcuter destructer
	UIManager();
	~UIManager();

	// delete Function
	UIManager(const UIManager& _Other) = delete;
	UIManager(UIManager&& _Other) noexcept = delete;
	UIManager& operator=(const UIManager& _Other) = delete;
	UIManager& operator=(UIManager&& _Other) noexcept = delete;

	float4 UIScale = float4::ZERO;

protected:
	GameEngineRenderer* MainUIRenderer = nullptr;
	GameEngineRenderer* PortraitRenderer = nullptr;

	GameEngineRenderer* First_LivesRenderer = nullptr;
	GameEngineRenderer* Second_LivesRenderer = nullptr;


	GameEngineRenderer* First_StaminaRenderer= nullptr;
	GameEngineRenderer* Second_StaminaRenderer= nullptr;
	GameEngineRenderer* Third_StaminaRenderer= nullptr;
	GameEngineRenderer* Fourth_StaminaRenderer= nullptr;
	GameEngineRenderer* Fifth_StaminaRenderer= nullptr;
	GameEngineRenderer* Sixth_StaminaRenderer= nullptr;



	void PortraitState(float _Delta);

	bool IsGulpPortraitDone = true;
	float IsGulpPortraitTime = 0.0f;
	const float IsGulpPortraitDuration = 1.0f;





	static int KirbyMode;
	static int m_LivesCount;
	static int m_KirbySteminaCount;

private:
};

