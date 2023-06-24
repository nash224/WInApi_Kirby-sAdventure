#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"





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
		MsgBoxAssert("������ �������� NUll�Դϴ�.");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("FadeOut.bmp", "Resources\\Other");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
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
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}

	// FadeOut�� ��û�޾��� ��
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


void FadeObject::FadeOut(float _Delta)
{
	// ���ݸ���
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


		// ���İ� ����
		MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));

	}


	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Ŀ�� �ҷ����� ���߽��ϴ�.");
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
	// 0.04f�� ����
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


		// ����
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




void FadeObject::RequestFadeScreen(int _AlphaCount /*= 0*/)
{
	IsFadeScreen = true;

	AlphaCount = _AlphaCount;

	MainRenderer->SetAlpha(static_cast<unsigned char>(AlphaCount));
}


void FadeObject::FadeScreen(float _Delta)
{

	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Ŀ�� �ҷ����� ���߽��ϴ�.");
		return;
	}


	if (true == KirbyPtr->IsFadeScreenRelease)
	{
		KirbyPtr->IsFadeScreenRelease = false;

		Death();
		if (nullptr != MainRenderer)
		{
			MainRenderer = nullptr;
		}
		return;
	}
}