#include "UIManager.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "Kirby.h"


UIManager* UIManager::UI = nullptr;
int UIManager::m_LivesCount = 4;
int UIManager::m_KirbySteminaCount = 6;
int UIManager::KirbyMode = -1;




UIManager::UIManager() 
{
}

UIManager::~UIManager() 
{
}



// �ʻ�ȭ �ʱ� ����
void UIManager::PortraitRendererSet(const float4& _RenderPos)
{
	// UI �г�
	PortraitRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == PortraitRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�..");
		return;
	}


	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("UI_Portrait_7x2_96x120.bmp", "Resources\\UI", 7, 2);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI �ؽ�ó�� ���ϸ��� ����");
		return;
	}


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
	PortraitRenderer->CreateAnimation("Portrait_Ice", "UI_Portrait_7x2_96x120.bmp", 10, 10, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_Clear", "UI_Portrait_7x2_96x120.bmp", 11, 11, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_ByeBye", "UI_Portrait_7x2_96x120.bmp", 12, 12, 0.1f, false);
	PortraitRenderer->CreateAnimation("Portrait_WarpStar", "UI_Portrait_7x2_96x120.bmp", 13, 13, 0.1f, false);

	PortraitRenderer->ChangeAnimation("Portrait_Normal");


	float4 PortraitScale = Sprite->GetSprite(0).RenderScale;


	PortraitRenderer->SetRenderPos(_RenderPos + PortraitScale.Half());
}




/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */




// �ʻ�ȭ ������Ʈ
void UIManager::PortraitState(float _Delta)
{
	if (0 == m_KirbySteminaCount)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� �������ϴ�.");
			return;
		}

		PortraitRenderer->ChangeAnimation("Portrait_Miss");
	}



	// ��Ŵ �ʻ�ȭ
	if (true == KirbyPtr->IsGulpEnemy)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� �������ϴ�.");
			return;
		}

		PortraitRenderer->ChangeAnimation("Portrait_Nothing");
		IsGulpPortraitDone = false;
	}

	if (false == IsGulpPortraitDone)
	{
		GulpPortraitTime += _Delta;
	}

	if (GulpPortraitTime > GulpPortraitDuration)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� �������ϴ�.");
			return;
		}

		IsGulpPortraitDone = true;
		GulpPortraitTime = 0.0f;

		PortraitRenderer->ChangeAnimation("Portrait_Normal");
	}



	// ��庰 �ʻ�ȭ
	int KirbyPtrMode = static_cast<int>(KirbyPtr->Mode);
	if (KirbyMode != KirbyPtrMode && AbilityStar::Max != KirbyPtr->Mode)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� �������ϴ�.");
			return;
		}

		switch (KirbyPtr->Mode)
		{
		case AbilityStar::Normal:
			PortraitRenderer->ChangeAnimation("Portrait_Normal");
			break;
		case AbilityStar::Spark:
			PortraitRenderer->ChangeAnimation("Portrait_Spark");
			break;
		case AbilityStar::Laser:
			PortraitRenderer->ChangeAnimation("Portrait_Laser");
			break;
		case AbilityStar::Beam:
			PortraitRenderer->ChangeAnimation("Portrait_Beam");
			break;
		case AbilityStar::Fire:
			PortraitRenderer->ChangeAnimation("Portrait_Fire");
			break;
		case AbilityStar::Thorn:
			PortraitRenderer->ChangeAnimation("Portrait_Needle");
			break;
		case AbilityStar::Sword:
			PortraitRenderer->ChangeAnimation("Portrait_Sword");
			break;
		case AbilityStar::Ice:
			PortraitRenderer->ChangeAnimation("Portrait_Ice");
			break;
		default:
			break;
		}


		KirbyMode = static_cast<int>(KirbyPtr->Mode);
	}
}



// �׾��� �� ���׹̳� 
void UIManager::StaminaState()
{
	if (true == KirbyPtr->IsKirbyRevive)
	{
		// ������ 1���� 
		--m_LivesCount;

		// Hp �ʱ�ȭ
		m_KirbySteminaCount = 6;


		for (int i = 0; i < StaminaRenderer_vec.size(); i++)
		{
			GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
			if (nullptr == StaminaRenderer)
			{
				MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
				return;
			}

			StaminaRenderer->On();
			StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.6f , 0.6f };
			StaminaRenderer->FindAnimation("StaminaRemain")->CurInter = 0.0f;
			StaminaRenderer->FindAnimation("StaminaRemain")->CurFrame = 0;
		}


		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� �������ϴ�.");
			return;
		}

		PortraitRenderer->ChangeAnimation("Portrait_Normal");

		KirbyPtr->IsKirbyRevive = false;



		if (nullptr == Second_LivesRenderer)
		{
			MsgBoxAssert("�������� �ҷ����� �������ϴ�.");
			return;
		}

		Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount), 0.0f });
	}

}




/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */




// �ʻ�ȭ ����
void UIManager::LevelStartPortrait()
{
	if (nullptr == PortraitRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}


	// Ŀ�� ���
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
	case 7:
		PortraitRenderer->ChangeAnimation("Portrait_Sword");
		break;
	case 8:
		PortraitRenderer->ChangeAnimation("Portrait_Ice");
		break;
	default:
		break;
	}
}



// ��� ����
void UIManager::LevelStartLivesCount()
{
	if (nullptr == First_LivesRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	if (nullptr == Second_LivesRenderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	// Ŀ�� ���
	First_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount / 10), 0.0f });
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount % 10), 0.0f });
}
