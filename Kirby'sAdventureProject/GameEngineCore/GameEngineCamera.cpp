#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineCamera::GameEngineCamera() 
{
}

GameEngineCamera::~GameEngineCamera() 
{
}

void GameEngineCamera::Render(float _Delta)
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& List = GroupStartIter->second;

		std::list<GameEngineRenderer*>::iterator RenderStartIter = List.begin();
		std::list<GameEngineRenderer*>::iterator RenderEndIter = List.end();

		for (; RenderStartIter != RenderEndIter; ++RenderStartIter)
		{
			GameEngineRenderer* Render = *RenderStartIter;

			if (false == Render->IsUpdate())
			{
				continue;
			}

			Render->Render(this, _Delta);
		}
	}
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer, int _Order)
{
	if (nullptr == _Renderer)
	{
		MsgBoxAssert("NULL인 랜더러는 그룹에 속할 수 없습니다.");
	}

	Renderers[_Order].push_back(_Renderer);
}


void GameEngineCamera::Release()
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();

	std::list<GameEngineRenderer*>::iterator ActorStartIter;
	std::list<GameEngineRenderer*>::iterator ActorEndIter;

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& Group = GroupStartIter->second;

		ActorStartIter = Group.begin();
		ActorEndIter = Group.end();

		for (; ActorStartIter != ActorEndIter;)
		{
			GameEngineRenderer* Object = *ActorStartIter;

			if (nullptr == Object)
			{
				MsgBoxAssert("nullptr인 객체가 레벨의 리스트에 들어가 있습니다.");
				return;
			}

			if (false == Object->IsDeath())
			{
				++ActorStartIter;
				continue;
			}

			ActorStartIter = Group.erase(ActorStartIter);
		}
	}
}