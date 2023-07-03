#include "VegetableValley12.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "Kirby.h"
#include "PlayUI.h"
#include "BackGround.h"


VegetableValley12::VegetableValley12() 
{
}

VegetableValley12::~VegetableValley12() 
{
}

void VegetableValley12::Start()
{
	// 배경 생성
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("레벨 배경화면 생성에 실패했습니다.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValley1_2.bmp", "VegetableValley1_2Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("비트맵 파일을 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();

	BitMapFileName = "VegetableValley1_2Pixel.bmp";



	EnemySummon();

	// UI생성
	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}



	// 사운드 로드
	GlobalContents::SoundFileLoad("06_Underground_Level.mp3", "Resources\\SoundResources\\SoundTrack");
	LevelBgmFileName = "06_Underground_Level.mp3";

	// 리스폰 세팅
	Kirby_RespawnPos = float4{ 83.0f, 384.0f };
}




void VegetableValley12::Update(float _Delta)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 불러오지 못했습니다.");
		return;
	}

	LevelDebugShortcut(_Delta);



	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValleyHub");
	}

	if (true == GameEngineInput::IsDown('6'))
	{
		GameEngineCamera* MainCameraPtr = GetMainCamera();
		if (nullptr == MainCameraPtr)
		{
			MsgBoxAssert("카메라가 NUll 입니다.");
			return;
		}

		float4 WinScale = GameEngineWindow::MainWindow.GetScale();

		LevelPlayer->SetPos(float4{ 3457.0f , 383.0f });
		MainCameraPtr->SetPos(float4{ BackGroundScale.X - WinScale.X , 0.0f });
	}


	if (true == IsPlayerMiss)
	{
		GlobalContents::FadeOut(this);

		IsPlayerMiss = false;
	}




	//PlayerMissPrevLevel();
	PlayerEnterNextLevel();


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


	CheckRespawnEnemy();


	CameraFocus(_Delta);
}





void VegetableValley12::PlayerMissPrevLevel()
{
	if (true == IsPlayerMiss)
	{
		IsPlayerMiss = false;
		IsPrevLeveling = true;

		GlobalContents::FadeOut(this);
	}

	if (true == IsFadeDone && true == IsPrevLeveling)
	{
		IsFadeDone = false;
		PrevLevelTriggerOn = true;
	}


	if (true == PrevLevelTriggerOn)
	{
		PrevLevelTriggerOn = false;
		IsPrevLeveling = false;
		IsChangeLevel = true;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}
}


void VegetableValley12::PlayerEnterNextLevel()
{
	if (true == IsPlayerEnter)
	{
		IsPlayerEnter = false;
		IsNextLeveling = true;
		IsStageEnd = true;

		GlobalContents::FadeOut(this);
	}

	if (true == IsFadeDone && true == IsNextLeveling)
	{
		IsFadeDone = false;
		NextLevelTriggerOn = true;
	}

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		IsNextLeveling = false;
		IsChangeLevel = true;

		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}
}



void VegetableValley12::Render(float _Delta)
{
	DebugRender(_Delta);
}




void VegetableValley12::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);

	SetPlayerPosAndCameraPos(Kirby_RespawnPos, float4::ZERO);



	// 사운드 재생
	if (false == IsBGM_On)
	{
		BGM_Player = GameEngineSound::SoundPlay("06_Underground_Level.mp3");
		IsBGM_On = true;
	}




	GlobalContents::FadeIn(this);
}

void VegetableValley12::LevelEnd(GameEngineLevel* _NextLevel) 
{
	NextLevelTriggerOn = false;
	IsPlayerEnter = false;

	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}

