#pragma once
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <string>
#include <map>

// ���� :
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

	// ResourceManager�� �̱��� ��ü
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
	// �̱��� �������
	static ResourceManager Inst;
	// Texture�� �����ϴ� ����
	std::map<std::string, GameEngineWindowTexture*> AllTexture;

	ResourceManager();
	~ResourceManager();
};