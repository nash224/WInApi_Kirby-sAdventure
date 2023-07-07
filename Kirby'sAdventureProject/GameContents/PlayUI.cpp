#include "PlayUI.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "GlobalContents.h"
#include "Kirby.h"
#include <vector>



int PlayUI::PlayUI_Score = 0;

PlayUI::PlayUI()
{
	UI = this;
}

PlayUI::~PlayUI()
{
}


void PlayUI::Start()
{
	HubRendererSet("MainUI.bmp", "Resources\\UI");
	LivesAniRendererSet();
	PortraitRendererSet(PORTRAITLOCATION);
	LivesNumberRendererSet();
	StaminaCountRendererSet("UI_LifeBar_3x1_24x42.bmp", "Resources\\UI", PLAY_STAMINAFIRSTNUMBERLOCATION);
	ScoreRendererSet();
}



// Lives 아이콘 로드
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
	LivesAniRenderer->SetRenderPos(Play_LIVESANILOCATION + LivesAniScale.Half());


}





// Lives 횟수 숫자 로드
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






// 점수 이미지 로드
void PlayUI::ScoreRendererSet()
{
	// 점수 1번째 자리
	GameEngineRenderer* First_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == First_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 2번째 자리
	GameEngineRenderer* Second_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Second_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 3번째 자리
	GameEngineRenderer* Third_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Third_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 4번째 자리
	GameEngineRenderer* Fourth_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fourth_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 5번째 자리
	GameEngineRenderer* Fifth_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Fifth_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 6번째 자리
	GameEngineRenderer* Sixth_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
	if (nullptr == Sixth_ScoreRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다..");
		return;
	}

	// 점수 7번째 자리
	GameEngineRenderer* Seventh_ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
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


	ScoreRenderer_vec.reserve(7);

	// Set Score Position and Render
	First_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	First_ScoreRenderer->SetCopyPos(float4::ZERO);
	First_ScoreRenderer->SetCopyScale(NumberScale);
	First_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + NumberScale.Half());
	First_ScoreRenderer->SetRenderScale(NumberScale);
	ScoreRenderer_vec.push_back(First_ScoreRenderer);



	Second_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Second_ScoreRenderer->SetCopyPos(float4::ZERO);
	Second_ScoreRenderer->SetCopyScale(NumberScale);
	Second_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X , 0.0f } + NumberScale.Half());
	Second_ScoreRenderer->SetRenderScale(NumberScale);
	ScoreRenderer_vec.push_back(Second_ScoreRenderer);



	Third_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Third_ScoreRenderer->SetCopyPos(float4::ZERO);
	Third_ScoreRenderer->SetCopyScale(NumberScale);
	Third_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 2.0f , 0.0f } + NumberScale.Half());
	Third_ScoreRenderer->SetRenderScale(NumberScale);
	ScoreRenderer_vec.push_back(Third_ScoreRenderer);



	Fourth_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Fourth_ScoreRenderer->SetCopyPos(float4::ZERO);
	Fourth_ScoreRenderer->SetCopyScale(NumberScale);
	Fourth_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 3.0f , 0.0f } + NumberScale.Half());
	Fourth_ScoreRenderer->SetRenderScale(NumberScale);
	ScoreRenderer_vec.push_back(Fourth_ScoreRenderer);



	Fifth_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Fifth_ScoreRenderer->SetCopyPos(float4::ZERO);
	Fifth_ScoreRenderer->SetCopyScale(NumberScale);
	Fifth_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 4.0f, 0.0f } + NumberScale.Half());
	Fifth_ScoreRenderer->SetRenderScale(NumberScale);
	ScoreRenderer_vec.push_back(Fifth_ScoreRenderer);



	Sixth_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Sixth_ScoreRenderer->SetCopyPos(float4::ZERO);
	Sixth_ScoreRenderer->SetCopyScale(NumberScale);
	Sixth_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 5.0f , 0.0f } + NumberScale.Half());
	Sixth_ScoreRenderer->SetRenderScale(NumberScale);
	ScoreRenderer_vec.push_back(Sixth_ScoreRenderer);



	Seventh_ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
	Seventh_ScoreRenderer->SetCopyPos(float4::ZERO);
	Seventh_ScoreRenderer->SetCopyScale(NumberScale);
	Seventh_ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * 6.0f , 0.0f } + NumberScale.Half());
	Seventh_ScoreRenderer->SetRenderScale(NumberScale);
	ScoreRenderer_vec.push_back(Seventh_ScoreRenderer);

}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void PlayUI::Update(float _Delta)
{
	PortraitState(_Delta);
	OuchState(_Delta);
	StaminaState();
	ScoreState();
}




// Ouch 로직
void PlayUI::OuchState(float _Delta)
{
	if (true == Ouch_State)
	{
		Ouch_Time += _Delta;
	}

	if (Ouch_Time > Ouch_Duration)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
			return;
		}


		Ouch_Time = 0.0f;
		Ouch_State = false;
		PortraitRenderer->ChangeAnimation("Portrait_Normal");
	}
	
	// 커비의 체력과 UI의 체력이 다르면
	if (m_KirbySteminaCount != KirbyPtr->m_KirbyHp && -1 != KirbyPtr->m_KirbyHp)
	{
		if (nullptr == PortraitRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못헀습니다.");
			return;
		}


		// 커비의 체력이 감소하면
		if (m_KirbySteminaCount > KirbyPtr->m_KirbyHp)
		{
			// 피가 0일때 모든 Hp Off
			if (0 == KirbyPtr->m_KirbyHp)
			{
				for (int i = 0; i < StaminaRenderer_vec.size(); i++)
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
				GameEngineRenderer * StaminaRenderer_Off = StaminaRenderer_vec[KirbyPtr->m_KirbyHp];
				if (nullptr == StaminaRenderer_Off)
				{
					MsgBoxAssert("렌더러를 불러오지 못했습니다.");
					return;
				}

				StaminaRenderer_Off->Off();


				for (int i = 0; i < KirbyPtr->m_KirbyHp; i++)
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


				Ouch_State = true;
				PortraitRenderer->ChangeAnimation("Portrait_OUCH");
			}

			m_KirbySteminaCount = KirbyPtr->m_KirbyHp;
		}

		// 커비의 체력이 증가하면
		if (m_KirbySteminaCount < KirbyPtr->m_KirbyHp && m_KirbySteminaCount < 6 && 6 != (KirbyPtr->m_KirbyHp - m_KirbySteminaCount))
		{
			Increase_Hp_Time += _Delta;

			if (Increase_Hp_Time > Increase_Hp_Cycle || false == IsIncresing_Hp)
			{
				Increase_Hp_Time = 0.0f;

				if (false == IsIncresing_Hp)
				{
					// 잠시 멈춤
					GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0.0f);
					GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0.0f);
					GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Ability, 0.0f);
					IsIncresing_Hp = true;
				}

				for (int i = 0; i < m_KirbySteminaCount + 1; i++)
				{
					GameEngineRenderer* StaminaRenderer = StaminaRenderer_vec[i];
					if (nullptr == StaminaRenderer)
					{
						MsgBoxAssert("렌더러를 불러오지 못했습니다.");
						return;
					}


					StaminaRenderer->On();

					// 스태미나 렌더러 일부 변수 초기화
					float Stamina_Inter = 0.1f * static_cast<float>(KirbyPtr->m_KirbyHp);
					StaminaRenderer->FindAnimation("StaminaRemain")->Inters = { Stamina_Inter , Stamina_Inter };
					StaminaRenderer->FindAnimation("StaminaRemain")->CurInter = 0.0f;
					StaminaRenderer->FindAnimation("StaminaRemain")->CurFrame = 0;
				}

				++m_KirbySteminaCount;

				PlayUI_Score += 1000;
				GameEngineSound::SoundPlay("Boss_StaminaFullSound.wav");


				if (m_KirbySteminaCount == KirbyPtr->m_KirbyHp)
				{
					// 시간 정지 해제
					GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
					IsIncresing_Hp = false;
				}
			}
		}
	}
}


// 0 번째 요소 : 1의 자리수 = Score % 10 또는 Score / 1 % 10
// 1 번째 요소 : 10의 자리수 = Score % 100 / 10 또는 Score / 10 % 10
// 2 번째 요소 : 100의 자리수 = Score % 1000 / 100 또는 Score / 100 % 10

// 점수 Update
void PlayUI::ScoreState()
{
	if (PlayUI_Score == RenderScore)
	{
		return;
	}

	// 점수 렌더링
	for (int i = 0; i < ScoreRenderer_vec.size(); i++)
	{
		GameEngineRenderer* ScoreRendererPtr = ScoreRenderer_vec[i];
		if (nullptr == ScoreRendererPtr)
		{
			MsgBoxAssert("벡터 참조 영역을 벗어났습니다.");
			return;
		}

		size_t Digit = ScoreRenderer_vec.size() - i;

		size_t Pow = 1;

		for (size_t j = 1; j < Digit; j++)
		{
			Pow *= 10;
		}


		int DigitNumber = static_cast<int>(PlayUI_Score / Pow % 10);

		ScoreRendererPtr->SetCopyPos(float4{ NumberScale.X * DigitNumber , 0.0f });
	}

	RenderScore = PlayUI_Score;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



// 다음 레벨로 넘어갈 때 유지
void PlayUI::LevelStart()
{
	UI = this;

	LevelStartPortrait();
	LevelStartStamina();
	LevelStartLivesCount();
}



void PlayUI::LevelStartStamina()
{
	KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Kirby가 Null 입니다.");
		return;
	}


	// 커비 체력
	for (int i = KirbyPtr->m_KirbyHp; i < StaminaRenderer_vec.size(); i++)
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



