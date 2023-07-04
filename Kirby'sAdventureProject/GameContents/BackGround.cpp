#include "BackGround.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>

#pragma comment(lib, "msimg32.lib")

#include "GlobalContents.h"
#include "VegetableValleyPlayLevel.h"
#include "Boss.h"



int BackGround::BossStage = 0;
BackGround::BackGround() 
{
}

BackGround::~BackGround() 
{
}


void BackGround::Start()
{
	Renderer = CreateRenderer(RenderOrder::BackGround);
	DebugRenderer = CreateRenderer(RenderOrder::BackGround);

	Renderer->On();
	DebugRenderer->Off();
}



void BackGround::init(const std::string& _FileName, const std::string& _Path)
{
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();

	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}


	Renderer->SetTexture(_FileName);
	Renderer->SetCopyScale(BackGroundScale);
	
	SetPos(BackGroundScale.Half());
	Renderer->SetRenderScale(BackGroundScale);
}


GameEngineWindowTexture* BackGround::init(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path)
{
	static GameEngineWindowTexture* ReturnValue;

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad(_FileName, _Path);
	GlobalContents::TextureFileLoad(_DebugFileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return ReturnValue;
	}

	float4 Scale = Texture->GetScale();



	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return ReturnValue;
	}

	if (nullptr == DebugRenderer)
	{
		MsgBoxAssert("디버그 렌더러를 불러오지 못했습니다.");
		return ReturnValue;
	}


	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);

	SetPos(Scale.Half());

	return Texture;
}

GameEngineRenderer* BackGround::SpriteInit(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path, int _XCount, int _YCount)
{
	static GameEngineRenderer* ReturnValue;

	GlobalContents::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad(_DebugFileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return ReturnValue;
	}
	
	float4 Scale = Texture->GetScale();


	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return ReturnValue;
	}

	if (nullptr == DebugRenderer)
	{
		MsgBoxAssert("디버그 렌더러를 불러오지 못했습니다.");
		return ReturnValue;
	}


	Renderer->SetSprite(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);

	SetPos(Scale.Half());

	return Renderer;
}



void BackGround::ExtraMapSet(const std::string& _FileName, const std::string& _Path)
{
	GlobalContents::TextureFileLoad(_FileName, _Path);
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void BackGround::Update(float _Delta)
{
	if (true == IsBossChangeMap)
	{
		switch (BossStage)
		{
		case 1:
			WhispyChangeMap(_Delta);
			break;
		case 2:
			break;
		default:
			break;
		}
	}

}


void BackGround::SwitchRender()
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("배경 렌더러를 불러오지 못했습니다.");
		return;
	}

	if (nullptr == DebugRenderer)
	{
		return;
	}

	if (false == VegetableValleyPlayLevel::Level_SwitchBitMapRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else 
	{
		Renderer->Off();
		DebugRenderer->On();
	}
}



void BackGround::WhispyChangeMap(float _Delta)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("배경 렌더러를 불러오지 못했습니다.");
		return;
	}


	Whispy_ChangeMap_Time += _Delta;

	if (Whispy_ChangeMap_Time > Whispy_ChangeMap_Cycle)
	{
		Whispy_ChangeMap_Time = 0.0f;

		switch (Whispy_ChangeMap_Number % 4)
		{
		case 0:
			Renderer->SetTexture("VegetableValleyP_Black.bmp");
			break;
		case 1:
			Renderer->SetTexture("VegetableValleyP_Orange_Black.bmp");
			break;
		case 2:
			Renderer->SetTexture("VegetableValleyP.bmp");
			break;
		default:
			break;
		}


		++Whispy_ChangeMap_Number;
	}

	if (27 == Whispy_ChangeMap_Number)
	{
		Boss* WhispyWoodPtr = Boss::GetMainBossPtr();
		if (nullptr == WhispyWoodPtr)
		{
			MsgBoxAssert("보스를 불러오지 못했습니다.");
			return;
		}

		WhispyWoodPtr->BossChangeMapPattern = true;

		IsBossChangeMap = false;
	}
}