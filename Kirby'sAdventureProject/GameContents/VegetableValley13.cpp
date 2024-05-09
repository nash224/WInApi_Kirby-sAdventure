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

	// ������ ����
	Kirby_RespawnPos = float4{ 370.0f, 200.0f };

	// ����� 
	NextLevelName = "VegetableValleyHub";


	ResourcesLoad();
}


// ���ҽ� �ε�
void VegetableValley13::ResourcesLoad()
{
	// ��� ����
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("���� ���ȭ�� ������ �����߽��ϴ�.");
		return;
	}

	GameEngineWindowTexture* Texture = LevelBackGround->init("VegetableValleyP.bmp", "VegetableValleyBossP.bmp", "Resources\\Map");
	if (nullptr == Texture)
	{
		MsgBoxAssert("��Ʈ�� ������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	LevelBackGround->ExtraMapSet("VegetableValleyP_Black.bmp", "Resources\\Map");
	LevelBackGround->ExtraMapSet("VegetableValleyP_Orange_Black.bmp", "Resources\\Map");

	// ���� ��� ������ ���� �������� ����
	LevelBackGround->BossStage = 1;

	// ����
	BackGroundScale = Texture->GetScale();


	// UI����
	LevelUIManager = GameEngineLevel::CreateActor<BossUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI ������ �����߽��ϴ�.");
		return;
	}


	GlobalContents::SoundFileLoad("07_Boss.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("30_Level_Clear.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("32_Crane_Fever_(faster).mp3", "Resources\\SoundResources\\SoundTrack");

}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */



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


// ��Ʈ�� ����� ����ġ
void VegetableValley13::SwitchRenders()
{
	if (nullptr == LevelBackGround)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	LevelBackGround->SwitchRender();
}




// ���� ũ����
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

		// UI�� ByeBye �ʻ�ȭ ȣ��
		if (nullptr == LevelUIManager)
		{
			MsgBoxAssert("UI �� �ҷ����� ���߽��ϴ�.");
			return;
		}

		BossUI* BossUIPtr = dynamic_cast<BossUI*>(LevelUIManager);
		if (nullptr == BossUIPtr)
		{
			MsgBoxAssert("�ٿ� ĳ������ �����߽��ϴ�.");
			return;
		}

		BossUIPtr->IsCall_ByeByePortrait = true;


		FadeObject::IsFadeOutScreenRelease = true;
		GlobalContents::WhiteFadeIn(this);

		if (nullptr == LevelPlayer)
		{
			MsgBoxAssert("�÷��̾ �ҷ����� ���߽��ϴ�.");
			return;
		}

		LevelPlayer->Off();
		LevelBoss->Off();


		// ���� ����
		EndingPlank* PlankPtr = CreateActor<EndingPlank>(UpdateOrder::UI);
		if (nullptr == PlankPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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




// Miss ���� ����
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




/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */



void VegetableValley13::Render(float _Delta)
{
	DebugRender(_Delta);
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void VegetableValley13::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(Kirby_RespawnPos);


	GlobalContents::FadeIn(this);


	// ��������
	LevelBoss = GameEngineLevel::CreateActor<WhispyWood>(UpdateOrder::Monster);
	if (nullptr == LevelBoss)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}

}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void VegetableValley13::LevelEnd(GameEngineLevel* _NextLevel)
{
	IsFadeDone = false; 

	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}
