#pragma once
#include "UIManager.h"

// 이미지 좌상단 기준
// 목숨 애니메이션 위치
#define LIVESANILOCATION float4{ 573.0f , 66.0f}

// 초상화 위치
#define HUB_PORTRAITLOCATION float4{ 63.0f , 42.0f }

// 목숨 숫자 위치
#define HUB_LIVESFIRSTNUMBERLOCATION float4{ 615.0f , 138.0f}

// 스태미나 위치
#define HUB_STAMINAFIRSTNUMBERLOCATION float4{ 375.0f , 138.0f}






// 설명 :
class HubUI : public UIManager
{
public:

public:
	// constrcuter destructer
	HubUI();
	~HubUI();

	// delete Function
	HubUI(const HubUI& _Other) = delete;
	HubUI(HubUI&& _Other) noexcept = delete;
	HubUI& operator=(const HubUI& _Other) = delete;
	HubUI& operator=(HubUI&& _Other) noexcept = delete;


protected:
	void HubRendererSet();
	void LivesNumberRendererSet();
	void StaminaCountRendererSet();




	void Start() override;
	void Update(float _Delta) override;

	void LevelStart() override;

private:
	const float4 HUB_StaminaScale = float4{ 24.0f, 24.0f };




};

