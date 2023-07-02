#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>


// 초상화 위치
#define PORTRAITLOCATION float4{ 444.0f , 30.0f}



// 설명 :
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

	std::vector<GameEngineRenderer*> StaminaRenderer_vec;


	const float4 NumberScale = float4{ 24.0f, 24.0f };




	void PortraitRendererSet(const float4& _RenderPos);

	void LevelStartPortrait();


	void PortraitState(float _Delta);
	void StaminaState();

	bool IsGulpPortraitDone = true;
	float IsGulpPortraitTime = 0.0f;
	const float IsGulpPortraitDuration = 1.0f;

	const float StaminaFramesInter = 0.6f;


	static int KirbyMode;
	static int m_KirbySteminaCount;

public:
	static int m_LivesCount;

private:
};

