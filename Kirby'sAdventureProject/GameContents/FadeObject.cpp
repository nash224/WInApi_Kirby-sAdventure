#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"


bool FadeObject::IsFadeOutScreenRelease = false;
bool FadeObject::IsFadeScreenRelease = false; 
bool FadeObject::IsFadeDone = false;

float FadeObject::TimeRaito = 1.0f;


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
	MainRenderer->On();

}


void FadeObject::Update(float _Delta)
{
	ChangeFadeAlphaTime += _Delta;

	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	// Fade 를 요청받았을 때
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


	if (true == IsFadeScreen)
	{
		FadeScreen(_Delta);
	}
}





void FadeObject::FadeOut(float _Delta)
{
	// 간격마다
	if (ChangeFadeAlphaTime > ChangeFadeOutAlphaDuration * TimeRaito && FadeNumber <=1 )
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



		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("렌더러가 Null 입니다.");
			return;
		}

		// 알파값 설정
		MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));

	}


	if (FadeNumber >= 2 && true == IsFadeOutScreenRelease)
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
	if (ChangeFadeAlphaTime > ChangeFadeInAlphaDuration * TimeRaito && FadeNumber <= 2)
	{
		ChangeFadeAlphaTime = 0.0f;

		++FadeNumber;



		switch (FadeNumber)
		{
		case 0:
			AlphaCount = 255;
			break;
		case 1:
			AlphaCount = 128;
			break;
		case 2:
			AlphaCount = 55;
			break;
		case 3:
			AlphaCount = 0;
			break;
		default:
			break;
		}



		if (nullptr == MainRenderer)
		{
			MsgBoxAssert("렌더러가 Null 입니다.");
			return;
		}

		// 설정
		MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));
	}


	if (FadeNumber >= 3)
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





void FadeObject::RequestFadeIn()
{
	IsChangeFade = true;
	IsFadeOut = false;

	AlphaCount = 255;
	MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));
}

void FadeObject::RequestFadeOut()
{
	IsChangeFade = true;
	IsFadeOut = true;
	IsFadeOutScreenRelease = false;

	AlphaCount = 0;
	MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));
}



void FadeObject::Request_WhiteFadeIn()
{
	RequestFadeIn();


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	MainRenderer->SetTexture("WhiteFade.bmp");
}


void FadeObject::Request_WhiteFadeOut()
{
	RequestFadeOut();


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	MainRenderer->SetTexture("WhiteFade.bmp");
}


void FadeObject::RequestFadeScreen(int _AlphaCount /*= 0*/)
{
	IsFadeScreen = true;
	IsFadeScreenRelease = false;

	AlphaCount = _AlphaCount;


	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

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