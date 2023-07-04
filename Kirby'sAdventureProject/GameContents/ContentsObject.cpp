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
	// 렌더러 생성
	MainRenderer = CreateRenderer(RenderOrder::BackGroundEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("생성한 렌더러가 NUll입니다.");
		return;
	}



	// 파일로드
	GlobalContents::TextureFileLoad("EndingPlank.bmp", "Resources\\Unit\\Object");

	MainRenderer->SetTexture("EndingPlank.bmp");

}


void ContentsObject::init(const float4& _PlankPos)
{
	SetPos(_PlankPos);
}
