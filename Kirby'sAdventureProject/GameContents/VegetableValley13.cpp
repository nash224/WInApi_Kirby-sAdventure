#include "VegetableValley13.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>


#include "BackGround.h"
#include "BossUI.h"
#include "FadeObject.h"
#include "Kirby.h"
#include "WhispyWood.h"
#include "EndingPlank.h"



bool VegetableValley13::IsEndingCreditOn = false;
VegetableValley13::VegetableValley13()
{
}

VegetableValley13::~VegetableValley13()
{
}




void VegetableValley13::Start()
{
	BitMapFileName = "VegetableValleyBossP.bmp";

	// 리스폰 세팅
	Kirby_RespawnPos = float4{ 370.0f, 200.0f };

	// 디버깅 
	NextLevelName = "VegetableValleyHub";


	ResourcesLoad();
}


// 리소스 로드
void VegetableValley13::ResourcesLoad()
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


	// UI생성
	LevelUIManager = GameEngineLevel::CreateActor<BossUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI 생성에 실패했습니다.");
		return;
	}


	GlobalContents::SoundFileLoad("07_Boss.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("30_Level_Clear.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("32_Crane_Fever_(faster).mp3", "Resources\\SoundResources\\SoundTrack");

}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void VegetableValley13::Update(float _Delta)
{
	if (true == IsEndingCreditOn)
	{
		EndingCredit(_Delta);
	}


	PlayerMissPrevLevel();

	if (true == PrevLevelTriggerOn)
	{
		PrevLevelTriggerOn = false;
	}


	LevelDebugShortcut(_Delta);

	CameraFocus(_Delta);
}


// 비트맵 디버깅 스위치
void VegetableValley13::SwitchRenders()
{
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	LevelBackGround->SwitchRender();
}




// 엔딩 크래딧
void VegetableValley13::EndingCredit(float _Delta)
{
	if (false == Ending_IsFadeOut)
	{
		GlobalContents::WhiteFadeOut(this);
		FadeObject::SetTimeRaito(2.0f);

		Ending_IsFadeOut = true;
	}


	if (true == IsFadeDone && false == FadeObject::IsFadeOutScreenRelease)
	{
		IsFadeDone = false;

		// UI에 ByeBye 초상화 호출
		if (nullptr == LevelUIManager)
		{
			MsgBoxAssert("UI 를 불러오지 못했습니다.");
			return;
		}

		BossUI* BossUIPtr = dynamic_cast<BossUI*>(LevelUIManager);
		if (nullptr == BossUIPtr)
		{
			MsgBoxAssert("다운 캐스팅을 실패했습니다.");
			return;
		}

		BossUIPtr->IsCall_ByeByePortrait = true;


		FadeObject::IsFadeOutScreenRelease = true;
		GlobalContents::WhiteFadeIn(this);

		if (nullptr == LevelPlayer)
		{
			MsgBoxAssert("플레이어를 불러오지 못했습니다.");
			return;
		}

		LevelPlayer->Off();
		LevelBoss->Off();


		// 판자 생성
		EndingPlank* PlankPtr = CreateActor<EndingPlank>(UpdateOrder::UI);
		if (nullptr == PlankPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		PlankPtr->init(PlankPos);


		if (true == IsBGM_On)
		{
			BGM_Player.Stop();
			IsBGM_On = false;
		}

		BGM_Player = GameEngineSound::SoundPlay("32_Crane_Fever_(faster).mp3");
		BGMFileName = "32_Crane_Fever_.mp3";
	}
}




// Miss 레벨 패턴
void VegetableValley13::PlayerMissPrevLevel()
{
	if (true == IsPlayerMiss)
	{
		IsPlayerMiss = false;

		GlobalContents::FadeOut(this);
	}

	if (true == IsFadeDone)
	{
		IsFadeDone = false;
		PrevLevelTriggerOn = true;
	}


	if (true == PrevLevelTriggerOn)
	{
		PrevLevelTriggerOn = false;
		IsChangeLevel = true;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}
}




/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void VegetableValley13::Render(float _Delta)
{
	DebugRender(_Delta);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValley13::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(Kirby_RespawnPos);


	GlobalContents::FadeIn(this);


	// 보스생성
	LevelBoss = GameEngineLevel::CreateActor<WhispyWood>(UpdateOrder::Monster);
	if (nullptr == LevelBoss)
	{
		MsgBoxAssert("생성한 액터가 Null입니다.");
		return;
	}

}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void VegetableValley13::LevelEnd(GameEngineLevel* _NextLevel)
{
	IsFadeDone = false; 

	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}
