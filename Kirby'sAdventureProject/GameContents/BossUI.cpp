#include "BossUI.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "GlobalContents.h"
#include "Kirby.h"
#include "Boss.h"



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
	PortraitRendererSet(PORTRAITLOCATION);
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



	// 엔딩 패널 렌더러
	EndingPanelRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == EndingPanelRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	GameEngineWindowTexture* EndingPanel_Texture = GlobalContents::TextureFileLoad("ThanksForWatching.bmp", "Resources\\UI");
	if (nullptr == EndingPanel_Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	float4 EndingPanelScale = EndingPanel_Texture->GetScale();

	EndingPanelRenderer->SetTexture("ThanksForWatching.bmp");
	EndingPanelRenderer->SetRenderPos(BOSS_ENDINGPANEL_LOCATION + EndingPanelScale.Half());
	EndingPanelRenderer->Off();
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
	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("UI_LifeBar_3x1_24x42.bmp", "Resources\\UI", 3, 1);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	float4 StaminaScale = Sprite->GetSprite(0).RenderScale;


	StaminaRenderer_vec.reserve(6);


	// Set Stamina Render
	First_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	First_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	First_StaminaRenderer->ChangeAnimation("StaminaRemain");
	First_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + StaminaScale.Half());
	StaminaRenderer_vec.push_back(First_StaminaRenderer);



	Second_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Second_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Second_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Second_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 1.0f , 0.0f } + StaminaScale.Half());
	StaminaRenderer_vec.push_back(Second_StaminaRenderer);



	Third_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Third_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Third_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Third_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 2.0f , 0.0f } + StaminaScale.Half());
	StaminaRenderer_vec.push_back(Third_StaminaRenderer);



	Fourth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Fourth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Fourth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Fourth_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 3.0f , 0.0f } + StaminaScale.Half());
	StaminaRenderer_vec.push_back(Fourth_StaminaRenderer);



	Fifth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Fifth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Fifth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Fifth_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 4.0f , 0.0f } + StaminaScale.Half());
	StaminaRenderer_vec.push_back(Fifth_StaminaRenderer);



	Sixth_StaminaRenderer->CreateAnimation("StaminaRemain", "UI_LifeBar_3x1_24x42.bmp", 0, 1, 0.6f, true);
	Sixth_StaminaRenderer->CreateAnimation("StaminaNone", "UI_LifeBar_3x1_24x42.bmp", 2, 2, 0.6f, false);
	Sixth_StaminaRenderer->ChangeAnimation("StaminaRemain");
	Sixth_StaminaRenderer->SetRenderPos(BOSS_STAMINAFIRSTNUMBERLOCATION + float4{ StaminaScale.X * 5.0f , 0.0f } + StaminaScale.Half());
	StaminaRenderer_vec.push_back(Sixth_StaminaRenderer);


	// 사운드
	GlobalContents::SoundFileLoad("Kirby_LowerHP.wav", "Resources\\SoundResources\\EffectVoice");
}


void BossUI::BossStaminaRendererSet()
{
	// 로드
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("Boss_UI_LifeBar_1x1_9x24.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	// 이미지 한칸 사이즈
	Boss_StaminaScale = Texture->GetScale();

	Boss_StaminaRenderer.reserve(Boss_MaxStaminaCount);

	// 초기설정
	for (int i = 0; i < Boss_MaxStaminaCount; i++)
	{
		GameEngineRenderer* BossStaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
		if (nullptr == BossStaminaRenderer)
		{
			MsgBoxAssert("렌더러 생성에 실패했습니다.");
			return;
		}

		BossStaminaRenderer->SetTexture("Boss_UI_LifeBar_1x1_9x24.bmp");
		BossStaminaRenderer->SetCopyPos(float4::ZERO);
		BossStaminaRenderer->SetCopyScale(Boss_StaminaScale);
		BossStaminaRenderer->SetRenderPos(BOSS_STAMINA_FIRSTNUMBERLOCATION
			+ float4{ Boss_Stamina_Image_Inter * static_cast<int>(i) , 0.0f } + Boss_StaminaScale.Half());
		BossStaminaRenderer->SetRenderScale(Boss_StaminaScale);
		BossStaminaRenderer->Off();


		Boss_StaminaRenderer.push_back(BossStaminaRenderer);
	}


	// 사운드
	GlobalContents::SoundFileLoad("Boss_StaminaFullSound.wav", "Resources\\SoundResources\\EffectVoice");
}




void BossUI::Update(float _Delta)
{
	// 피 다 채웠으면 실행 x
	if (false == Boss_Stamina_Full_Done)
	{
		BossAppearance(_Delta);
	}


	PortraitState(_Delta);
	ChangePortrait_StarStick();
	ChangePortrait_ByeBye();

	OuchState(_Delta);

	StaminaState();

	if (true == Boss_Stamina_Full_Done)
	{
		BossStaminaState(_Delta);
	}



}




void BossUI::BossAppearance(float _Delta)
{
	if (nullptr == BossPtr)
	{
		MsgBoxAssert("보스를 불러오지 못했습니다.");
		return;
	}

	// 보스가 플레이어를 찾았으면, 피를채움
	if (true == BossPtr->IsBossFindKirby)
	{
		BossPtr->IsBossFindKirby = false;
		IsBossStaminaFull = true;
	}

	if (true == IsBossStaminaFull)
	{
		Boss_Stamina_Full_Time += _Delta;
	}


	// 일정 간격마다
	if (Boss_Stamina_Full_Time > Boss_Stamina_Full_Inter)
	{
		Boss_Stamina_Full_Time = 0.0f;

		// 2번 피를 채움
		for (size_t i = 0; i < 2; i++)
		{
			GameEngineRenderer* Boss_Stamina_RendererPtr = Boss_StaminaRenderer[UI_BossStamina];
			if (nullptr == Boss_Stamina_RendererPtr)
			{
				MsgBoxAssert("참조하지 못했습니다.");
				return;
			}

			Boss_Stamina_RendererPtr->On();


			++UI_BossStamina;
		}


		// 사운드 재생
		GameEngineSound::SoundPlay("Boss_StaminaFullSound.wav");


		if (Boss_MaxStaminaCount == UI_BossStamina)
		{
			Boss_Stamina_Full_Done = true;
		}
	}
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
			// 피가 0일때 모든 Hp Off
			if (0 == KirbyPtr->m_KirbyHp)
			{
				for (size_t i = 0; i < StaminaRenderer_vec.size(); i++)
				{
					GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
					if (nullptr == StaminaRenderer)
					{
						MsgBoxAssert("렌더러를 불러오지 못했습니다.");
						return;
					}

					StaminaRenderer->Off();
				}
			}
			// 피가 0보다 클 때
			else if (KirbyPtr->m_KirbyHp > 0)
			{
				GameEngineRenderer* StaminaRenderer_Off = StaminaRenderer_vec[KirbyPtr->m_KirbyHp];
				if (nullptr == StaminaRenderer_Off)
				{
					MsgBoxAssert("렌더러를 불러오지 못했습니다.");
					return;
				}

				StaminaRenderer_Off->Off();


				for (size_t i = 0; i < KirbyPtr->m_KirbyHp; i++)
				{
					GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
					if (nullptr == StaminaRenderer)
					{
						MsgBoxAssert("렌더러를 불러오지 못했습니다.");
						return;
					}

					float Stamina_Inter = 0.1f * static_cast<float>(KirbyPtr->m_KirbyHp);

					StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { Stamina_Inter , Stamina_Inter };
				}

				if (1 == KirbyPtr->m_KirbyHp)
				{
					GameEngineSound::SoundPlay("Kirby_LowerHP.wav");
				}

				PortraitRenderer->ChangeAnimation("Portrait_OUCH");
			}

		}

		m_KirbySteminaCount = KirbyPtr->m_KirbyHp;
		Ouch_State = true;
	}
}



void BossUI::BossStaminaState(float _Delta)
{
	if (nullptr == BossPtr)
	{
		MsgBoxAssert("보스를 불러오지 못했습니다.");
		return;
	}

	int Current_BossHp = BossPtr->m_BossHp;


	if (UI_BossStamina != Current_BossHp)
	{
		for (size_t i = Current_BossHp; i < UI_BossStamina; i++)
		{
			if (i < 0)
			{
				continue;
			}

			GameEngineRenderer* CurStaminarenderer = Boss_StaminaRenderer[i];
			if (nullptr == CurStaminarenderer)
			{
				MsgBoxAssert("벡터의 렌더러를 불러오지 못했습니다.");
				return;
			}

			CurStaminarenderer->Off();
		}

		UI_BossStamina = Current_BossHp;
	}



	if (UI_BossStamina <= 0)
	{
		//
	}
}



void BossUI::ChangePortrait_StarStick()
{
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return;
	}

	if (true == KirbyPtr->IsReachedStarStick)
	{
		if (false == IsChangeStarStick)
		{
			if (nullptr == PortraitRenderer)
			{
				MsgBoxAssert("초상화 렌더러를 불러오지 못했습니다.");
				return;
			}

			PortraitRenderer->ChangeAnimation("Portrait_Clear");

			IsChangeStarStick = true;
		}
	}
}


void BossUI::ChangePortrait_ByeBye()
{
	if (true == IsCall_ByeByePortrait)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
		}

		if (nullptr == EndingPanelRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		for (size_t i = 0; i < StaminaRenderer_vec.size(); i++)
		{
			GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
			if (nullptr == StaminaRenderer)
			{
				MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
			}

			StaminaRenderer->Off();
		}



		PortraitRenderer->ChangeAnimation("Portrait_ByeBye");
		EndingPanelRenderer->On();

		IsCall_ByeByePortrait = false;
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


	BossPtr = Boss::GetMainBossPtr();
	if (nullptr == BossPtr)
	{
		MsgBoxAssert("보스를 불러오지 못했습니다.");
		return;
	}


	// 커비 체력
	for (size_t i = KirbyPtr->m_KirbyHp; i < StaminaRenderer_vec.size(); i++)
	{
		GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		StaminaRenderer->Off();
	}



	LevelStartPortrait();


	// 커비 목숨
	First_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount / 10), 0.0f });
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount % 10), 0.0f });
}

void BossUI::LevelEnd()
{

	for (size_t i = 0; i < Boss_StaminaRenderer.size(); i++)
	{
		GameEngineRenderer* StaminaRenderer = Boss_StaminaRenderer[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("펑");
			return;
		}

		StaminaRenderer->Off();
	}

	Boss_Stamina_Full_Done = false;
	IsBossStaminaFull = false;
	UI_BossStamina = 0;
}