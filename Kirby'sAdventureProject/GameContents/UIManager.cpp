#include "UIManager.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"

#include <GameEnginePlatform/GameEngineWindow.h>
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




// UI 이미지 세팅
void UIManager::HubRendererSet(const std::string& _FileName, const std::string& _Path)
{
	// UI 패널
	MainUIRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == MainUIRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	UIScale = Texture->GetScale();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();


	SetPos(float4{ 0.0f , WinScale.Y - UIScale.Y });


	MainUIRenderer->SetTexture(_FileName);
	MainUIRenderer->SetRenderPos(UIScale.Half());
	MainUIRenderer->SetRenderScale(UIScale);
}



// 초상화 초기 세팅
void UIManager::PortraitRendererSet(const float4& _RenderPos)
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



// 목숨 숫자 세팅
void UIManager::LivesNumberRendererSet(const float4& _Pos)
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
	First_LivesRenderer->SetRenderPos(_Pos + NumberScale.Half());
	First_LivesRenderer->SetRenderScale(NumberScale);


	Second_LivesRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount), 0.0f });
	Second_LivesRenderer->SetCopyScale(NumberScale);
	Second_LivesRenderer->SetRenderPos(_Pos + float4{ NumberScale.X , 0.0f } + NumberScale.Half());
	Second_LivesRenderer->SetRenderScale(NumberScale);
}






// 스태미나 숫자 세팅
void UIManager::StaminaCountRendererSet(const std::string& _FileName, const std::string& _Path, const float4& _StaminaFirstPos)
{
	// Sprite Scale
	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad(_FileName, _Path, 3, 1);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	float4 StaminaScale = Sprite->GetSprite(0).RenderScale;


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
		StaminaRenderer->CreateAnimation("StaminaRemain", _FileName, 0, 1, 0.6f, true);
		StaminaRenderer->ChangeAnimation("StaminaRemain");

		StaminaRenderer->SetRenderPos(_StaminaFirstPos + float4{ StaminaScale.X * static_cast<float>(i), 0.0f } + StaminaScale.Half());
		StaminaRenderer_vec.push_back(StaminaRenderer);
	}


	// 사운드
	GlobalContents::SoundFileLoad("Kirby_LowerHP.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Boss_StaminaFullSound.wav", "Resources\\SoundResources\\EffectVoice");
}





/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */




// 초상화 업데이트
void UIManager::PortraitState(float _Delta)
{
	if (0 == m_KirbySteminaCount)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
			return;
		}

		PortraitRenderer->ChangeAnimation("Portrait_Miss");
	}



	// 삼킴 초상화
	if (true == KirbyPtr->IsGulpEnemy)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
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
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
			return;
		}

		IsGulpPortraitDone = true;
		GulpPortraitTime = 0.0f;

		PortraitRenderer->ChangeAnimation("Portrait_Normal");
	}



	// 모드별 초상화
	int KirbyPtrMode = static_cast<int>(KirbyPtr->Mode);
	if (KirbyMode != KirbyPtrMode && AbilityStar::Max != KirbyPtr->Mode)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
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



// 죽었을 때 스테미나 
void UIManager::StaminaState()
{
	if (true == KirbyPtr->IsKirbyRevive)
	{
		// 라이프 1감소 
		--m_LivesCount;

		// Hp 초기화
		m_KirbySteminaCount = 6;


		for (int i = 0; i < StaminaRenderer_vec.size(); i++)
		{
			GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
			if (nullptr == StaminaRenderer)
			{
				MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
			}

			StaminaRenderer->On();
			StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { 0.6f , 0.6f };
			StaminaRenderer->FindAnimation("StaminaRemain")->CurInter = 0.0f;
			StaminaRenderer->FindAnimation("StaminaRemain")->CurFrame = 0;
		}


		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
			return;
		}

		PortraitRenderer->ChangeAnimation("Portrait_Normal");

		KirbyPtr->IsKirbyRevive = false;



		if (nullptr == Second_LivesRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
			return;
		}

		Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount), 0.0f });
	}

}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */




// 초상화 유지
void UIManager::LevelStartPortrait()
{
	if (nullptr == PortraitRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
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



// 목숨 유지
void UIManager::LevelStartLivesCount()
{
	if (nullptr == First_LivesRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (nullptr == Second_LivesRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	// 커비 목숨
	First_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount / 10), 0.0f });
	Second_LivesRenderer->SetCopyPos(float4{ NumberScale.X * static_cast<float>(m_LivesCount % 10), 0.0f });
}
