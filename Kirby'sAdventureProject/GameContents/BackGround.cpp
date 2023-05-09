#include "BackGround.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
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
	SetPos({ 640, 360 });
}

void BackGround::Update(float _Delta)
{

}

void BackGround::Render()
{
	GameEngineWindowTexture* FindTexture = ResourceManager::GetInst().FindTexture(FileName);

	if (nullptr == FindTexture)
	{
		return;
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	
	float4 Scale = FindTexture->GetScale();

	Scale *= 2.0f;

	//                    그림의 HDC , 위치    , 확대  , 입력장치의 시작위치, 입력 장치의 끝위치
	BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());
}

void BackGround::Release()
{

}


void BackGround::init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourceManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\KirbyTest\\" + _FileName);
		GameEngineWindowTexture* Texture = ResourceManager::GetInst().TextureLoad(FilePath.GetStringPath());

		float4 Scale = Texture->GetScale();

		Scale.X *= 8.0f;
		Scale.Y *= 8.0f;

		SetScale(Scale);
	}
}