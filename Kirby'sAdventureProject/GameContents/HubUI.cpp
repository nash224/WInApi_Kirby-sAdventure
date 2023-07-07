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
	LivesNumberRendererSet();
	StaminaCountRendererSet();
}



// 목숨 숫자 로드
void HubUI::LivesNumberRendererSet()
{
	// 목숨 숫자 앞자리
	First_LivesRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == First_LivesRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 목숨 숫자 뒷자리
	Second_LivesRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Second_LivesRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("UI_Number_10x1_24x24.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	First_LivesRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	First_LivesRenderer->SetCopyPos(float4{ 0.0f , 0.0f });
	First_LivesRenderer->SetCopyScale(NumberScale);
	First_LivesRenderer->SetRenderPos(HUB_LIVESFIRSTNUMBERLOCATION + NumberScale.Half());
	First_LivesRenderer->SetRenderScale(NumberScale);


	Second_LivesRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount), 0.0f });
	Second_LivesRenderer->SetCopyScale(NumberScale);
	Second_LivesRenderer->SetRenderPos(HUB_LIVESFIRSTNUMBERLOCATION + float4{ NumberScale.X , 0.0f } + NumberScale.Half());
	Second_LivesRenderer->SetRenderScale(NumberScale);
}




// 스태미나 숫자 세팅
void HubUI::StaminaCountRendererSet()
{
	// UI StaminaAnimation
	GameEngineRenderer* First_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == First_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	GameEngineRenderer* Second_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Second_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	GameEngineRenderer* Third_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Third_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	GameEngineRenderer* Fourth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fourth_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	GameEngineRenderer* Fifth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fifth_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	GameEngineRenderer* Sixth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Sixth_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}


	// Sprite Scale
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("HUB_UI_LifeBar_2x1_24x24.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}




	// Set Stamina Render
	First_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	First_StaminaRenderer->SetCopyPos(float4::ZERO);
	First_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	First_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + HUB_StaminaScale.Half());
	First_StaminaRenderer->SetRenderScale(HUB_StaminaScale);
	StaminaRenderer_vec.push_back(First_StaminaRenderer);


	Second_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Second_StaminaRenderer->SetCopyPos(float4::ZERO);
	Second_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Second_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X , 0.0f } + HUB_StaminaScale.Half());
	Second_StaminaRenderer->SetRenderScale(HUB_StaminaScale);
	StaminaRenderer_vec.push_back(Second_StaminaRenderer);



	Third_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Third_StaminaRenderer->SetCopyPos(float4::ZERO);
	Third_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Third_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 2.0f, 0.0f } + HUB_StaminaScale.Half());
	Third_StaminaRenderer->SetRenderScale(HUB_StaminaScale);
	StaminaRenderer_vec.push_back(Third_StaminaRenderer);



	Fourth_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Fourth_StaminaRenderer->SetCopyPos(float4::ZERO);
	Fourth_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Fourth_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 3.0f, 0.0f } + HUB_StaminaScale.Half());
	Fourth_StaminaRenderer->SetRenderScale(HUB_StaminaScale);
	StaminaRenderer_vec.push_back(Fourth_StaminaRenderer);



	Fifth_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Fifth_StaminaRenderer->SetCopyPos(float4::ZERO);
	Fifth_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Fifth_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 4.0f, 0.0f } + HUB_StaminaScale.Half());
	Fifth_StaminaRenderer->SetRenderScale(HUB_StaminaScale);
	StaminaRenderer_vec.push_back(Fifth_StaminaRenderer);



	Sixth_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Sixth_StaminaRenderer->SetCopyPos(float4::ZERO);
	Sixth_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Sixth_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 5.0f, 0.0f } + HUB_StaminaScale.Half());
	Sixth_StaminaRenderer->SetRenderScale(HUB_StaminaScale);
	StaminaRenderer_vec.push_back(Sixth_StaminaRenderer);


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


	for (int i = KirbyPtr->m_KirbyHp; i < StaminaRenderer_vec.size(); i++)
	{
		GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
	}
}