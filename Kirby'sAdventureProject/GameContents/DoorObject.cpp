#include "DoorObject.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>





DoorObject::DoorObject() 
{
}

DoorObject::~DoorObject() 
{
}


void DoorObject::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("������ �������� NUll�Դϴ�.");
		return;
	}


	GlobalContents::SpriteFileLoad("StageDoorAndFlag.bmp", "Resources\\Unit\\Object", 5, 2);
	GlobalContents::SpriteFileLoad("EnterDoor.bmp", "Resources\\Unit\\Object", 5, 4);

	
	MainRenderer->CreateAnimation("PlayDoor_Idle", "EnterDoor.bmp", 16, 19, 0.08f, true);
	MainRenderer->CreateAnimation("PlayDoor_StarDoor", "EnterDoor.bmp", 15, 15, 0.04f, false);
	MainRenderer->CreateAnimation("PlayDoor_Open", "StageDoorAndFlag.bmp", 0, 3, 0.04f, false);
	MainRenderer->CreateAnimation("PlayDoor_Close", "StageDoorAndFlag.bmp", 3, 0, 0.04f, false);
	MainRenderer->CreateAnimation("PlayDoor_Clear", "StageDoorAndFlag.bmp", 4, 4, 0.04f, false);

	MainRenderer->ChangeAnimation("PlayDoor_Idle");



}


void DoorObject::init(const float4& _DoorPos)
{
	SetPos(_DoorPos);
}




void DoorObject::Update(float _Delta)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� Null �Դϴ�.");
		return;
	}


	if (true == IsDoorOpen)
	{
		MainRenderer->ChangeAnimation("PlayDoor_Open");

		IsDoorOpen = false;
	}

	if (true == IsDoorIdle)
	{
		MainRenderer->ChangeAnimation("PlayDoor_Idle");

		IsDoorIdle = false;
	}

	if (true == IsDoorClose)
	{
		MainRenderer->ChangeAnimation("PlayDoor_Close");

		IsDoorClose = false;
	}

	if (true == IsDoorClear)
	{
		MainRenderer->ChangeAnimation("PlayDoor_Clear");

		IsDoorClear = false;
	}

	if (true == IsDoorStar)
	{
		MainRenderer->ChangeAnimation("PlayDoor_StarDoor");

		IsDoorStar = false;
	}
}