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
	// ������ ����
	FlagRenderer = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == FlagRenderer)
	{
		MsgBoxAssert("������ �������� NUll�Դϴ�.");
		return;
	}


	// ���Ϸε�
	GlobalContents::SpriteFileLoad("StageDoorAndFlag.bmp", "Resources\\Unit\\Object", 5, 2);


	// �ִϸ��̼� ���� �� ����
	FlagRenderer->CreateAnimation("FlagFlutters", "StageDoorAndFlag.bmp", 5, 7, 0.1f, true);

	FlagRenderer->ChangeAnimation("FlagFlutters");

	Off();
}


void Flag::init(const float4& _StageOneDoorPos)
{
	if (nullptr == FlagRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}

	FlagRenderer->SetRenderPos(_StageOneDoorPos);
}