#include "BackGround.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourceManager.h>
#include <GameEngineCore/GameEngineRenderer.h>


#pragma comment(lib, "msimg32.lib")

BackGround::BackGround() 
{
}

BackGround::~BackGround() 
{
}


void BackGround::Start()
{
	SetPos(GameEngineWindow::MainWindow.GetScale().GetHalf());
	//SetPos({ 1714, 792 });
}

void BackGround::Update(float _Delta)
{

}

void BackGround::Render()
{
	//GameEngineWindowTexture* FindTexture = ResourceManager::GetInst().FindTexture(FileName);

	//if (nullptr == FindTexture)
	//{
	//	return;
	//}

	//GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();
	//
	//float4 Scale = FindTexture->GetScale();

	//Scale *= 2.0f;

	////                    그림의 HDC , 위치    , 크기  , 입력장치의 시작위치, 입력 장치의 끝위치
	//BackBuffer->TransCopy(FindTexture, GetPos(), Scale, { 0,0 }, FindTexture->GetScale());
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

		Scale.X *= 3.0f;
		Scale.Y *= 3.0f;

		//SetScale(Scale);

		GameEngineRenderer* Render = CreateRenderer(_FileName, RenderOrder::BackGround);
		Render->SetRenderScale(Scale);

	}
}