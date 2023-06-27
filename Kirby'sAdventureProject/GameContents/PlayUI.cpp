#include "PlayUI.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "GlobalContents.h"
#include "Kirby.h"



PlayUI::PlayUI()
{
	UI = this;
}

PlayUI::~PlayUI()
{
}

void PlayUI::Start()
{
	HubRendererSet();
	LivesAniRendererSet();
	PortraitRendererSet();
	LivesNumberRendererSet();
	StaminaCountRendererSet();
	ScoreRendererSet();

}





void PlayUI::HubRendererSet()
{
	// UI 패널
	MainUIRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == MainUIRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("MainUI.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	UIScale = Texture->GetScale();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();


	//SetPos(float4{ WinScale.Half().X , WinScale.Y - UIScale.Half().Y });
	SetPos(float4{ 0.0f , WinScale.Y - UIScale.Y });


	MainUIRenderer->SetTexture("MainUI.bmp");
	MainUIRenderer->SetRenderPos(UIScale.Half());
	MainUIRenderer->SetRenderScale(UIScale);


	// 지정위치에 배치
}





void PlayUI::LivesAniRendererSet()
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





void PlayUI::PortraitRendererSet()
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





void PlayUI::LivesNumberRendererSet()
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
	First_LivesRenderer->SetRenderPos(PLAY_LIVESFIRSTNUMBERLOCATION + NumberScale.Half());
	First_LivesRenderer->SetRenderScale(NumberScale);


	Second_LivesRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount), 0.0f });
	Second_LivesRenderer->SetCopyScale(NumberScale);
	Second_LivesRenderer->SetRenderPos(PLAY_LIVESFIRSTNUMBERLOCATION + float4{ NumberScale.X , 0.0f } + NumberScale.Half());
	Second_LivesRenderer->SetRenderScale(NumberScale);
}






void PlayUI::StaminaCountRendererSet()
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
	First_StaminaRenderer->SetRenderPos(PLAY_STAMINAFIRSTNUMBERLOCATION + StaminaScale.Half());



	Second_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Second_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Second_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Second_StaminaRenderer->SetRenderPos(PLAY_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 1.0f , 0.0f } + StaminaScale.Half());



	Third_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Third_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Third_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Third_StaminaRenderer->SetRenderPos(PLAY_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 2.0f , 0.0f } + StaminaScale.Half());



	Fourth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Fourth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Fourth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Fourth_StaminaRenderer->SetRenderPos(PLAY_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 3.0f , 0.0f } + StaminaScale.Half());



	Fifth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Fifth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Fifth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Fifth_StaminaRenderer->SetRenderPos(PLAY_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 4.0f , 0.0f } + StaminaScale.Half());



	Sixth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Sixth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Sixth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Sixth_StaminaRenderer->SetRenderPos(PLAY_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 5.0f , 0.0f } + StaminaScale.Half());




	// 사운드
	GlobalContents::SoundFileLoad("Kirby_LowerHP.wav", "Resources\\SoundResources\\EffectVoice");
}




void PlayUI::ScoreRendererSet()
{
	// 점수 1번째 자리
	First_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == First_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 2번째 자리
	Second_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Second_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 3번째 자리
	Third_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Third_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 4번째 자리
	Fourth_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fourth_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 5번째 자리
	Fifth_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fifth_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 6번째 자리
	Sixth_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Sixth_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 7번째 자리
	Seventh_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Seventh_ScoreRenderer)
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



	// Set Score Position and Render
	First_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	First_ScoreRenderer->SetCopyPos(float4::ZERO);
	First_ScoreRenderer->SetCopyScale(NumberScale);
	First_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + NumberScale.Half());
	First_ScoreRenderer->SetRenderScale(NumberScale);



	Second_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Second_ScoreRenderer->SetCopyPos(float4::ZERO);
	Second_ScoreRenderer->SetCopyScale(NumberScale);
	Second_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X , 0.0f } + NumberScale.Half());
	Second_ScoreRenderer->SetRenderScale(NumberScale);



	Third_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Third_ScoreRenderer->SetCopyPos(float4::ZERO);
	Third_ScoreRenderer->SetCopyScale(NumberScale);
	Third_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 2.0f , 0.0f } + NumberScale.Half());
	Third_ScoreRenderer->SetRenderScale(NumberScale);



	Fourth_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Fourth_ScoreRenderer->SetCopyPos(float4::ZERO);
	Fourth_ScoreRenderer->SetCopyScale(NumberScale);
	Fourth_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 3.0f , 0.0f } + NumberScale.Half());
	Fourth_ScoreRenderer->SetRenderScale(NumberScale);



	Fifth_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Fifth_ScoreRenderer->SetCopyPos(float4::ZERO);
	Fifth_ScoreRenderer->SetCopyScale(NumberScale);
	Fifth_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 4.0f, 0.0f } + NumberScale.Half());
	Fifth_ScoreRenderer->SetRenderScale(NumberScale);



	Sixth_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Sixth_ScoreRenderer->SetCopyPos(float4::ZERO);
	Sixth_ScoreRenderer->SetCopyScale(NumberScale);
	Sixth_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 5.0f , 0.0f } + NumberScale.Half());
	Sixth_ScoreRenderer->SetRenderScale(NumberScale);



	Seventh_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Seventh_ScoreRenderer->SetCopyPos(float4::ZERO);
	Seventh_ScoreRenderer->SetCopyScale(NumberScale);
	Seventh_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 6.0f , 0.0f } + NumberScale.Half());
	Seventh_ScoreRenderer->SetRenderScale(NumberScale);

}






void PlayUI::Update(float _Delta)
{
	PortraitState(_Delta);

	OuchState(_Delta);

	StaminaState();
}




void PlayUI::OuchState(float _Delta)
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
				First_StaminaRenderer->Off();
				break;
			case 2:
				Second_StaminaRenderer->Off();
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.1f , 0.1f };

				// 사운드 재생
				GameEngineSound::SoundPlay("Kirby_LowerHP.wav");
				break;
			case 3:
				Third_StaminaRenderer->Off();
				Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.2f , 0.2f };
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.2f , 0.2f };
				break;
			case 4:
				Fourth_StaminaRenderer->Off();
				Third_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.3f , 0.3f };
				Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.3f , 0.3f };
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.3f , 0.3f };
				break;
			case 5:
				Fifth_StaminaRenderer->Off();
				Fourth_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				Third_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.4f , 0.4f };
				break;
			case 6:
				Sixth_StaminaRenderer->Off();
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
void PlayUI::LevelStart()
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
		Second_StaminaRenderer->Off();
		Third_StaminaRenderer->Off();
		Fourth_StaminaRenderer->Off();
		Fifth_StaminaRenderer->Off();
		Sixth_StaminaRenderer->Off();
		break;
	case 2:
		Third_StaminaRenderer->Off();
		Fourth_StaminaRenderer->Off();
		Fifth_StaminaRenderer->Off();
		Sixth_StaminaRenderer->Off();
		break;
	case 3:
		Fourth_StaminaRenderer->Off();
		Fifth_StaminaRenderer->Off();
		Sixth_StaminaRenderer->Off();
		break;
	case 4:
		Fifth_StaminaRenderer->Off();
		Sixth_StaminaRenderer->Off();
		break;
	case 5:
		Sixth_StaminaRenderer->Off();
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