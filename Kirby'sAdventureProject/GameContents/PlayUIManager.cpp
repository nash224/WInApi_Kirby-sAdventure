#include "PlayUIManager.h"

#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>

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
	// ��ġ�� �ű��� �ʾҴ�.
	// GetPos();
	// ī�޶� �ȿ�����

	//{
	//	GameEngineRenderer* Ptr = CreateUIRenderer("HPBar.bmp", RenderOrder::Play);
	//	Ptr->SetRenderPos({ 100, 100 });
	//	Ptr->SetRenderScale({ 40, 40 });
	//	Ptr->SetTexture("HPBar.bmp");
	//}
}