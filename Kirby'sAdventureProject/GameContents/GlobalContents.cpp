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


// �ؽ��� �ε�
GameEngineWindowTexture* GlobalContents::TextureFileLoad(const std::string& _FileName, const std::string& _Path)
{
	static GameEngineWindowTexture* ReturnValue;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
		if (nullptr == Texture)
		{
			// ����Ƚ�� 0
			MsgBoxAssert("�̰� �� ������?");
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
		// ����Ƚ�� 0
		MsgBoxAssert("�̰� �� ������?");
		return ReturnValue;
	}

	return Texture;
}


// �������̵� ���ν���
GameEngineSprite* GlobalContents::SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	static GameEngineSprite* ReturnValue;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEngineSprite* Sprite = ResourcesManager::GetInst().FindSprite(_FileName);
		if (nullptr == Sprite)
		{
			// ����Ƚ�� 0
			MsgBoxAssert("�̰� �� ������?");
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
		// ����Ƚ�� 0
		MsgBoxAssert("�̰� �� ������?");
		return ReturnValue;
	}

	return Sprite;
}


// ���� �ε� ���ν���
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



// FadeOut ���ν���
void GlobalContents::FadeOut(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("������ Null �Դϴ�.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelFade->RequestFadeOut();
}


// FadeIn ���ν���
void GlobalContents::FadeIn(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("������ Null �Դϴ�.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelFade->RequestFadeIn();
}



// WhiteFadeOut ���ν���
void GlobalContents::WhiteFadeOut(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("������ Null �Դϴ�.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelFade->Request_WhiteFadeOut();
}


// WhiteFadeIn ���ν���
void GlobalContents::WhiteFadeIn(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("������ Null �Դϴ�.");
		return;
	}

	FadeObject* LevelFade = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelFade->Request_WhiteFadeIn();
}
