#include "BackGround.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourceManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourceManager.h>


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
	ResourceManager::GetInst().LoadTextureFile(_FileName, _Path);

	GameEngineWindowTexture* Texture = ResourceManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();

	Renderer->SetTexture(_FileName);
	Renderer->SetCopyScale(Scale);
	
	SetPos(Scale.GetHalf());
	SetScale(Scale);
	Renderer->SetRenderScale(Scale);
}

void BackGround::init(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path)
{
	ResourceManager::GetInst().LoadTextureFile(_FileName, _Path);
	ResourceManager::GetInst().LoadTextureFile(_DebugFileName, _Path);

	GameEngineWindowTexture* Texture = ResourceManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();

	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);

	SetPos(Scale.GetHalf());
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