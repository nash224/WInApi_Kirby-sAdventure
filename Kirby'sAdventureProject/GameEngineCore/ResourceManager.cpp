#include "ResourceManager.h"
#include "GameEngineSprite.h"

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineBase/GameEngineString.h>

#include <string>


ResourceManager ResourceManager::Inst;
ResourceManager::ResourceManager() 
{
}

ResourceManager::~ResourceManager() 
{
	for (const std::pair<std::string, GameEngineWindowTexture*>& Pair : AllTexture)
	{
		GameEngineWindowTexture* Texture = Pair.second;

		if (nullptr != Texture)
		{
			delete Texture;
			Texture = nullptr;
		}
	}

	for (const std::pair<std::string, GameEngineSprite*>& Pair : AllSprite)
	{
		GameEngineSprite* Sprite = Pair.second;

		if (nullptr != Sprite)
		{
			delete Sprite;
			Sprite = nullptr;
		}
	}
}


bool ResourceManager::IsLoadTexture(const std::string& _Name)
{
	return FindTexture(_Name) != nullptr;
}

GameEngineWindowTexture* ResourceManager::FindTexture(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineWindowTexture*>::iterator FindIter = AllTexture.find(UpperName);

	if (FindIter  == AllTexture.end())
	{
		return nullptr;
	}

	return FindIter->second;
}


GameEngineWindowTexture* ResourceManager::TextureLoad(const std::string& _Name, const std::string& _Path)
{
	std::string UpperString = GameEngineString::ToUpperReturn(_Name);

	GameEngineWindowTexture* NewTexture = new GameEngineWindowTexture();

	NewTexture->ResLoad(_Path);

	AllTexture.insert(std::make_pair(UpperString, NewTexture));

	return NewTexture;
}

GameEngineSprite* ResourceManager::FindSprite(const std::string& _Name)
{
	std::string UpperString = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineSprite*>::iterator FindIter = AllSprite.find(UpperString);

	if (FindIter == AllSprite.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineSprite* ResourceManager::CreateSpriteSheet(const std::string& _SpriteName,
	const std::string& _TexturePath,
	int _XCount,
	int _YCount)
{
	std::string UpperString = GameEngineString::ToUpperReturn(_SpriteName);

	if (nullptr != FindSprite(UpperString))
	{
		MsgBoxAssert("이미 로드된 스프라이트입니다." + _SpriteName);
		return nullptr;
	}

	GameEnginePath Path = _TexturePath;
	GameEngineWindowTexture* Texture = ResourceManager::FindTexture(Path.GetFileName());

	if (nullptr == Texture)
	{
		Texture = ResourceManager::TextureLoad(_TexturePath);
	}

	float4 Scale = Texture->GetScale();

	GameEngineSprite* NewSprite = new GameEngineSprite();
	NewSprite->CreateSpriteSheet(Texture, _XCount, _YCount);

	AllSprite.insert(std::make_pair(UpperString, NewSprite));

	return NewSprite;
}

GameEngineSprite* ResourceManager::CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SpriteName);

	if (nullptr != FindSprite(UpperName))
	{
		MsgBoxAssert("해당 스프라이트가 이미 존재합니다." + UpperName);
	}

	GameEngineSprite* NewSprite = new GameEngineSprite();

	NewSprite->CreateSpriteFolder(_Path);

	AllSprite.insert(std::make_pair(UpperName, NewSprite));

	return NewSprite;
}