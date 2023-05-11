#include "GameEngineRenderer.h"
#include "ResourceManager.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}


void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourceManager::GetInst().FindTexture(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert(_Name + "�� �������� �ʽ��ϴ�.");
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}
}

void GameEngineRenderer::SetRenderScaleToTexture()
{
	RenderScale = Texture->GetScale();
	ScaleCheck = false;
}


void GameEngineRenderer::Render(class GameEngineCamera* _Camera)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("�������� �̹����� �������� �ʽ��ϴ�.");
	}

	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos, CopyScale);
}