#include "BackGround.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourceManager.h>
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

}

void BackGround::Update(float _Delta)
{
}

void BackGround::Render()
{
}

void BackGround::Release()
{

}


void BackGround::init(const std::string& _FileName, const std::string& _Path, float4 _CopyPos, float4 _CopyScale)
{
	ResourceManager::GetInst().LoadTextureFile(_FileName, _Path);

	float4 Scale = _CopyScale;

	//GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);
	Renderer = CreateRenderer(_FileName, RenderOrder::BackGround);
	Renderer->SetCopyPos(_CopyPos);
	Renderer->SetCopyScale(Scale);

	Scale.X *= 3.0f;
	Scale.Y *= 3.0f;
		
	SetPos(Scale.GetHalf());
	SetScale(Scale);
	Renderer->SetRenderScale(Scale);
}