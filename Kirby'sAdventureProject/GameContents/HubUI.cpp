#include "HubUI.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "GlobalContents.h"
#include "Kirby.h"

#include <vector>



HubUI::HubUI()
{
	UI = this;
}

HubUI::~HubUI()
{
}

void HubUI::Start()
{
	HubRendererSet("HubUI.bmp", "Resources\\UI");
	PortraitRendererSet(HUB_PORTRAITLOCATION);
	LivesNumberRendererSet(HUB_LIVESFIRSTNUMBERLOCATION);
	StaminaCountRendererSet("HUB_UI_LifeBar_2x1_24x24.bmp", "Resources\\UI", HUB_STAMINAFIRSTNUMBERLOCATION);
}



// 스태미나 숫자 세팅
void HubUI::StaminaCountRendererSet(const std::string& _FileName, const std::string& _Path, const float4& _StaminaFirstPos)
{
	// Sprite Scale
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	float4 StaminaScale = Texture->GetScale();


	// UI StaminaAnimation
	StaminaRenderer_vec.reserve(StaminaCount);
	for (size_t i = 0; i < StaminaCount; i++)
	{
		GameEngineRenderer* StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("렌더러가 Null 입니다..");
			return;
		}


		// Set Stamina Render
		StaminaRenderer->SetTexture(_FileName);
		StaminaRenderer->SetCopyPos(float4::ZERO);
		StaminaRenderer->SetCopyScale(StaminaScale);
		StaminaRenderer->SetRenderPos(_StaminaFirstPos + float4{ StaminaScale.X * static_cast<float>(i), 0.0f } + StaminaScale.Half());
		StaminaRenderer->SetRenderScale(StaminaScale);
		StaminaRenderer_vec.push_back(StaminaRenderer);
	}
}







/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */




void HubUI::Update(float _Delta)
{
	PortraitState(_Delta);
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void HubUI::LevelStart()
{
	UI = this;

	LevelStartStamina();
	LevelStartPortrait();
	LevelStartLivesCount();
}


// 스태미나 유지
void HubUI::LevelStartStamina()
{
	KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Kirby가 Null 입니다.");
		return;
	}


	for (int i = 0; i < StaminaRenderer_vec.size(); i++)
	{
		GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		StaminaRenderer->Off();
	}



	for (int i = 0; i < KirbyPtr->m_KirbyHp; i++)
	{
		GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		StaminaRenderer->On();
	}
}