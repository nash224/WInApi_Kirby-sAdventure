#pragma once
#include <GameEngineBase/GameEnginePath.h>

#include <string>
#include <map>

// ���� :
class GameEngineWindowTexture;
class ResourceManager
{
public:

	// delete Function
	ResourceManager(const ResourceManager& _Other) = delete;
	ResourceManager(ResourceManager&& _Other) noexcept = delete;
	ResourceManager& operator=(const ResourceManager& _Other) = delete;
	ResourceManager& operator=(ResourceManager&& _Other) noexcept = delete;

	static ResourceManager& GetInst()
	{
		return Inst;
	}

	bool IsLoadTexture(const std::string& _Name);
	GameEngineWindowTexture* FindTexture(const std::string& _Name);

	GameEngineWindowTexture* TextureLoad(const std::string& _Path)
	{
		// C2240 : �ʱ�ȭ �� : const std::string���� GameEnginePath�� ��ȯ�� �� �����ϴ�.
		// std::string�� ���ڷ� �޴� �����ڸ� ����� ���� �ʾƼ� ����
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	// �����ε��� ���� 
	// => ��θ� ȣ������� �����ε��� �Լ��� ȣ��޾� ResourceManagerŬ�������� �ٽ� �����ų����
	//    ��, ������ ResourceManager�� �ϱ����ؼ�
	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);


protected:

private:
	// Manager ���� ��ü
	static ResourceManager Inst;
	std::map<std::string, GameEngineWindowTexture*> AllTexture;


	// constrcuter destructer
	ResourceManager();
	~ResourceManager();
};