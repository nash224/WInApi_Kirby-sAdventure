#pragma once
#include <string>

// 설명 :
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

	// 오버로딩한 이유 
	// => 경로를 호출받으면 오버로딩한 함수로 호출받아 ResourceManager클래스에서 다시 실행시킬려고
	//    즉, 관리를 ResourceManager가 하기위해서
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

