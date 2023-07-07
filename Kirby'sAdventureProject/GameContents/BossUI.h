#pragma once
#include "UIManager.h"

#include <vector>



// �̹��� �»�� ����
// ��� �ִϸ��̼� ��ġ
#define BOSS_LIVESANILOCATION float4{ 573.0f , 66.0f}


// ��� ���� ��ġ
#define BOSS_LIVESFIRSTNUMBERLOCATION float4{ 636.0f , 78.0f}

// ���¹̳� ��ġ
#define BOSS_STAMINAFIRSTNUMBERLOCATION float4{ 228.0f , 45.0f}

// ���� ���¹̳� ��ġ
#define BOSS_STAMINA_FIRSTNUMBERLOCATION float4{ 225.0f , 102.0f}


// ���� �г� ��ġ
#define BOSS_ENDINGPANEL_LOCATION float4{ 48.0f , 21.0f}


// ���� �г� ��ġ
#define BOSS_ENDINGPANEL_LOCATION float4{ 48.0f , 21.0f}





// ���� :
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



	// GameEngineObject ���
private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart() override;
	void LevelEnd() override;




	// this
private:
	// ����
	GameEngineRenderer* LivesAniRenderer = nullptr;


	// Start
	void EndingRendererSet();
	void LivesAniRendererSet();
	void BossStaminaRendererSet();


	const float4 NumberScale = float4{ 24.0f, 24.0f };



	// Update
	// Ouch ���� ����
	bool Ouch_State = false;
	float Ouch_Time = 0.0f;
	const float Ouch_Duration = 1.0f;

	void OuchState(float _Delta);




	// ���� ü�� ��� ����
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



	// ���� ���¹̳� ����
	void BossStaminaState(float _Delta);



	// StarStick ����
	bool IsChangeStarStick = false;

	void ChangePortrait_StarStick();


	// Ending ����
	GameEngineRenderer* EndingPanelRenderer = nullptr;

	bool IsCall_ByeByePortrait = false;

	void ChangePortrait_ByeBye();



	// LevelStart
	void LevelStartStamina();
};

