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

}

void BackGround::init(const std::string& _FileName, const std::string& _Path)
{
	ResourceManager::GetInst().LoadTextureFile(_FileName, _Path);

	GameEngineWindowTexture* Texture = ResourceManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();


	//GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);
	Renderer->SetTexture(_FileName);
	Renderer->SetCopyScale(Scale);

	Scale.X *= 3.0f;
	Scale.Y *= 3.0f;
		
	SetPos(Scale.GetHalf());
	SetScale(Scale);
	Renderer->SetRenderScale(Scale);
}



void BackGround::Update(float _Delta)
{
}