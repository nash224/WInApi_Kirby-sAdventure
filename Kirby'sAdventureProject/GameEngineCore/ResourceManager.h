#pragma once
#include <string>

// ���� :
class GameEngineTexture;
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

	void TextureLoad(const std::string& _Path)
	{
		// _Path fileName

		// TextureLoad();
	}

	// �����ε��� ���� 
	// => ��θ� ȣ������� �����ε��� �Լ��� ȣ��޾� ResourceManagerŬ�������� �ٽ� �����ų����
	//    ��, ������ ResourceManager�� �ϱ����ؼ�
	void TextureLoad(const std::string& _Name, const std::string& _Path)
	{

	}

	GameEngineTexture* FindTexture(const std::string& _Name);
	bool IsLoadTexture(const std::string& _Name);

protected:

private:
	static ResourceManager Inst;



	// constrcuter destructer
	ResourceManager();
	~ResourceManager();
};

