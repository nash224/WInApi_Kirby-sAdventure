#include "EndingLevel.h"

#include "Kirby.h"
#include "BackGround.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>


EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{

}


void EndingLevel::Start()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	BackRenderer = LevelBackGround->SpriteInit("MrShine&MrBright.bmp","MrShine&MrBrightPixel.bmp", "Resources\\Map", 3, 2);

	BackRenderer->CreateAnimation("NightToDay", "MrShine&MrBright.bmp", 0, 5, 0.05f, false);
	BackRenderer->CreateAnimation("DayToNight", "MrShine&MrBright.bmp", 5, 0, 0.05f, false);
	BackRenderer->ChangeAnimation("DayToNight");

	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	LevelPlayer->SetGroundTexture("MrShine&MrBrightPixel.bmp");
}

void EndingLevel::Update(float _Delta)
{

}


void EndingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}
}


void EndingLevel::LevelEnd(GameEngineLevel* _NextLevel) { }