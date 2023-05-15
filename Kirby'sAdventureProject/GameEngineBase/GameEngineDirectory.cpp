#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include <string>

GameEngineDirectory::GameEngineDirectory() 
{
}

GameEngineDirectory::~GameEngineDirectory() 
{
}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
	:GameEnginePath(_Path)
{
	if (false == IsDirectory())
	{
		MsgBoxAssert("���丮 ��ΰ� �ƴմϴ�." + _Path);
	}
}