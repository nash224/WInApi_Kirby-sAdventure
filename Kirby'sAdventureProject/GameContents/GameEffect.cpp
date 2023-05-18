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


void GameEffect::init(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	ResourceManager::GetInst().LoadSpriteFile(_FileName, _Path, _XCount, _YCount);
}

GameEngineRenderer* GameEffect::CreateEffectRenderer(int _Order)
{
	EffectRenderer = CreateRenderer(_Order);

	return EffectRenderer;
}


void GameEffect::Start() 
{

}

void GameEffect::Update(float _Delta)
{

}