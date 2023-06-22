#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "VegetableValleyPlayLevel.h"





FadeObject::FadeObject()
{
}

FadeObject::~FadeObject()
{
}


void FadeObject::Start()
{
	MainRenderer = CreateUIRenderer(RenderOrder::Fade);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("생성한 렌더러가 NUll입니다.");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("FadeOut.bmp", "Resources\\Other");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	MainRenderer->SetTexture("FadeOut.bmp");


	float4 FadeScale = Texture->GetScale();
	MainRenderer->SetRenderPos(FadeScale.Half());

	MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));

}


void FadeObject::Update(float _Delta)
{
	ChangeFadeAlphaTime += _Delta;

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	// FadeOut을 요청받았을 때
	if (true == IsChangeFade && true == IsFadeOut)
	{
		// 간격마다
		if (ChangeFadeAlphaTime > ChangeFadeAlphaDuration)
		{
			ChangeFadeAlphaTime = 0.0f;
			++FadeNumber;

			switch (FadeNumber)
			{
			case 0:
				AlphaCount = 128;
				break;
			case 1:
				AlphaCount = 200;
				break;
			case 2:
				AlphaCount = 255;
				break;
			default:
				break;
			}
			

			// 알파값 설정
			MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));

		}

		if (2 == FadeNumber)
		{
			Death();
			if (nullptr != MainRenderer)
			{
				MainRenderer = nullptr;
			}
		}
	}
	else if (true == IsChangeFade && false == IsFadeOut)
	{
		// 0.04f초 마다
		if (ChangeFadeAlphaTime > ChangeFadeAlphaDuration)
		{
			ChangeFadeAlphaTime = 0.0f;

			++FadeNumber;



			switch (FadeNumber)
			{
			case 0:
				AlphaCount = 128;
				break;
			case 1:
				AlphaCount = 55;
				break;
			case 2:
				AlphaCount = 0;
				break;
			default:
				break;
			}



			// 설정
			MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));

		}

		if (2 == FadeNumber)
		{
			Death();
			if (nullptr != MainRenderer)
			{
				MainRenderer = nullptr;
			}
		}
	}
}



void FadeObject::RequestFadeOut()
{
	IsChangeFade = true;
	IsFadeOut = true;

	AlphaCount = 0;
}

void FadeObject::RequestFadeIn()
{
	IsChangeFade = true;
	IsFadeOut = false;

	AlphaCount = 255;
}