#pragma once
#include "UIManager.h"

#include <vector>



// 이미지 좌상단 기준
// 목숨 애니메이션 위치
#define BOSS_LIVESANILOCATION float4{ 573.0f , 66.0f}


// 목숨 숫자 위치
#define BOSS_LIVESFIRSTNUMBERLOCATION float4{ 636.0f , 78.0f}

// 스태미나 위치
#define BOSS_STAMINAFIRSTNUMBERLOCATION float4{ 228.0f , 45.0f}

// 보스 스태미나 위치
#define BOSS_STAMINA_FIRSTNUMBERLOCATION float4{ 225.0f , 102.0f}


// 엔딩 패널 위치
#define BOSS_ENDINGPANEL_LOCATION float4{ 48.0f , 21.0f}


// 엔딩 패널 위치
#define BOSS_ENDINGPANEL_LOCATION float4{ 48.0f , 21.0f}





// 설명 :
class BossUI : public UIManager
{
	friend class VegetableValley13;
	friend class WhispyWood;

public:
	int UI_BossStamina = 0;

public:
	// constrcuter destructer
	BossUI();
	~BossUI();

	// delete Function
	BossUI(const BossUI& _Other) = delete;
	BossUI(BossUI&& _Other) noexcept = delete;
	BossUI& operator=(const BossUI& _Other) = delete;
	BossUI& operator=(BossUI&& _Other) noexcept = delete;



	// GameEngineObject 상속
private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart() override;
	void LevelEnd() override;




	// this
private:
	// 렌더
	GameEngineRenderer* LivesAniRenderer = nullptr;


	// Start
	void EndingRendererSet();
	void LivesAniRendererSet();
	void BossStaminaRendererSet();


	const float4 NumberScale = float4{ 24.0f, 24.0f };



	// Update
	// Ouch 상태 관련
	bool Ouch_State = false;
	float Ouch_Time = 0.0f;
	const float Ouch_Duration = 1.0f;

	void OuchState(float _Delta);




	// 보스 체력 재생 관련
	class Boss* BossPtr = nullptr;
	std::vector<GameEngineRenderer*> Boss_StaminaRenderer;
	float4 Boss_StaminaScale = float4::ZERO;
	const int Boss_MaxStaminaCount = 28;


	const float Boss_Stamina_Image_Inter = 6.0f;
	bool IsBossStaminaFull = false;
	bool Boss_Stamina_Full_Done = false;
	const float Boss_Stamina_Full_Inter = 0.1f;
	float Boss_Stamina_Full_Time = 0.0f;
	


	void BossAppearance(float _Delta);



	// 보스 스태미나 관련
	void BossStaminaState(float _Delta);



	// StarStick 관련
	bool IsChangeStarStick = false;

	void ChangePortrait_StarStick();


	// Ending 관련
	GameEngineRenderer* EndingPanelRenderer = nullptr;

	bool IsCall_ByeByePortrait = false;

	void ChangePortrait_ByeBye();



	// LevelStart
	void LevelStartStamina();
};

