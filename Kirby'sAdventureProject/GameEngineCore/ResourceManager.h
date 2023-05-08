#pragma once
#include <GameEngineBase/GameEnginePath.h>

#include <string>
#include <map>

// 설명 :
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
		// C2240 : 초기화 중 : const std::string에서 GameEnginePath로 변환할 수 없습니다.
		// std::string을 인자로 받는 생성자를 만들어 주지 않아서 오류
		GameEnginePath LoadPath = _Path;
		return TextureLoad(LoadPath.GetFileName(), _Path);
	}

	// 오버로딩한 이유 
	// => 경로를 호출받으면 오버로딩한 함수로 호출받아 ResourceManager클래스에서 다시 실행시킬려고
	//    즉, 관리를 ResourceManager가 하기위해서
	GameEngineWindowTexture* TextureLoad(const std::string& _Name, const std::string& _Path);


protected:

private:
	// Manager 메인 객체
	static ResourceManager Inst;
	std::map<std::string, GameEngineWindowTexture*> AllTexture;


	// constrcuter destructer
	ResourceManager();
	~ResourceManager();
};