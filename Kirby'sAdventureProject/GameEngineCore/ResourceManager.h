#pragma once
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <string>
#include <map>

// ¼³¸í :
class ResourceManager
{
public:
	// delete Function
	ResourceManager(const ResourceManager& _Other) = delete;
	ResourceManager(ResourceManager&& _Other) noexcept = delete;
	ResourceManager& operator=(const ResourceManager& _Other) = delete;
	ResourceManager& operator=(ResourceManager&& _Other) noexcept = delete;


	bool IsLoadTexture(const std::string& _Name);
	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	// ResourceManagerÀÇ ½Ì±ÛÅæ °´Ã¼
	static ResourceManager& GetInst()
	{
		return Inst;
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);

protected:

private:
	// ½Ì±ÛÅæ ¸â¹öº¯¼ö
	static ResourceManager Inst;
	// Texture¸¦ ÀúÀåÇÏ´Â º¯¼ö
	std::map<std::string, GameEngineWindowTexture*> AllTexture;

	ResourceManager();
	~ResourceManager();
};