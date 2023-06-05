#include "VegetableValley11.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

// contents
#include "BackGround.h"
#include "GameEffect.h"
#include "Kirby.h"
#include "WaddleDee.h"
#include "BroomHatter.h"
#include "Kabu.h"
#include "PlayUIManager.h"


VegetableValley11::VegetableValley11() 
{
}

VegetableValley11::~VegetableValley11() 
{

}


void VegetableValley11::Start() 
{
	LevelBackGround = GameEngineLevel::CreateActor<BackGround>();
	LevelBackGround->init("VegetableValley1_1.bmp","VegetableValley1_1Pixel.bmp", "Resources\\Map");

	LevelEffect = GameEngineLevel::CreateActor<GameEffect>();
	LevelEffect->LoadBackGroundEffect("CloudAndWater12x3_8x8.bmp", "Resources\\Effect\\MapEffect", 12, 4);

	VegetableValley11BackGroundEffect(3.0f, 0.15f, true);


	LevelPlayer = GameEngineLevel::CreateActor<Kirby>();
	LevelPlayer->SetGroundTexture("VegetableValley1_1Pixel.bmp");

	// 몹1
	WaddleDee* WaddleDee1 = GameEngineLevel::CreateActor<WaddleDee>();
	WaddleDee1->init("VegetableValley1_1Pixel.bmp", float4{ 600, 384 });
	LevelEnemy.insert(std::make_pair("WaddleDee1", WaddleDee1));

	// 몹2
	BroomHatter* BroomHatter1 = GameEngineLevel::CreateActor<BroomHatter>();
	BroomHatter1->init("VegetableValley1_1Pixel.bmp", float4{ 500, 384 });
	LevelEnemy.insert(std::make_pair("BroomHatter1", BroomHatter1));

	// 몹3
	Kabu* Kabu1 = GameEngineLevel::CreateActor<Kabu>();
	Kabu1->init("VegetableValley1_1Pixel.bmp", float4{ 400, 384 });
	LevelEnemy.insert(std::make_pair("Kabu1", Kabu1));


	GameEngineLevel::CreateActor<PlayUIManager>();

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("VegetableValley1_1.bmp");
	BackGroundScale = Texture->GetScale();
}


void VegetableValley11::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	if (true == GameEngineInput::IsDown('N'))
	{
		GameEngineCore::ChangeLevel("VegetableValley12");
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		LevelBackGround->SwitchRender();
	}


	Enemy* WaddleDee1 = LevelEnemy.find("WaddleDee1")->second;
	if (false == WaddleDee1->IsUpdate())
	{
		WaddleDee1->RespawnTrigger("Walk");
	}

	Enemy* BroomHatter1 = LevelEnemy.find("BroomHatter1")->second;
	if (false == BroomHatter1->IsUpdate())
	{
		BroomHatter1->RespawnTrigger("Idle");
	}

	Enemy* Kabu1 = LevelEnemy.find("Kabu1")->second;
	if (false == Kabu1->IsUpdate())
	{
		Kabu1->RespawnTrigger("Idle");
	}
}


void VegetableValley11::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}
}


void VegetableValley11::LevelEnd(GameEngineLevel* _NextLevel) { }

void VegetableValley11::Render(float _Delta)
{
	UpdateTime += _Delta;

	std::string Text = "";
	Text += "프레임 : ";
	if (UpdateTime >= 1.0f)
	{
		UpdateTime = 0.0f;

		FPSText = 1.0f / _Delta;
	}
	Text += std::to_string(static_cast<int>(FPSText));
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
}