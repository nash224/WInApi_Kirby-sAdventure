#include "VegetableValley13.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>


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

	BitMapFileName = "VegetableValleyBossP.bmp";


	// ��������
	LevelBoss = GameEngineLevel::CreateActor<WhispyWood>(UpdateOrder::Monster);
	if (nullptr == LevelBoss)
	{
		MsgBoxAssert("������ ���Ͱ� Null�Դϴ�.");
		return;
	}





	// UI����
	LevelUIManager = GameEngineLevel::CreateActor<BossUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI ������ �����߽��ϴ�.");
		return;
	}


	GlobalContents::SoundFileLoad("07_Boss.mp3", "Resources\\SoundResources\\SoundTrack");
	GlobalContents::SoundFileLoad("30_Level_Clear.mp3", "Resources\\SoundResources\\SoundTrack");

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


	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
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

void VegetableValley13::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(float4{ 370.0f, 200.0f });

}


void VegetableValley13::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();
		IsBGM_On = false;
	}
}
