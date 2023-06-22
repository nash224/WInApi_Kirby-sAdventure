#pragma once
#include "UIManager.h"

#include <map>


// �̹��� �»�� ����
// ��� �ִϸ��̼� ��ġ
#define LIVESANILOCATION float4{ 573.0f , 66.0f}

// �ʻ�ȭ ��ġ
#define PORTRAITLOCATION float4{ 444.0f , 30.0f}

// ��� ���� ��ġ
#define BOSS_LIVESFIRSTNUMBERLOCATION float4{ 636.0f , 78.0f}

// ���¹̳� ��ġ
#define BOSS_STAMINAFIRSTNUMBERLOCATION float4{ 228.0f , 45.0f}

// ���� ���¹̳� ��ġ
#define BOSS_STAMINA_FIRSTNUMBERLOCATION float4{ 225.0f , 102.0f}





// ���� :
class BossUI : public UIManager
{
public:
	// constrcuter destructer
	BossUI();
	~BossUI();

	// delete Function
	BossUI(const BossUI& _Other) = delete;
	BossUI(BossUI&& _Other) noexcept = delete;
	BossUI& operator=(const BossUI& _Other) = delete;
	BossUI& operator=(BossUI&& _Other) noexcept = delete;


protected:
	GameEngineRenderer* LivesAniRenderer = nullptr;


	std::map<int, GameEngineRenderer*> Boss_StaminaRenderer;
	const int Boss_StaminaCount = 28;
	const float Boss_Stamina_Image_Inter = 6.0f;
	float4 Boss_StaminaScale = float4::ZERO;




	void HubRendererSet();
	void LivesAniRendererSet();
	void PortraitRendererSet();
	void LivesNumberRendererSet();
	void StaminaCountRendererSet();
	void BossStaminaRendererSet();




	void Start() override;
	void Update(float _Delta) override;

	void LevelStart() override;

private:
	const float4 NumberScale = float4{ 24.0f, 24.0f };


	bool Ouch_State = false;
	float Ouch_Time = 0.0f;
	const float Ouch_Duration = 1.0f;


	void OuchState(float _Delta);
};

