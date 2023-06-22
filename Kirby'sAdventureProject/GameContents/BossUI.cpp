#include "BossUI.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "GlobalContents.h"
#include "Kirby.h"



BossUI::BossUI()
{
	UI = this;
}

BossUI::~BossUI()
{
}

void BossUI::Start()
{
	HubRendererSet();
	LivesAniRendererSet();
	PortraitRendererSet();
	LivesNumberRendererSet();
	StaminaCountRendererSet();
	BossStaminaRendererSet();
}





void BossUI::HubRendererSet()
{
	// UI 패널
	MainUIRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == MainUIRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("BossUI.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	UIScale = Texture->GetScale();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();


	SetPos(float4{ 0.0f , WinScale.Y - UIScale.Y });


	MainUIRenderer->SetTexture("BossUI.bmp");
	MainUIRenderer->SetRenderPos(UIScale.Half());
	MainUIRenderer->SetRenderScale(UIScale);


}





void BossUI::LivesAniRendererSet()
{
	// UI LivesAnimation
	LivesAniRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == LivesAniRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}


	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("UI_LivesAni_3x1_39x36.bmp", "Resources\\UI", 3, 1);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	float4 LivesAniScale = Sprite->GetSprite(0).RenderScale;

	LivesAniRenderer->CreateAnimationToFrame("UI_LivesAnimation", "UI_LivesAni_3x1_39x36.bmp", { 0, 1, 2, 1 }, 0.5f, true);
	LivesAniRenderer->ChangeAnimation("UI_LivesAnimation");
	LivesAniRenderer->SetRenderPos(LIVESANILOCATION + LivesAniScale.Half());


}





void BossUI::PortraitRendererSet()
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

	PortraitRenderer->SetRenderPos(PORTRAITLOCATION + PortraitScale.Half());

}





void BossUI::LivesNumberRendererSet()
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
	First_LivesRenderer->SetRenderPos(BOSS_LIVESFIRSTNUMBERLOCATION + NumberScale.Half());
	First_LivesRenderer->SetRenderScale(NumberScale);


	Second_LivesRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount), 0.0f });
	Second_LivesRenderer->SetCopyScale(NumberScale);
	Second_LivesRenderer->SetRenderPos(BOSS_LIVESFIRSTNUMBERLOCATION + float4{ NumberScale.X , 0.0f } + NumberScale.Half());
	Second_LivesRenderer->SetRenderScale(NumberScale);
}






void BossUI::StaminaCountRendererSet()
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
	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("UI_LifeBar_3x1_24x42.bmp", "Resources\\UI", 3, 1);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	float4 StaminaScale = Sprite->GetSprite(0).RenderScale;



	// Set Stamina Render
	First_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	First_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	First_StaminaRenderer->ChangeAnimation("StaminaRemain");
	First_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + StaminaScale.Half());



	Second_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Second_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Second_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Second_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 1.0f , 0.0f } + StaminaScale.Half());



	Third_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Third_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Third_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Third_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 2.0f , 0.0f } + StaminaScale.Half());



	Fourth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Fourth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Fourth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Fourth_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 3.0f , 0.0f } + StaminaScale.Half());



	Fifth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Fifth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Fifth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Fifth_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 4.0f , 0.0f } + StaminaScale.Half());



	Sixth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Sixth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Sixth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Sixth_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 5.0f , 0.0f } + StaminaScale.Half());


}


void BossUI::BossStaminaRendererSet()
{

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("Boss_UI_LifeBar_2x1_9x24.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 Temprary_Boss_StaminaScale = Texture->GetScale();
	Boss_StaminaScale = float4{ Temprary_Boss_StaminaScale.Half().X , Temprary_Boss_StaminaScale.Y };


	for (int i = 0; i < Boss_StaminaCount; i++)
	{
		GameEngineRenderer* BossStaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
		if (nullptr == BossStaminaRenderer)
		{
			MsgBoxAssert("렌더러 생성에 실패했습니다.");
			return;
		}

		BossStaminaRenderer->SetTexture("Boss_UI_LifeBar_2x1_9x24.bmp");
		BossStaminaRenderer->SetCopyPos(float4{ 0.0f , 0.0f });
		BossStaminaRenderer->SetCopyScale(Boss_StaminaScale);
		BossStaminaRenderer->SetRenderPos(BOSS_STAMINA_FIRSTNUMBERLOCATION
			+ float4{ Boss_Stamina_Image_Inter * static_cast<int>(i) , 0.0f } + Boss_StaminaScale.Half());
		BossStaminaRenderer->SetRenderScale(Boss_StaminaScale);


		Boss_StaminaRenderer.insert(std::make_pair(i, BossStaminaRenderer));
	}

}




void BossUI::Update(float _Delta)
{
	PortraitState(_Delta);

	OuchState(_Delta);

	StaminaState();
}




void BossUI::OuchState(float _Delta)
{
	if (true == Ouch_State)
	{
		Ouch_Time += _Delta;
	}

	if (Ouch_Time > Ouch_Duration)
	{
		Ouch_Time = 0.0f;
		Ouch_State = false;
		PortraitRenderer->ChangeAnimation("Portrait_Normal");
	}


	// 커비의 체력과 UI의 체력이 다르면+
	if (m_KirbySteminaCount != KirbyPtr->m_KirbyHp && -1 != KirbyPtr->m_KirbyHp)
	{
		// 커비의 체력이 감소하면
		if (m_KirbySteminaCount > KirbyPtr->m_KirbyHp)
		{
			switch (m_KirbySteminaCount)
			{
			case 1:
				// 죽음
				First_StaminaRenderer->ChangeAnimation("StaminaNone");
				break;
			case 2:
				Second_StaminaRenderer->ChangeAnimation("StaminaNone");
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.1f , 0.1f };
				break;
			case 3:
				Third_StaminaRenderer->ChangeAnimation("StaminaNone");
				Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.2f , 0.2f };
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.2f , 0.2f };
				break;
			case 4:
				Fourth_StaminaRenderer->ChangeAnimation("StaminaNone");
				Third_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.3f , 0.3f };
				Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.3f , 0.3f };
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.3f , 0.3f };
				break;
			case 5:
				Fifth_StaminaRenderer->ChangeAnimation("StaminaNone");
				Fourth_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				Third_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				break;
			case 6:
				Sixth_StaminaRenderer->ChangeAnimation("StaminaNone");
				Fifth_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.5f , 0.5f };
				Fourth_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.5f , 0.5f };
				Third_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.5f , 0.5f };
				Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.5f , 0.5f };
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.5f , 0.5f };
				break;
			default:
				break;
			}

			PortraitRenderer->ChangeAnimation("Portrait_OUCH");
		}

		m_KirbySteminaCount = KirbyPtr->m_KirbyHp;
		Ouch_State = true;
	}
}





// 다음 레벨로 넘어갈 때 유지
void BossUI::LevelStart()
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
		Second_StaminaRenderer->ChangeAnimation("StaminaNone");
		Third_StaminaRenderer->ChangeAnimation("StaminaNone");
		Fourth_StaminaRenderer->ChangeAnimation("StaminaNone");
		Fifth_StaminaRenderer->ChangeAnimation("StaminaNone");
		Sixth_StaminaRenderer->ChangeAnimation("StaminaNone");
		break;
	case 2:
		Third_StaminaRenderer->ChangeAnimation("StaminaNone");
		Fourth_StaminaRenderer->ChangeAnimation("StaminaNone");
		Fifth_StaminaRenderer->ChangeAnimation("StaminaNone");
		Sixth_StaminaRenderer->ChangeAnimation("StaminaNone");
		break;
	case 3:
		Fourth_StaminaRenderer->ChangeAnimation("StaminaNone");
		Fifth_StaminaRenderer->ChangeAnimation("StaminaNone");
		Sixth_StaminaRenderer->ChangeAnimation("StaminaNone");
		break;
	case 4:
		Fifth_StaminaRenderer->ChangeAnimation("StaminaNone");
		Sixth_StaminaRenderer->ChangeAnimation("StaminaNone");
		break;
	case 5:
		Sixth_StaminaRenderer->ChangeAnimation("StaminaNone");
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