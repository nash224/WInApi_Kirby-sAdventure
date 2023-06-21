#include "UIManager.h"

#include <GameEngineCore/GameEngineRenderer.h>

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


// 죽었을 때 스테미나 
void UIManager::StaminaState()
{
	if (true == KirbyPtr->IsKirbyRevive && 0 == m_KirbySteminaCount)
	{
		// Hp 초기화
		m_KirbySteminaCount = 6;

		First_StaminaRenderer->ChangeAnimation("StaminaRemain");
		Second_StaminaRenderer->ChangeAnimation("StaminaRemain");
		Third_StaminaRenderer->ChangeAnimation("StaminaRemain");
		Fourth_StaminaRenderer->ChangeAnimation("StaminaRemain");
		Fifth_StaminaRenderer->ChangeAnimation("StaminaRemain");
		Sixth_StaminaRenderer->ChangeAnimation("StaminaRemain");


		// 프레임간격 재설정
		Fifth_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.6f , 0.6f };
		Fourth_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.6f , 0.6f };
		Third_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.6f , 0.6f };
		Second_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.6f , 0.6f };
		First_StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.6f , 0.6f };
	}

}



void UIManager::PortraitState(float _Delta)
{
	if (0 == m_KirbySteminaCount)
	{
		PortraitRenderer->ChangeAnimation("Portrait_Miss");
	}



	// 삼킴 초상화
	if (true == KirbyPtr->IsGulpEnemy)
	{
		PortraitRenderer->ChangeAnimation("Portrait_Nothing");
		IsGulpPortraitDone = false;
	}

	if (false == IsGulpPortraitDone)
	{
		IsGulpPortraitTime += _Delta;
	}

	if (IsGulpPortraitTime > IsGulpPortraitDuration)
	{
		IsGulpPortraitDone = true;
		IsGulpPortraitTime = 0.0f;

		PortraitRenderer->ChangeAnimation("Portrait_Normal");
	}



	// 모드별 초상화
	int KirbyPtrMode = static_cast<int>(KirbyPtr->Mode);
	if (KirbyMode != KirbyPtrMode && AbilityStar::Max != KirbyPtr->Mode)
	{
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
		default:
			break;
		}


		KirbyMode = static_cast<int>(KirbyPtr->Mode);
	}
}
