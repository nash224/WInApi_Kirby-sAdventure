#include "VegetableValley12.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>


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
	BitMapFileName = "VegetableValley1_2Pixel.bmp";

	// 리스폰 세팅
	Kirby_RespawnPos = float4{ 83.0f, 384.0f };


	// 디버그 세팅
	NextLevelName = "VegetableValleyHub";
	KirbyShortCutPos = float4{ 3457.0f , 383.0f };


	ResourcesLoad();
}


// 리소스 로드
void VegetableValley12::ResourcesLoad()
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



	EnemySummon();

}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValley12::Update(float _Delta)
{
	LevelDebugShortcut(_Delta);

	PlayerEnterNextLevel();

	if (true == PrevLevelTriggerOn)
	{
		PrevLevelTriggerOn = false;
	}

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}


	CheckRespawnEnemy();

	CameraFocus(_Delta);
}



// 비트맵 디버그 렌더 스위치
void VegetableValley12::SwitchRenders()
{
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	LevelBackGround->SwitchRender();
}




// Miss 패턴
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


// 다음 레벨 Change
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



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValley12::Render(float _Delta)
{
	DebugRender(_Delta);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


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
		BGMFileName = "06_Underground_Level.mp3";
		IsBGM_On = true;
	}


	GlobalContents::FadeIn(this);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


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

