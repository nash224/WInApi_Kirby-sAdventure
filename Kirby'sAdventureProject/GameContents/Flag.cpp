#include "Flag.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>


Flag::Flag()
{
}

Flag::~Flag()
{
}


void Flag::Start()
{
	// 렌더러 생성
	FlagRenderer = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == FlagRenderer)
	{
		MsgBoxAssert("생성한 렌더러가 NUll입니다.");
		return;
	}


	// 파일로드
	GlobalContents::SpriteFileLoad("StageDoorAndFlag.bmp", "Resources\\Unit\\Object", 5, 2);


	// 애니메이션 생성 및 적용
	FlagRenderer->CreateAnimation("FlagFlutters", "StageDoorAndFlag.bmp", 5, 7, 0.1f, true);

	FlagRenderer->ChangeAnimation("FlagFlutters");

	Off();
}


void Flag::init(const float4& _StageOneDoorPos)
{
	if (nullptr == FlagRenderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	FlagRenderer->SetRenderPos(_StageOneDoorPos);
}