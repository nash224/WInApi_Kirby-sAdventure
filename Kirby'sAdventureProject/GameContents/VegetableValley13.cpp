#include "VegetableValley13.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>


#include "Kirby.h"
#include "PlayUI.h"
#include "BackGround.h"



VegetableValley13::VegetableValley13()
{
}

VegetableValley13::~VegetableValley13()
{
}

void VegetableValley13::Start()
{
	// 배경 생성
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("레벨 배경화면 생성에 실패했습니다.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValleyP.bmp", "VegetableValleyBossP.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("비트맵 파일을 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();

	BitMapFileName = "VegetableValleyBossP.bmp";




	// UI생성
	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}
}

void VegetableValley13::Update(float _Delta)
{
	float4 CameraHalfSize = GameEngineWindow::MainWindow.GetScale().Half();

	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("EndingLevel");
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}

}

void VegetableValley13::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(float4{ 370.0f, 200.0f });
}


void VegetableValley13::LevelEnd(GameEngineLevel* _NextLevel) { }
