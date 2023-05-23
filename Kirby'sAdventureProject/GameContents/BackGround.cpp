#include "BackGround.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>


#pragma comment(lib, "msimg32.lib")

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
	ResourcesManager::GetInst().TextureFileLoad(_FileName, _Path);

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();

	Renderer->SetTexture(_FileName);
	Renderer->SetCopyScale(Scale);
	
	SetPos(Scale.Half());
	Renderer->SetRenderScale(Scale);
}


void BackGround::init(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path)
{
	ResourcesManager::GetInst().TextureFileLoad(_FileName, _Path);
	ResourcesManager::GetInst().TextureFileLoad(_DebugFileName, _Path);

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();

	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);

	SetPos(Scale.Half());
}

GameEngineRenderer* BackGround::SpriteInit(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path, int _XCount, int _YCount)
{
	ResourcesManager::GetInst().SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	ResourcesManager::GetInst().TextureFileLoad(_DebugFileName, _Path);


	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_DebugFileName);
	float4 Scale = Texture->GetScale();

	Renderer->SetSprite(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);

	SetPos(Scale.Half());

	return Renderer;
}


void BackGround::Update(float _Delta)
{
}


void BackGround::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else {
		Renderer->Off();
		DebugRenderer->On();
	}
}