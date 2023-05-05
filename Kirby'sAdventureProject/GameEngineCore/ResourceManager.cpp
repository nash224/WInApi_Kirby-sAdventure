#include "ResourceManager.h"
#include "GameEngineTexture.h"
#include <GameEngineBase/GameEngineString.h>
#include <string>


ResourceManager ResourceManager::Inst;
ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager() 
{
	for (const std::pair<std::string, GameEngineTexture*>& Pair : AllTexture)
	{
		GameEngineTexture* Texture = Pair.second;

		if (nullptr != Texture)
		{
			delete Texture;
			Texture = nullptr;
		}
	}
}


bool ResourceManager::IsLoadTexture(const std::string& _Name)
{
	return FindTexture(_Name) != nullptr;
}

GameEngineTexture* ResourceManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineTexture*>::iterator FindIter = AllTexture.find(UpperName);

	if (FindIter == AllTexture.end())
	{
		return nullptr;
	}

	return FindIter->second;
}


void ResourceManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperString = GameEngineString::ToUpperReturn(_Name);

	GameEngineTexture* NewTexture = new GameEngineTexture();

	// 객체에 경로를 담음
	NewTexture->LoadResource(_Path);

	AllTexture.insert(std::make_pair(UpperString, NewTexture));
}
