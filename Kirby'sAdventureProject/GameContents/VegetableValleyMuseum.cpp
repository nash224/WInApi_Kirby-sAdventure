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


// ���ҽ� �ε�
void VegetableValleyMuseum::ResourcesLoad()
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>(UpdateOrder::BackGround);
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValleyMuseum.bmp", "VegetableValleyMuseum_Pixel.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	BackGroundScale = Texture->GetScale();


	Pengi* PengiPtr = GameEngineLevel::CreateActor<Pengi>(UpdateOrder::Monster);
	if (nullptr == PengiPtr)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

	PengiPtr->init(BitMapFileName, PengiState::Idle, float4{ 192.0f, 312.0f });


	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI ������ �����߽��ϴ�.");
		return;
	}



	// ���� �ε�
	GlobalContents::SoundFileLoad("11_Museum.mp3", "Resources\\SoundResources\\SoundTrack");
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */



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


// ��Ʈ�� ��ȯ ����Ī
void VegetableValleyMuseum::SwitchRenders()
{
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	LevelBackGround->SwitchRender();
}


// ���� ���� ü����
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



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void VegetableValleyMuseum::Render(float _Delta)
{
	DebugRender(_Delta);
}




/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void VegetableValleyMuseum::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
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



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void VegetableValleyMuseum::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();

		IsBGM_On = false;
	}
}

