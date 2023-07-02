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
	// UI �г�
	MainUIRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == MainUIRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("BossUI.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI �ؽ�ó�� ���ϸ��� ����");
		return;
	}

	UIScale = Texture->GetScale();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();


	SetPos(float4{ 0.0f , WinScale.Y - UIScale.Y });


	MainUIRenderer->SetTexture("BossUI.bmp");
	MainUIRenderer->SetRenderPos(UIScale.Half());
	MainUIRenderer->SetRenderScale(UIScale);



	// ���� �г� ������
	EndingPanelRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == EndingPanelRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	GameEngineWindowTexture* EndingPanel_Texture = GlobalContents::TextureFileLoad("ThanksForWatching.bmp", "Resources\\UI");
	if (nullptr == EndingPanel_Texture)
	{
		MsgBoxAssert("UI �ؽ�ó�� ���ϸ��� ����");
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
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}


	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("UI_LivesAni_3x1_39x36.bmp", "Resources\\UI", 3, 1);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI �ؽ�ó�� ���ϸ��� ����");
		return;
	}

	float4 LivesAniScale = Sprite->GetSprite(0).RenderScale;

	LivesAniRenderer->CreateAnimationToFrame("UI_LivesAnimation", "UI_LivesAni_3x1_39x36.bmp", { 0, 1, 2, 1 }, 0.5f, true);
	LivesAniRenderer->ChangeAnimation("UI_LivesAnimation");
	LivesAniRenderer->SetRenderPos(LIVESANILOCATION + LivesAniScale.Half());


}







void BossUI::LivesNumberRendererSet()
{
	// ��� ���� ���ڸ�
	First_LivesRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == First_LivesRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	// ��� ���� ���ڸ�
	Second_LivesRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Second_LivesRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("UI_Number_10x1_24x24.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI �ؽ�ó�� ���ϸ��� ����");
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
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	GameEngineRenderer* Second_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Second_StaminaRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	GameEngineRenderer* Third_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Third_StaminaRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	GameEngineRenderer* Fourth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fourth_StaminaRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	GameEngineRenderer* Fifth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fifth_StaminaRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}

	GameEngineRenderer* Sixth_StaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Sixth_StaminaRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}


	// Sprite Scale
	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("UI_LifeBar_3x1_24x42.bmp", "Resources\\UI", 3, 1);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI �ؽ�ó�� ���ϸ��� ����");
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


	// ����
	GlobalContents::SoundFileLoad("Kirby_LowerHP.wav", "Resources\\SoundResources\\EffectVoice");
}


void BossUI::BossStaminaRendererSet()
{
	// �ε�
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("Boss_UI_LifeBar_1x1_9x24.bmp", "Resources\\UI");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	// �̹��� ��ĭ ������
	Boss_StaminaScale = Texture->GetScale();

	Boss_StaminaRenderer.reserve(Boss_MaxStaminaCount);

	// �ʱ⼳��
	for (int i = 0; i < Boss_MaxStaminaCount; i++)
	{
		GameEngineRenderer* BossStaminaRenderer = CreateUIRenderer(RenderOrder::PlayUI);
		if (nullptr == BossStaminaRenderer)
		{
			MsgBoxAssert("������ ������ �����߽��ϴ�.");
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


	// ����
	GlobalContents::SoundFileLoad("Boss_StaminaFullSound.wav", "Resources\\SoundResources\\EffectVoice");
}




void BossUI::Update(float _Delta)
{
	// �� �� ä������ ���� x
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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	// ������ �÷��̾ ã������, �Ǹ�ä��
	if (true == BossPtr->IsBossFindKirby)
	{
		BossPtr->IsBossFindKirby = false;
		IsBossStaminaFull = true;
	}

	if (true == IsBossStaminaFull)
	{
		Boss_Stamina_Full_Time += _Delta;
	}


	// ���� ���ݸ���
	if (Boss_Stamina_Full_Time > Boss_Stamina_Full_Inter)
	{
		Boss_Stamina_Full_Time = 0.0f;

		// 2�� �Ǹ� ä��
		for (size_t i = 0; i < 2; i++)
		{
			GameEngineRenderer* Boss_Stamina_RendererPtr = Boss_StaminaRenderer[UI_BossStamina];
			if (nullptr == Boss_Stamina_RendererPtr)
			{
				MsgBoxAssert("�������� ���߽��ϴ�.");
				return;
			}

			Boss_Stamina_RendererPtr->On();


			++UI_BossStamina;
		}


		// ���� ���
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


	// Ŀ���� ü�°� UI�� ü���� �ٸ���+
	if (m_KirbySteminaCount != KirbyPtr->m_KirbyHp && -1 != KirbyPtr->m_KirbyHp)
	{
		// Ŀ���� ü���� �����ϸ�
		if (m_KirbySteminaCount > KirbyPtr->m_KirbyHp)
		{
			// �ǰ� 0�϶� ��� Hp Off
			if (0 == KirbyPtr->m_KirbyHp)
			{
				for (size_t i = 0; i < StaminaRenderer_vec.size(); i++)
				{
					GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
					if (nullptr == StaminaRenderer)
					{
						MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
						return;
					}

					StaminaRenderer->Off();
				}
			}
			// �ǰ� 0���� Ŭ ��
			else if (KirbyPtr->m_KirbyHp > 0)
			{
				GameEngineRenderer* StaminaRenderer_Off = StaminaRenderer_vec[KirbyPtr->m_KirbyHp];
				if (nullptr == StaminaRenderer_Off)
				{
					MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
					return;
				}

				StaminaRenderer_Off->Off();


				for (size_t i = 0; i < KirbyPtr->m_KirbyHp; i++)
				{
					GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
					if (nullptr == StaminaRenderer)
					{
						MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
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
				MsgBoxAssert("������ �������� �ҷ����� ���߽��ϴ�.");
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
		MsgBoxAssert("Ŀ�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	if (true == KirbyPtr->IsReachedStarStick)
	{
		if (false == IsChangeStarStick)
		{
			if (nullptr == PortraitRenderer)
			{
				MsgBoxAssert("�ʻ�ȭ �������� �ҷ����� ���߽��ϴ�.");
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
			MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
				return;
		}

		if (nullptr == EndingPanelRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
			return;
		}

		for (size_t i = 0; i < StaminaRenderer_vec.size(); i++)
		{
			GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
			if (nullptr == StaminaRenderer)
			{
				MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
				return;
			}

			StaminaRenderer->Off();
		}



		PortraitRenderer->ChangeAnimation("Portrait_ByeBye");
		EndingPanelRenderer->On();

		IsCall_ByeByePortrait = false;
	}
}



// ���� ������ �Ѿ �� ����
void BossUI::LevelStart()
{
	UI = this;

	KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Kirby�� Null �Դϴ�.");
		return;
	}


	BossPtr = Boss::GetMainBossPtr();
	if (nullptr == BossPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}


	// Ŀ�� ü��
	for (size_t i = KirbyPtr->m_KirbyHp; i < StaminaRenderer_vec.size(); i++)
	{
		GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
			return;
		}

		StaminaRenderer->Off();
	}



	LevelStartPortrait();


	// Ŀ�� ���
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
			MsgBoxAssert("��");
			return;
		}

		StaminaRenderer->Off();
	}

	Boss_Stamina_Full_Done = false;
	IsBossStaminaFull = false;
	UI_BossStamina = 0;
}