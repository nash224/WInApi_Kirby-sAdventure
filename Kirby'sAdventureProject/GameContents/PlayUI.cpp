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
	LivesNumberRendererSet(PLAY_LIVESFIRSTNUMBERLOCATION);
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




// 점수 이미지 로드
void PlayUI::ScoreRendererSet()
{
	ScoreRenderer_vec.reserve(ScoreRenderer);
	for (size_t i = 0; i < ScoreRenderer; i++)
	{
		GameEngineRenderer* ScoreRenderer = CreateUIRenderer(RenderOrder::PlayUI);
		if (nullptr == ScoreRenderer)
		{
			MsgBoxAssert("렌더러가 Null 입니다..");
			return;
		}

		ScoreRenderer->SetTexture("UI_Number_10x1_24x24.bmp");
		ScoreRenderer->SetCopyPos(float4::ZERO);
		ScoreRenderer->SetCopyScale(NumberScale);
		ScoreRenderer->SetRenderPos(PLAY_SCOREFIRSTNUMBERLOCATION + float4{ NumberScale.X * static_cast<float>(i) , 0.0f} + NumberScale.Half());
		ScoreRenderer->SetRenderScale(NumberScale);
		ScoreRenderer_vec.push_back(ScoreRenderer);
	}
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



