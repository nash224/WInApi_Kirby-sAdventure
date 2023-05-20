#include "ContentUtils.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourceManager.h>

ContentUtils::ContentUtils() 
{
}

ContentUtils::~ContentUtils() 
{
}


void ContentUtils::CameraFocus()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() - WinScale.GetHalf());




	//if (true == GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D'))
//{
//	if (LevelPlayer->GetPos().iX() > GameEngineWindow::MainWindow.GetScale().GetHalf().iX() &&
//		LevelPlayer->GetPos().iX() <
//		LevelBackGround->GetScale().iX() - GameEngineWindow::MainWindow.GetScale().GetHalf().iX())
//	{
//		GetMainCamera()->AddPos(float4::XValue(LevelPlayer->GetMovePos()));
//	}
//}
//if (true == GameEngineInput::IsPress('W') || GameEngineInput::IsPress('S'))
//{
//	if (LevelPlayer->GetPos().iY() > GameEngineWindow::MainWindow.GetScale().GetHalf().iY() &&
//		LevelPlayer->GetPos().iY() <
//		LevelBackGround->GetScale().iY() - GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
//	{
//		GetMainCamera()->AddPos(float4::YValue(LevelPlayer->GetMovePos()));
//	}
//}


}

void ContentUtils::Gravity()
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityPower;

	AddPos(GravityVector);
}

void ContentUtils::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourceManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert(" 픽셀충돌 맵을 찾을 수 없습니다. "+ _GroundTextureName);
	}
}