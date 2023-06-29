#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"


bool FadeObject::IsFadeScreenRelease = false; 
bool FadeObject::IsFadeDone = false;


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

	GlobalContents::TextureFileLoad("WhiteFade.bmp", "Resources\\Other");
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
	if (true == IsChangeFade)
	{
		if (true == IsFadeOut)
		{
			FadeOut(_Delta);
		}
		else if (false == IsFadeOut)
		{
			FadeIn(_Delta);
		}
	}


	// WhiteFadeOut을 요청받았을 때
	if (true == IsChangeWhiteFade)
	{
		if (true == IsFadeOut)
		{
			White_FadeOut(_Delta);
		}
		else if (false == IsFadeOut)
		{
			White_FadeIn(_Delta);
		}
	}

	if (true == IsFadeScreen)
	{
		FadeScreen(_Delta);
	}
}





void FadeObject::FadeOut(float _Delta)
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


	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return;
	}




	if (FadeNumber >= 2 && false == KirbyPtr->IsFadeOut)
	{
		Death();
		if (nullptr != MainRenderer)
		{
			MainRenderer = nullptr;
		}
	}
}


void FadeObject::FadeIn(float _Delta)
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


	if (FadeNumber >= 2)
	{
		Death();
		if (nullptr != MainRenderer)
		{
			MainRenderer = nullptr;
		}
	}

}




void FadeObject::White_FadeOut(float _Delta)
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


	if (FadeNumber >= 2 && true == IsFadeDone)
	{
		Death();
		if (nullptr != MainRenderer)
		{
			MainRenderer = nullptr;
		}
	}
}


void FadeObject::White_FadeIn(float _Delta)
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


	if (FadeNumber >= 2)
	{
		Death();
		if (nullptr != MainRenderer)
		{
			MainRenderer = nullptr;
		}
	}

}





void FadeObject::FadeScreen(float _Delta)
{

	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return;
	}


	if (true == IsFadeScreenRelease)
	{
		IsFadeScreenRelease = false;

		Death();
		if (nullptr != MainRenderer)
		{
			MainRenderer = nullptr;
		}
		return;
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



void FadeObject::Request_WhiteFadeIn()
{
	IsChangeWhiteFade = true;
	IsFadeOut = false;

	AlphaCount = 0;

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	MainRenderer->SetTexture("WhiteFade.bmp");
}

void FadeObject::Request_WhiteFadeOut()
{
	IsChangeWhiteFade = true;
	IsFadeOut = true;

	AlphaCount = 255;

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	MainRenderer->SetTexture("WhiteFade.bmp");
}


void FadeObject::RequestFadeScreen(int _AlphaCount /*= 0*/)
{
	IsFadeScreen = true;
	IsFadeScreenRelease = false;

	AlphaCount = _AlphaCount;
	MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));
}



void FadeObject::LevelEnd()
{
	Death();
	if (nullptr != MainRenderer)
	{
		MainRenderer = nullptr;
	}
}