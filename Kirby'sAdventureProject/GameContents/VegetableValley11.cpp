#include "VegetableValley11.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>


// contents
#include "BackGround.h"
#include "GameEffect.h"
#include "PlayUI.h"
#include "FadeObject.h"
#include "Kirby.h"
#include "EnergeDrink.h"



VegetableValley11::VegetableValley11() 
{
}

VegetableValley11::~VegetableValley11() 
{

}


void VegetableValley11::Start() 
{
	BitMapFileName = "VegetableValley1_1Pixel.bmp";


	// 리스폰 세팅
	Kirby_RespawnPos = float4{ 200.0f , 384.0f };


	// 디버그 세팅
	NextLevelName = "VegetableValley12";
	KirbyShortCutPos = float4{ 2880.0f , 336.0f };



	ResourcesLoad();

	EnemySummon();
}


// 리소스 로드
void VegetableValley11::ResourcesLoad()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValley1_1.bmp", "VegetableValley1_1Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();
	SetLevelBackgroundScale(BackGroundScale);



	LevelEffect = GameEngineLevel::CreateActor<GameEffect>(UpdateOrder::BackGroundEffect);
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelEffect->LoadBackGroundEffect("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);



	EnergeDrink* EnergeDrinkPtr = GameEngineLevel::CreateActor<EnergeDrink>(UpdateOrder::Item);
	if (nullptr == EnergeDrinkPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	EnergeDrinkPtr->init(float4{ 2500.0f , 240.0f });
	EnergeDrinkPtr->SetGroundTexture(BitMapFileName);



	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}


	// 사운드 로드
	GlobalContents::SoundFileLoad("03_Plains_Level.mp3", "Resources\\SoundResources\\SoundTrack");
	LevelBgmFileName = "03_Plains_Level.mp3";
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */




void VegetableValley11::Update(float _Delta)
{
	LevelDebugShortcut(_Delta);


	PlayerMissPrevLevel();

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



// 비트맵 전환 스위치
void VegetableValley11::SwitchRenders()
{
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("이펙트를 불러오지 못했습니다.");
		return;
	}

	LevelEffect->SwitchEffect();


	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	LevelBackGround->SwitchRender();
}




// Miss 로직
void VegetableValley11::PlayerMissPrevLevel()
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


// 다음 레벨 체인지
void VegetableValley11::PlayerEnterNextLevel()
{
	if (true == IsPlayerEnter)
	{
		IsPlayerEnter = false;
		IsNextLeveling = true;

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

		GameEngineCore::ChangeLevel("VegetableValley12");
		return;
	}
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void VegetableValley11::Render(float _Delta)
{
	DebugRender(_Delta);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);


	SetPlayerPosAndCameraPos(Kirby_RespawnPos, float4::ZERO);



	if (false == IsBGM_On)
	{
		BGM_Player = GameEngineSound::SoundPlay("03_Plains_Level.mp3");
		BGMFileName = "03_Plains_Level.mp3";

		IsBGM_On = true;
	}


	GlobalContents::FadeIn(this);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel)
{
	IsPlayerEnter = false;
	NextLevelTriggerOn = false;
	IsFadeDone = false;

	if (true == IsBGM_On)
	{
		BGM_Player.Stop();

		IsBGM_On = false;
	}
}

