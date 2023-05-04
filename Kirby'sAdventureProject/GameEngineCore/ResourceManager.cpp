#include "ResourceManager.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>
#include <string>


ResourceManager ResourceManager::Inst;
ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager() 
{
}


bool ResourceManager::IsLoadTexture(const std::string& _Name)
{
	//return FindTexture(_Name) != nullptr;
	return false;
}

//
//GameEngineTexture* ResourceManager::FindTexture(const std::string& _Name)
//{
//	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
//
//	GameEnginePath FilePath;
//	FilePath.GetCurrentPath();
//
//}
