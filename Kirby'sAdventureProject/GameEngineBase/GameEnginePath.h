#pragma once
#include <string>
#include <filesystem>

// Ό³Έν :
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	~GameEnginePath();

	// delete Function
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	void GetCurrentPath();
	void MoveParent();
	void MoveParentToExistsChild(const std::string& _ChildPath);
	void MoveChild(const std::string& _ChildPath);

	std::string GetStringPath()
	{
		return Path.string();
	}

protected:

private:
	std::filesystem::path Path;

};

