#include "PlayUIManager.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "GlobalContents.h"


PlayUIManager* PlayUIManager::UI = nullptr;

PlayUIManager::PlayUIManager()
{
	UI = this;
}

PlayUIManager::~PlayUIManager()
{
}

void PlayUIManager::Start()
{
	MainUIRenderer = CreateUIRenderer(RenderOrder::PlayUI);


	//{
	//	GameEngineRenderer* Ptr = CreateUIRenderer("HPBar.bmp", RenderOrder::Play);
	//	Ptr->SetRenderPos({ 100, 100 });
	//	Ptr->SetRenderScale({ 40, 40 });
	//	Ptr->SetTexture("HPBar.bmp");
	//}
}


void PlayUIManager::init(const std::string& _FileName, const std::string& _Path)
{
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("UI 텍스처가 널일리가 없어");
		return;
	}

	UIScale = Texture->GetScale();
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	MainUIRenderer->SetTexture(_FileName);
	MainUIRenderer->SetRenderScale(UIScale);
	SetPos(float4{ WinScale.Half().X , WinScale.Y - UIScale.Half().Y});
}


void PlayUIManager::Update(float _Delta)
{

}

void PlayUIManager::Render(float _Delta)
{

}

void PlayUIManager::LevelStart()
{
	UI = this;
}