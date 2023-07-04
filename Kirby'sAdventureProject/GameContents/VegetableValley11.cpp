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


	// ������ ����
	Kirby_RespawnPos = float4{ 200.0f , 384.0f };


	// ����� ����
	NextLevelName = "VegetableValley12";
	KirbyShortCutPos = float4{ 2880.0f , 336.0f };



	ResourcesLoad();

	EnemySummon();
}


// ���ҽ� �ε�
void VegetableValley11::ResourcesLoad()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValley1_1.bmp", "VegetableValley1_1Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	BackGroundScale = Texture->GetScale();
	SetLevelBackgroundScale(BackGroundScale);



	LevelEffect = GameEngineLevel::CreateActor<GameEffect>(UpdateOrder::BackGroundEffect);
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelEffect->LoadBackGroundEffect("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);



	EnergeDrink* EnergeDrinkPtr = GameEngineLevel::CreateActor<EnergeDrink>(UpdateOrder::Item);
	if (nullptr == EnergeDrinkPtr)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	EnergeDrinkPtr->init(float4{ 2500.0f , 240.0f });
	EnergeDrinkPtr->SetGroundTexture(BitMapFileName);



	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI ������ �����߽��ϴ�.");
		return;
	}


	// ���� �ε�
	GlobalContents::SoundFileLoad("03_Plains_Level.mp3", "Resources\\SoundResources\\SoundTrack");
	LevelBgmFileName = "03_Plains_Level.mp3";
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */




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



// ��Ʈ�� ��ȯ ����ġ
void VegetableValley11::SwitchRenders()
{
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("����Ʈ�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	LevelEffect->SwitchEffect();


	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	LevelBackGround->SwitchRender();
}




// Miss ����
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


// ���� ���� ü����
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




/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */



void VegetableValley11::Render(float _Delta)
{
	DebugRender(_Delta);
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */



void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
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



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


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

