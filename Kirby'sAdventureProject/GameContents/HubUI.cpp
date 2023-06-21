#include "HubUI.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "GlobalContents.h"
#include "Kirby.h"



HubUI::HubUI()
{
	UI = this;
}

HubUI::~HubUI()
{
}

void HubUI::Start()
{
	HubRendererSet();
	PortraitRendererSet();
	LivesNumberRendererSet();
	StaminaCountRendererSet();

}





void HubUI::HubRendererSet()
{
	// UI 패널
	MainUIRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == MainUIRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("HubUI.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	UIScale = Texture->GetScale();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();


	SetPos(float4{ 0.0f , WinScale.Y - UIScale.Y });

	// 크기 및 위치 설정
	MainUIRenderer->SetTexture("HubUI.bmp");
	MainUIRenderer->SetRenderPos(UIScale.Half());
	MainUIRenderer->SetRenderScale(UIScale);


}







void HubUI::PortraitRendererSet()
{
	// UI 패널
	PortraitRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == PortraitRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}


	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("UI_Portrait_7x2_96x120.bmp", "Resources\\UI", 7, 2);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	float4 PortraitScale = Sprite->GetSprite(0).RenderScale;

	PortraitRenderer->CreateAnimation("Portrait_Normal", "UI_Portrait_7x2_96x120.bmp", 0, 0, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Beam", "UI_Portrait_7x2_96x120.bmp", 1, 1, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Laser", "UI_Portrait_7x2_96x120.bmp", 2, 2, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Fire", "UI_Portrait_7x2_96x120.bmp", 3, 3, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Needle", "UI_Portrait_7x2_96x120.bmp", 4, 4, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Sword", "UI_Portrait_7x2_96x120.bmp", 5, 5, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Spark", "UI_Portrait_7x2_96x120.bmp", 6, 6, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Nothing", "UI_Portrait_7x2_96x120.bmp", 7, 7, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_OUCH", "UI_Portrait_7x2_96x120.bmp", 8, 8, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_MISS", "UI_Portrait_7x2_96x120.bmp", 9, 9, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Goal", "UI_Portrait_7x2_96x120.bmp", 10, 10, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Clear", "UI_Portrait_7x2_96x120.bmp", 11, 11, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_ByeBye", "UI_Portrait_7x2_96x120.bmp", 12, 12, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_WarpStar", "UI_Portrait_7x2_96x120.bmp", 13, 13, 0.1f, false);

	PortraitRenderer->ChangeAnimation("Portrait_Normal");

	PortraitRenderer->SetRenderPos(HUB_PORTRAITLOCATION + PortraitScale.Half());

}





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






void HubUI::StaminaCountRendererSet()
{
	// UI StaminaAnimation
	First_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == First_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	Second_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Second_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	Third_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Third_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	Fourth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fourth_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	Fifth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fifth_StaminaRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	Sixth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
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


	Second_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Second_StaminaRenderer->SetCopyPos(float4::ZERO);
	Second_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Second_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X , 0.0f } + HUB_StaminaScale.Half());
	Second_StaminaRenderer->SetRenderScale(HUB_StaminaScale);



	Third_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Third_StaminaRenderer->SetCopyPos(float4::ZERO);
	Third_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Third_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 2.0f, 0.0f } + HUB_StaminaScale.Half());
	Third_StaminaRenderer->SetRenderScale(HUB_StaminaScale);



	Fourth_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Fourth_StaminaRenderer->SetCopyPos(float4::ZERO);
	Fourth_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Fourth_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 3.0f, 0.0f } + HUB_StaminaScale.Half());
	Fourth_StaminaRenderer->SetRenderScale(HUB_StaminaScale);



	Fifth_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Fifth_StaminaRenderer->SetCopyPos(float4::ZERO);
	Fifth_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Fifth_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 4.0f, 0.0f } + HUB_StaminaScale.Half());
	Fifth_StaminaRenderer->SetRenderScale(HUB_StaminaScale);



	Sixth_StaminaRenderer->SetTexture("HUB_UI_LifeBar_2x1_24x24.bmp");
	Sixth_StaminaRenderer->SetCopyPos(float4::ZERO);
	Sixth_StaminaRenderer->SetCopyScale(HUB_StaminaScale);
	Sixth_StaminaRenderer->SetRenderPos(HUB_STAMINAFIRSTNUMBERLOCATION + float4{ HUB_StaminaScale.X * 5.0f, 0.0f } + HUB_StaminaScale.Half());
	Sixth_StaminaRenderer->SetRenderScale(HUB_StaminaScale);


}








void HubUI::Update(float _Delta)
{
	PortraitState(_Delta);
}




// 다음 레벨로 넘어갈 때 유지
void HubUI::LevelStart()
{
	UI = this;

	KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Kirby가 Null 입니다.");
		return;
	}


	// 커비 체력
	switch (KirbyPtr->m_KirbyHp)
	{
	case 1:
		Second_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Third_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Fourth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Fifth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Sixth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		break;
	case 2:
		Third_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Fourth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Fifth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Sixth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		break;
	case 3:
		Fourth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Fifth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Sixth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		break;
	case 4:
		Fifth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		Sixth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		break;
	case 5:
		Sixth_StaminaRenderer->SetCopyPos(float4{ HUB_StaminaScale.X , 0.0f });
		break;
	case 6:
		break;
	default:
		break;
	}


	// 커비 모드
	switch (KirbyMode)
	{
	case 0:
		PortraitRenderer->ChangeAnimation("Portrait_Normal");
		break;
	case 1:
		PortraitRenderer->ChangeAnimation("Portrait_Spark");
		break;
	case 2:
		PortraitRenderer->ChangeAnimation("Portrait_Laser");
		break;
	case 3:
		PortraitRenderer->ChangeAnimation("Portrait_Beam");
		break;
	case 4:
		PortraitRenderer->ChangeAnimation("Portrait_Fire");
		break;
	case 6:
		PortraitRenderer->ChangeAnimation("Portrait_Needle");
		break;
	default:
		break;
	}


	// 커비 목숨
	First_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount / 10), 0.0f });
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount % 10), 0.0f });
}