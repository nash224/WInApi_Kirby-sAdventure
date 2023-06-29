#pragma once
#include "UIManager.h"

// �̹��� �»�� ����
// ��� �ִϸ��̼� ��ġ
#define LIVESANILOCATION float4{ 573.0f , 66.0f}

// �ʻ�ȭ ��ġ
#define PORTRAITLOCATION float4{ 444.0f , 30.0f}

// ��� ���� ��ġ
#define PLAY_LIVESFIRSTNUMBERLOCATION float4{ 636.0f , 78.0f}

// ���¹̳� ��ġ
#define PLAY_STAMINAFIRSTNUMBERLOCATION float4{ 228.0f , 45.0f}

// ���� ��ġ
#define PLAY_SCOREFIRSTNUMBERLOCATION float4{ 228.0f , 102.0f}





// ���� :
class PlayUI : public UIManager
{
public:
	// ����
	static int PlayUI_ScoreNumber;

public:
	// constrcuter destructer
	PlayUI();
	~PlayUI();

	// delete Function
	PlayUI(const PlayUI& _Other) = delete;
	PlayUI(PlayUI&& _Other) noexcept = delete;
	PlayUI& operator=(const PlayUI& _Other) = delete;
	PlayUI& operator=(PlayUI&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* LivesAniRenderer = nullptr;


	std::vector<GameEngineRenderer*> ScoreRenderer_vec;



	void HubRendererSet();
	void LivesAniRendererSet();
	void PortraitRendererSet();
	void LivesNumberRendererSet();
	void StaminaCountRendererSet();
	void ScoreRendererSet();
		



	void Start() override;
	void Update(float _Delta) override;

	void LevelStart() override;

private:
	// Hp ���� ����
	bool Ouch_State = false;
	float Ouch_Time = 0.0f;
	const float Ouch_Duration = 1.0f;


	void OuchState(float _Delta);

	// Hp ���� ����
	float Increase_Hp_Time = 0.0f;
	const float Increase_Hp_Cycle = 0.12f;
	bool IsIncresing_Hp = false;


};

