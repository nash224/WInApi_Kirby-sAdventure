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
		MsgBoxAssert(_GroundTextureName + "는 픽셀충돌로 사용할 수 없습니다.");
	}
}