#pragma once
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <string>
#include <map>

// ¼³¸í :
class GameEngineSprite;
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
	GameEngineSprite* FindSprite(const std::string& _Name);
	void LoadTextureFile(const std::string& _FileName, const std::string& _Path);
	void LoadSpriteFile(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount);


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

	GameEngineSprite* CreateSpriteSheet(const std::string& _TexturePath, int _XCount, int _YCount)
	{
		GameEnginePath Path = _TexturePath;
		return CreateSpriteSheet(Path.GetFileName(), _TexturePath, _XCount, _YCount);
	}

	GameEngineSprite* CreateSpriteSheet(const std::string& _SpriteName, const std::string& _TexturePath, int _XCount, int _YCount);


	GameEngineSprite* CreateSpriteFolder(const std::string& _Path)
	{
		GameEnginePath FolderPath = _Path;
		return CreateSpriteFolder(FolderPath.GetFileName(), _Path);
	}

	GameEngineSprite* CreateSpriteFolder(const std::string& _SpriteName, const std::string& _Path);

protected:

private:
	// ½Ì±ÛÅæ ¸â¹öº¯¼ö
	static ResourceManager Inst;
	// Texture¸¦ ÀúÀåÇÏ´Â º¯¼ö
	std::map<std::string, GameEngineWindowTexture*> AllTexture;
	std::map<std::string, GameEngineSprite*> AllSprite;

	ResourceManager();
	~ResourceManager();
};