#include "GameEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourceManager.h>
#include <GameEngineCore/GameEngineSprite.h>


GameEffect::GameEffect()
{
}

GameEffect::~GameEffect()
{
}


GameEngineRenderer* GameEffect::init(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	ResourceManager::GetInst().LoadSpriteFile(_FileName, _Path, _XCount, _YCount);

	EffectRenderer = CreateRenderer(RenderOrder::BackGroundEffect);

	return EffectRenderer;
}


void GameEffect::Start() 
{

}

void GameEffect::Update(float _Delta)
{

}