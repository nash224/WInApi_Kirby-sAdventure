#include "BillboardsObject.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>





BillboardsObject::BillboardsObject()
{
}

BillboardsObject::~BillboardsObject()
{
}


void BillboardsObject::Start()
{
	// ������ ����
	StageOne_BillBoard = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == StageOne_BillBoard)
	{
		MsgBoxAssert("������ �������� NUll�Դϴ�.");
		return;
	}

	StageBoss_BillBoard = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == StageBoss_BillBoard)
	{
		MsgBoxAssert("������ �������� NUll�Դϴ�.");
		return;
	}

	// ���Ϸε�
	GlobalContents::SpriteFileLoad("StageDoorAndFlag.bmp", "Resources\\Unit\\Object", 5, 2);
	GlobalContents::SpriteFileLoad("EnterDoor.bmp", "Resources\\Unit\\Object", 5, 4);


	// �ִϸ��̼� ���� �� ����
	StageOne_BillBoard->CreateAnimation("StageOne_UnClear_Billboard", "EnterDoor.bmp", 10, 11, 0.16f, true);
	StageOne_BillBoard->CreateAnimation("StageOne_Clear_Billboard", "EnterDoor.bmp", 10, 10, 0.04f, false);

	StageOne_BillBoard->ChangeAnimation("StageOne_UnClear_Billboard");



	StageBoss_BillBoard->CreateAnimation("StageBoss_UnClear_Billboard", "EnterDoor.bmp", 0, 3, 0.08f, true);
	StageBoss_BillBoard->FindAnimation("StageBoss_UnClear_Billboard")->Inters = { 3.0f , 0.09f, 0.08f, 0.07f };

	StageBoss_BillBoard->ChangeAnimation("StageBoss_UnClear_Billboard");


}


void BillboardsObject::StageOneBillBoardinit(const float4& _StageOneBillBoardPos)
{
	if (nullptr == StageOne_BillBoard)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}

	StageOne_BillBoard->SetRenderPos(_StageOneBillBoardPos);
}



void BillboardsObject::StageBossBillBoardinit(const float4& _StageBossBillBoardPos)
{
	if (nullptr == StageBoss_BillBoard)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}

	StageBoss_BillBoard->SetRenderPos(_StageBossBillBoardPos);
}




void BillboardsObject::Update(float _Delta)
{
	if (nullptr == StageOne_BillBoard)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}

	if (nullptr == StageBoss_BillBoard)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}

}