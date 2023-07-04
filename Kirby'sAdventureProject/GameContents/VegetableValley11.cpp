#include "VegetableValley11.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

// contents
#include "BackGround.h"
#include "FadeObject.h"
#include "Kirby.h"
#include "GameEffect.h"
#include "EnergeDrink.h"
#include "PlayUI.h"



VegetableValley11::VegetableValley11() 
{
}

VegetableValley11::~VegetableValley11() 
{

}


void VegetableValley11::Start() 
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelBackGround->init("VegetableValley1_1.bmp","VegetableValley1_1Pixel.bmp", "Resources\\Map");

	BitMapFileName = "VegetableValley1_1Pixel.bmp";

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();



	LevelEffect = GameEngineLevel::CreateActor<GameEffect>(UpdateOrder::BackGroundEffect);
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelEffect->LoadBackGroundEffect("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);



	GameEngineWindowTexture* MapTexture = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	if (nullptr == MapTexture)
	{
		MsgBoxAssert("비트맵 로드에 실패했습니다.");
		return;
	}

	float4 BackScale = MapTexture->GetScale();
	SetLevelBackgroundScale(BackScale);



	EnemySummon();


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

	// 리스폰 세팅
	Kirby_RespawnPos = float4{ 200.0f , 384.0f };
}


void VegetableValley11::Update(float _Delta)
{
	LevelDebugShortcut(_Delta);


	if (true == GameEngineInput::IsDown('N'))
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValley12");
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

		LevelPlayer->SetPos(float4{ 2880.0f , 336.0f });
		MainCameraPtr->SetPos(float4{ BackGroundScale.X - WinScale.X , 0.0f });
	}


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


	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('Y'))
	{
		Level_DebugRenderValue = !Level_DebugRenderValue;
	}

	CheckRespawnEnemy();


	CameraFocus(_Delta);
}




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







void VegetableValley11::Render(float _Delta)
{
	DebugRender(_Delta);
}


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

