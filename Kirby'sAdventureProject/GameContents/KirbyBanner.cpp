#include "KirbyBanner.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>



KirbyBanner::KirbyBanner()
{
}

KirbyBanner::~KirbyBanner()
{
}


void KirbyBanner::Start()
{
	// 렌더러 생성
	KirbyRenderer = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == KirbyRenderer)
	{
		MsgBoxAssert("생성한 렌더러가 NUll입니다.");
		return;
	}

	// 파일로드
	GlobalContents::SpriteFileLoad("Title_Kirby_Banner.bmp", "Resources\\Unit\\Object", 3, 1);


	// 애니메이션 생성 및 적용
	KirbyRenderer->CreateAnimation("Idle", "Title_Kirby_Banner.bmp", 1, 1, 0.04f, false);
	KirbyRenderer->CreateAnimationToFrame("WaveHand", "Title_Kirby_Banner.bmp", { 2, 1, 2, 1}, 0.06f, false);
	KirbyRenderer->CreateAnimation("BlinkEyes", "Title_Kirby_Banner.bmp", 0, 1, 0.04f, false);
	KirbyRenderer->ChangeAnimation("Idle");

	NextStateStart = 1.0f;

	CurName = "Max";

	IsStateDone = true;
}


// 외부) 초기 설정
void KirbyBanner::init(const float4& _Pos)
{
	SetPos(_Pos);
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void KirbyBanner::Update(float _Delta)
{
	State_Queue(_Delta);
	StateUpdate(_Delta);
}


// 메세지 큐
void KirbyBanner::State_Queue(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > NextStateStart)
	{
		StateTime = 0.0f;
		NextStateStart = GameEngineRandom::MainRandom.RandomFloat(StateStart_MinTime, StateStart_MaxTime);


		int StateNumber = GameEngineRandom::MainRandom.RandomInt(0, 3) / 3;
		StateData.push_back(StateNumber);
	}


	if (true == IsStateDone && 0 != StateData.size())
	{
		int StateNumber = StateData.front();

		switch (StateNumber)
		{
		case 0:
			CurState = BannerState::WaveHand;
			WaveHandStart();
			break;
		case 1:
			CurState = BannerState::BlinkEyes;
			BlinkEyesStart();
			break;
		default:
			break;
		}

		StateData.pop_front();

		IsStateDone = false;
	}
}


// 행동 업데이트
void KirbyBanner::StateUpdate(float _Delta)
{
	switch (CurState)
	{
	case BannerState::WaveHand:
		WaveHandUpdate(_Delta);
		break;
	case BannerState::BlinkEyes:
		BlinkEyesUpdate(_Delta);
		break;
	default:
		break;
	}
}


// 행동 변환
void KirbyBanner::ChangeStateAndAnimation(const std::string& _StateName)
{
	if (nullptr == KirbyRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	CurName = _StateName;
	KirbyRenderer->ChangeAnimation(_StateName, 0, true);
}


// 손인사 패턴
void KirbyBanner::WaveHandStart()
{
	ChangeStateAndAnimation("WaveHand");
}

// 손인사 업데이트
void KirbyBanner::WaveHandUpdate(float _Delta)
{
	if (nullptr == KirbyRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (true == KirbyRenderer->IsAnimationEnd())
	{
		IsStateDone = true;
		return;
	}
}


// 눈 깜빡 패턴
void KirbyBanner::BlinkEyesStart()
{
	ChangeStateAndAnimation("BlinkEyes");
}

// 눈 깜빡 업데이트
void KirbyBanner::BlinkEyesUpdate(float _Delta)
{
	if (nullptr == KirbyRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (true == KirbyRenderer->IsAnimationEnd())
	{
		IsStateDone = true;
		return;
	}
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void KirbyBanner::Render(float _Delta)
{
	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("백버퍼를 불러오지 못했습니다.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();

	{
		std::string Text = "";

		Text += "다음 상태까지 남은 시간 : ";

		Text += std::to_string(NextStateStart - StateTime);
		TextOutA(dc, 2, 2, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		std::string Text = "";

		Text += "큐 Size : ";

		Text += std::to_string(StateData.size());
		TextOutA(dc, 2, 18, Text.c_str(), static_cast<int>(Text.size()));
	}


	{
		std::string Text = "";

		Text += "메세지 큐 : ";

		for (int Number : StateData)
		{
			std::string StateName = "";

			switch (Number)
			{
			case 0:
				StateName = "WaveHand ";
				break;
			case 1:
				StateName = "BlinkEyes ";
				break;
			default:
				break;
			}

			Text += StateName;

			
		}

		TextOutA(dc, 2, 34, Text.c_str(), static_cast<int>(Text.size()));
	}


	{
		std::string Text = "";

		Text += "현재 상태 : ";

		Text += CurName;
		TextOutA(dc, 2, 50, Text.c_str(), static_cast<int>(Text.size()));
	}

}
