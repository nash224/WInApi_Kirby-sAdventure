#include "BackGround.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourceManager.h>


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
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	GameEngineWindowTexture* FindTexture = ResourceManager::GetInst().FindTexture(FileName);
	BackBuffer->BitCopy(FindTexture, GetPos());
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

		SetScale(Scale);
	}
}