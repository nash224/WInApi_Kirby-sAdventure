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
	StaminaCountRendererSet("HUB_UI_LifeBar_2x1_24x24.bmp", "Resources\\UI", HUB_STAMINAFIRSTNUMBERLOCATION);
}



// ���¹̳� ���� ����
void HubUI::StaminaCountRendererSet(const std::string& _FileName, const std::string& _Path, const float4& _StaminaFirstPos)
{
	// Sprite Scale
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI �ؽ�ó�� ���ϸ��� ����");
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
			MsgBoxAssert("�������� Null �Դϴ�..");
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




// ��� ���� �ε�
void HubUI::LivesNumberRendererSet()
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
	First_LivesRenderer->SetRenderPos(HUB_LIVESFIRSTNUMBERLOCATION + NumberScale.Half());
	First_LivesRenderer->SetRenderScale(NumberScale);


	Second_LivesRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount), 0.0f });
	Second_LivesRenderer->SetCopyScale(NumberScale);
	Second_LivesRenderer->SetRenderPos(HUB_LIVESFIRSTNUMBERLOCATION + float4{ NumberScale.X , 0.0f } + NumberScale.Half());
	Second_LivesRenderer->SetRenderScale(NumberScale);
}







/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */




void HubUI::Update(float _Delta)
{
	PortraitState(_Delta);
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void HubUI::LevelStart()
{
	UI = this;

	LevelStartStamina();
	LevelStartPortrait();
	LevelStartLivesCount();
}


// ���¹̳� ����
void HubUI::LevelStartStamina()
{
	KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Kirby�� Null �Դϴ�.");
		return;
	}


	for (int i = 0; i < StaminaRenderer_vec.size(); i++)
	{
		GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
			return;
		}

		StaminaRenderer->Off();
	}



	for (int i = 0; i < KirbyPtr->m_KirbyHp; i++)
	{
		GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
		if (nullptr == StaminaRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
			return;
		}

		StaminaRenderer->On();
	}
}