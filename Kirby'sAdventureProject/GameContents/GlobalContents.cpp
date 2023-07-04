#include "GlobalContents.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "FadeObject.h"


GlobalContents::GlobalContents() 
{
}

GlobalContents::~GlobalContents() 
{
}


// 텍스쳐 로드
GameEngineWindowTexture* GlobalContents::TextureFileLoad(const std::string& _FileName, const std::string& _Path)
{
	static GameEngineWindowTexture* ReturnValue;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
		if (nullptr == Texture)
		{
			// 터짐횟수 0
			MsgBoxAssert("이게 왜 터지죠?");
			return ReturnValue;
		}

		return Texture;
	}

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();

	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));

	if (nullptr == Texture)
	{
		// 터짐횟수 0
		MsgBoxAssert("이게 왜 터지죠?");
		return ReturnValue;
	}

	return Texture;
}


// 스프라이드 프로시져
GameEngineSprite* GlobalContents::SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	static GameEngineSprite* ReturnValue;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEngineSprite* Sprite = ResourcesManager::GetInst().FindSprite(_FileName);
		if (nullptr == Sprite)
		{
			// 터짐횟수 0
			MsgBoxAssert("이게 왜 터지죠?");
			return ReturnValue;
		}

		return Sprite;
	}

	GameEnginePath FilePath;
	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);

	GameEngineSprite* Sprite = ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_FileName), _XCount, _YCount);

	if (nullptr == Sprite)
	{
		// 터짐횟수 0
		MsgBoxAssert("이게 왜 터지죠?");
		return ReturnValue;
	}

	return Sprite;
}


// 사운드 로드 프로시저
void GlobalContents::SoundFileLoad(const std::string& _FileName, const std::string& _Path)
{
	if (nullptr != GameEngineSound::FindSound(_FileName))
	{
		return;
	}

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();

	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);

	GameEngineSound::SoundLoad(FilePath.PlusFilePath(_FileName));
}



// FadeOut 프로시저
void GlobalContents::FadeOut(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("레벨이 Null 입니다.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelFade->RequestFadeOut();
}


// FadeIn 프로시저
void GlobalContents::FadeIn(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("레벨이 Null 입니다.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelFade->RequestFadeIn();
}



// WhiteFadeOut 프로시저
void GlobalContents::WhiteFadeOut(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("레벨이 Null 입니다.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelFade->Request_WhiteFadeOut();
}


// WhiteFadeIn 프로시저
void GlobalContents::WhiteFadeIn(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("레벨이 Null 입니다.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelFade->Request_WhiteFadeIn();
}
