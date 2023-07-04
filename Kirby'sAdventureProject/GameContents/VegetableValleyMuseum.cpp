#include "VegetableValleyMuseum.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>

// contents
#include "BackGround.h"
#include "PlayUI.h"
#include "Kirby.h"
#include "Pengi.h"
#include "FadeObject.h"



VegetableValleyMuseum::VegetableValleyMuseum()
{
}

VegetableValleyMuseum::~VegetableValleyMuseum()
{

}




void VegetableValleyMuseum::Start()
{
	Kirby_RespawnPos = KirbyRespawnLocation;

	BitMapFileName = "VegetableValleyMuseum_Pixel.bmp";

	LevelBgmFileName = "11_Museum.mp3";

	ResourcesLoad();
}


// 리소스 로드
void VegetableValleyMuseum::ResourcesLoad()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValleyMuseum.bmp", "VegetableValleyMuseum_Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	BackGroundScale = Texture->GetScale();


	Pengi* PengiPtr = GameEngineLevel::CreateActor<Pengi>(UpdateOrder::Monster);
	if (nullptr == PengiPtr)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

	PengiPtr->init(BitMapFileName, PengiState::Idle, float4{ 192.0f, 312.0f });


	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}



	// 사운드 로드
	GlobalContents::SoundFileLoad("11_Museum.mp3", "Resources\\SoundResources\\SoundTrack");
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void VegetableValleyMuseum::Update(float _Delta)
{
	if (false == FadeObject::IsFadeInDone)
	{
		return;
	}

	LevelDebugShortcut(_Delta);


	PlayerEnterNextLevel();


	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
	}
}


// 비트맵 전환 스위칭
void VegetableValleyMuseum::SwitchRenders()
{
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	LevelBackGround->SwitchRender();
}


// 다음 레벨 체인지
void VegetableValleyMuseum::PlayerEnterNextLevel()
{
	if (true == IsPlayerEnter)
	{
		IsPlayerEnter = false;

		GlobalContents::FadeOut(this);
	}

	if (true == IsFadeDone)
	{
		IsFadeDone = false;

		NextLevelTriggerOn = true;
	}

	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;

		IsChangeLevel = true;

		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValleyMuseum::Render(float _Delta)
{
	DebugRender(_Delta);
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValleyMuseum::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->On();
	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(Kirby_RespawnPos);


	if (false == IsBGM_On)
	{
		IsBGM_On = true;

		BGM_Player = GameEngineSound::SoundPlay("11_Museum.mp3");
		BGMFileName = "11_Museum.mp3";
	}

	GlobalContents::FadeIn(this);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValleyMuseum::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();

		IsBGM_On = false;
	}
}

