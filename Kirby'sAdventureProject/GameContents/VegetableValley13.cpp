#include "VegetableValley13.h"
#include "ContentsEnum.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "Kirby.h"
#include "GlobalContents.h"
#include "BossUI.h"
#include "WhispyWood.h"
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

	LevelBackGround->ExtraMapSet("VegetableValleyP_Black.bmp", "Resources\\Map");
	LevelBackGround->ExtraMapSet("VegetableValleyP_Orange_Black.bmp", "Resources\\Map");

	// 보스 배경 패턴을 위한 스테이지 설정
	LevelBackGround->BossStage = 1;

	// 설정
	BackGroundScale = Texture->GetScale();

	BitMapFileName = "VegetableValleyBossP.bmp";






	// UI생성
	LevelUIManager = GameEngineLevel::CreateActor<BossUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}


	GlobalContents::SoundFileLoad("07_Boss.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("30_Level_Clear.mp3", "Resources\\SoundResources\\SoundTrack");
	LevelBgmFileName = "07_Boss.mp3";


	// 리스폰 세팅
	Kirby_RespawnPos = float4{ 370.0f, 200.0f };
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
		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}




	if (true == PrevLevelTriggerOn)
	{
		PrevLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}




	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}



	if (true == PrevLevelTriggerOn)
	{
		PrevLevelTriggerOn = false;
	}


	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}



	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}

}



void VegetableValley13::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return;
	}


	{
		UpdateTime += _Delta;


		std::string Text = "";
		Text += "프레임 : ";
		if (UpdateTime >= 1.0f)
		{
			UpdateTime = 0.0f;

			FPSText = 1.0f / _Delta;
		}
		Text += std::to_string(FPSText);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
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
	LevelPlayer->SetPos(Kirby_RespawnPos);



	// 보스생성
	LevelBoss = GameEngineLevel::CreateActor<WhispyWood>(UpdateOrder::Monster);
	if (nullptr == LevelBoss)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

}


void VegetableValley13::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}
