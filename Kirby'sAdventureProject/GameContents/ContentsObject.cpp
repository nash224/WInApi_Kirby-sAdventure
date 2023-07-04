#include "ContentsObject.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineCore/GameEngineRenderer.h>


#include "VegetableValleyPlayLevel.h"


ContentsObject::ContentsObject()
{
}

ContentsObject::~ContentsObject()
{
}


void ContentsObject::Start()
{
	// ������ ����
	MainRenderer = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("������ �������� NUll�Դϴ�.");
		return;
	}



	// ���Ϸε�
	GlobalContents::TextureFileLoad("EndingPlank.bmp", "Resources\\Unit\\Object");

	MainRenderer->SetTexture("EndingPlank.bmp");

}


void ContentsObject::init(const float4& _PlankPos)
{
	SetPos(_PlankPos);
}
