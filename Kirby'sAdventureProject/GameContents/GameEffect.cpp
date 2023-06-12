#include "GameEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "GlobalContents.h"


GameEffect::GameEffect()
{
}

GameEffect::~GameEffect()
{
}


void GameEffect::LoadBackGroundEffect(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	GlobalContents::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
}

void GameEffect::Update(float _Delta)
{

}