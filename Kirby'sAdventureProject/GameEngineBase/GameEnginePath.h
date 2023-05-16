#pragma once
#include <string>
#include <filesystem>

// Ό³Έν :
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	// delete Function
	//GameEnginePath(const GameEnginePath& _Other) = delete;
	//GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	//GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	//GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	void SetCurrentPath();
	void MoveParent();
	void MoveParentToExistsChild(const std::string& _ChildPath); 
	static std::string GetParentString(const std::string& _ChildPath);
	void MoveChild(const std::string& _ChildPath);
	std::string PlusFilePath(const std::string& _ChildPath);
	bool IsDirectory();

	std::string GetFileName();

	std::string GetStringPath()
	{
		return Path.string();
	}

protected:
	std::filesystem::path Path;

private:

};

