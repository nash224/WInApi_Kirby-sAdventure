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
			MsgBoxAssert(_ChildPath + "�� ���� ������ ������ ���� �ʽ��ϴ�.");
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
		MsgBoxAssert(CheckPath.string() + "�� �������� �ʴ� ����Դϴ�.");
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
		MsgBoxAssert(CheckPath.string() + "�� �������� �ʴ� ����Դϴ�.");
	}

	return CheckPath.string();
}

std::string GameEnginePath::GetFileName()
{
	return Path.filename().string();
}
