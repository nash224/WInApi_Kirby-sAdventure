#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath() 
{
}

GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{

}

GameEnginePath::~GameEnginePath() 
{
}


void GameEnginePath::GetCurrentPath()
{
	Path = std::filesystem::current_path();
}

void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveParentToExistsChild(const std::string& _ChildPath)
{
	while (true)
	{
		std::filesystem::path CheckPath = Path;

		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else
		{
			break;
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert(_ChildPath + "의 하위 폴더를 가지고 있지 않습니다.");
			return;
		}
	}
}

void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert(CheckPath.string() + "은 존재하지 않는 경로입니다.");
		return;
	}

	Path = CheckPath;
}

std::string GameEnginePath::PlusFilePath(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;
	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert(CheckPath.string() + "은 존재하지 않는 경로입니다.");
	}

	return CheckPath.string();
}

std::string GameEnginePath::GetFileName()
{
	return Path.filename().string();
}
