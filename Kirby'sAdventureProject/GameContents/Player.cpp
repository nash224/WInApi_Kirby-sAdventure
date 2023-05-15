#include "Player.h"
#include "ContentsEnum.h"
#include "Projectile.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourceManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include <Windows.h>



Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	// 비트맵 파일이 없으면 하나 만들어줘야한다.
	if (false == ResourceManager::GetInst().IsLoadTexture("MetaKnightsSoldiersStand.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.GetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		//GameEnginePath FolderPath = FilePath;
		FilePath.MoveChild("Resources\\KirbyTest");
		ResourceManager::GetInst().TextureLoad(FilePath.PlusFilePath("MetaKnightsSoldiersStand.bmp"));
		ResourceManager::GetInst().CreateSpriteSheet("MetaKnightsSoldiersStand.bmp" ,FilePath.PlusFilePath("MetaKnightsSoldiersStand.bmp"), 3, 2);
	}

	MainRenderer = CreateRenderer("MetaKnightsSoldiersStand.bmp", RenderOrder::Play);
	MainRenderer->CreateAnimation("Run", "MetaKnightsSoldiersStand.bmp", 0, 5, 0.1f, true);
	MainRenderer->CreateAnimation("Idle", "MetaKnightsSoldiersStand.bmp", 0, 0, 0.1f, false);
	MainRenderer->ChangeAnimation("Idle");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	SetPos(WinScale.GetHalf());
}

void Player::Update(float _Delta)
{
	SetSpeed(600.0f);

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		SetDir(float4::LEFT);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		SetDir(float4::RIGHT);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsPress('W'))
	{
		SetDir(float4::UP);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		SetDir(float4::DOWN);
		MovePos = GetDir() * GetSpeed() * _Delta;
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		Projectile* NewRazer = GetLevel()->CreateActor<Projectile>();
		NewRazer->Renderer->SetTexture("MetaKnightsSoldiersStand.bmp");
		NewRazer->SetDir(float4::RIGHT);
		NewRazer->SetPos(GetPos() + float4::XValue(60.0f));
		NewRazer->SetSpeed(300.0f);
	}

	if (MovePos.X != 0.0f || MovePos.Y != 0.0f)
	{
		MainRenderer->ChangeAnimation("Run");
	}
	else
	{
		MainRenderer->ChangeAnimation("Idle");
	}


	if (0 != GetAsyncKeyState('P'))
	{
		GameEngineCore::ChangeLevel("PauseLevel");
	}

	SetMovePos(MovePos);
	AddPos(MovePos);
	//if (GetPos().iX() >= GameEngineWindow::MainWindow.GetScale().GetHalf().iX())
	//{
	//	GetLevel()->GetMainCamera()->AddPos(float4::XValue(MovePos));
	//}

	//if (GetPos().iY() >= GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
	//{
	//	GetLevel()->GetMainCamera()->AddPos(float4::YValue(MovePos));
	//}
}

void Player::Render() 
{
}

void Player::Release() 
{

}
