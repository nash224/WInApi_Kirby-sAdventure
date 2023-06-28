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
#include "Kirby.h"
#include "GameEffect.h"
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
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelBackGround->init("VegetableValley1_1.bmp","VegetableValley1_1Pixel.bmp", "Resources\\Map");

	BitMapFileName = "VegetableValley1_1Pixel.bmp";

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	BackGroundScale = Texture->GetScale();



	LevelEffect = GameEngineLevel::CreateActor<GameEffect>(UpdateOrder::BackGroundEffect);
	if (nullptr == LevelEffect)
	{
		MsgBoxAssert("������ ���Ͱ� Null �Դϴ�.");
		return;
	}

	LevelEffect->LoadBackGroundEffect("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);



	GameEngineWindowTexture* MapTexture = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	if (nullptr == MapTexture)
	{
		MsgBoxAssert("��Ʈ�� �ε忡 �����߽��ϴ�.");
		return;
	}

	float4 BackScale = MapTexture->GetScale();
	SetLevelBackgroundScale(BackScale);



	EnemySummon();




	LevelUIManager = GameEngineLevel::CreateActor<PlayUI>(UpdateOrder::UI);
	if (nullptr == LevelUIManager)
	{
		MsgBoxAssert("UI ������ �����߽��ϴ�.");
		return;
	}


	// ���� �ε�
	GlobalContents::SoundFileLoad("03_Plains_Level.mp3", "Resources\\SoundResources\\SoundTrack");
	LevelBgmFileName = "03_Plains_Level.mp3";

	// ������ ����
	Kirby_RespawnPos = float4{ 200.0f , 384.0f };
}


void VegetableValley11::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValley12");
	}



	if (true == PrevLevelTriggerOn)
	{
		PrevLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValleyHub");
		return;
	}


	if (true == NextLevelTriggerOn)
	{
		NextLevelTriggerOn = false;
		GameEngineCore::ChangeLevel("VegetableValley12");

		return;
	}



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
		Level_DebugRenderIsOn = !Level_DebugRenderIsOn;
	}

	CheckRespawnEnemy();
}



void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	LevelPlayer = Kirby::GetMainKirby();
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	LevelPlayer->SetGroundTexture(BitMapFileName);
	LevelPlayer->SetPos(Kirby_RespawnPos);


	if (false == IsBGM_On)
	{
		IsBGM_On = true;

		BGM_Player = GameEngineSound::SoundPlay("03_Plains_Level.mp3");
	}


	GlobalContents::FadeIn(this);
}


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) 
{
	if (true == IsBGM_On)
	{
		BGM_Player.Stop();

		IsBGM_On = false;
	}

}


void VegetableValley11::Render(float _Delta)
{
	if (false == Level_DebugRenderIsOn)
	{
		return;
	}


	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	GameEngineCamera* MainCameraPtr = GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
		return;
	}


	{
		UpdateTime += _Delta;


		std::string Text = "";
		Text += "������ : ";
		if (UpdateTime >= 1.0f)
		{
			UpdateTime = 0.0f;

			FPSText = 1.0f / _Delta;
		}
		Text += std::to_string(FPSText);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
	}


	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	float4 CameraPos = MainCameraPtr->GetPos();

	{
		std::string Text = "";
		Text += "���콺 X��ǥ : ";
		Text += std::to_string(MousePos.iX() + CameraPos.iX());
		TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));
	}


	{
		std::string Text = "";
		Text += "���콺 Y��ǥ : ";
		Text += std::to_string(MousePos.iY() + CameraPos.iY());
		TextOutA(dc, 2, 37, Text.c_str(), static_cast<int>(Text.size()));
	}
}


