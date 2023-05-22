#include "GameEngineActor.h"

#include <GameEngineBase/GameEngineDebug.h>

#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"

GameEngineActor::GameEngineActor() 
{
}

GameEngineActor::~GameEngineActor() 
{
	for (GameEngineRenderer* Renderer : AllRenderer)
	{
		if (nullptr != Renderer)
		{
			delete Renderer;
			Renderer = nullptr;
		}
	}

	for (GameEngineCollision* Collision : AllCollision)
	{
		if (nullptr != Collision)
		{
			delete Collision;
			Collision = nullptr;
		}
	}
}


GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, int _Order)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	// ���� ������ ����ī�޶� ������ ��Ҹ� �������� ����
	GetLevel()->MainCamera->PushRenderer(NewRenderer, _Order);

	NewRenderer->Master = this;
	NewRenderer->Start();
	NewRenderer->SetOrder(_Order);

	if (_ImageName != "")
	{
		NewRenderer->SetTexture(_ImageName);
	}

	AllRenderer.push_back(NewRenderer);

	return NewRenderer;
}

void GameEngineActor::ActorRelease()
{
	std::list<GameEngineRenderer*>::iterator ObjectStartIter = AllRenderer.begin();
	std::list<GameEngineRenderer*>::iterator ObjectEndIter = AllRenderer.end();
	
	for (; ObjectStartIter != ObjectEndIter;)
	{
		GameEngineRenderer* Renderer = *ObjectStartIter;
		if (false == Renderer->IsDeath())
		{
			++ObjectStartIter;
			continue;
		}

		if (nullptr == Renderer)
		{
			MsgBoxAssert(" nullptr�� ���Ͱ� ������ ����Ʈ�� �� �־����ϴ�. ");
			return;
		}

		delete Renderer;
		Renderer = nullptr;

		ObjectStartIter = AllRenderer.erase(ObjectStartIter);
	}
}


GameEngineCollision* GameEngineActor::CreateCollision(int _Order/* = 0*/)
{
	GameEngineCollision* NewCollision = new GameEngineCollision();

	NewCollision->Master = this;
	NewCollision->Start();
	NewCollision->SetOrder(_Order);
	
	AllCollision.push_back(NewCollision);

	return NewCollision;
}