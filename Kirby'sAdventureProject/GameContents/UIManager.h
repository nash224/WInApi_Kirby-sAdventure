#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>


// �ʻ�ȭ ��ġ
#define PORTRAITLOCATION float4{ 444.0f , 30.0f}



// ���� : UI�� �θ��Դϴ�. �ڽĿ��� �ʿ��� ����� �������ݴϴ�.
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
	// Start
	// ����
	GameEngineRenderer* MainUIRenderer = nullptr;
	GameEngineRenderer* PortraitRenderer = nullptr;

	GameEngineRenderer* First_LivesRenderer = nullptr;
	GameEngineRenderer* Second_LivesRenderer = nullptr;



	const float4 NumberScale = float4{ 24.0f, 24.0f };


	void HubRendererSet(const std::string& _FileName, const std::string& _Path);
	void PortraitRendererSet(const float4& _RenderPos);
	void StaminaCountRendererSet(const std::string& _FileName, const std::string& _Path, const float4& _StaminaFirstPos);
	std::vector<GameEngineRenderer*> StaminaRenderer_vec;

	size_t StaminaCount = 6;




	// Update
	static int KirbyMode;

	bool IsGulpPortraitDone = true;
	const float GulpPortraitDuration = 1.0f;
	float GulpPortraitTime = 0.0f;

	void PortraitState(float _Delta);




	static int m_KirbySteminaCount;

	void StaminaState();





	// LevelStart
	void LevelStartPortrait();
	void LevelStartLivesCount();

public:
	static int m_LivesCount;

private:
};

