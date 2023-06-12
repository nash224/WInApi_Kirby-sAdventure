#include "GlobalContents.h"
#include <GameEngineCore/ResourcesManager.h>

GlobalContents::GlobalContents() 
{
}

GlobalContents::~GlobalContents() 
{
}


void GlobalContents::TextureFileLoad(const std::string& _FileName, const std::string& _Path)
{
	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		return;
	}

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();

	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);
	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
}

void GlobalContents::SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		return;
	}

	GameEnginePath FilePath;
	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);

	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_FileName), _XCount, _YCount);
}
