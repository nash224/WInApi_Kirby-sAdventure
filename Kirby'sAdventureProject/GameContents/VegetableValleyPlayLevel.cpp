#include "VegetableValleyPlayLevel.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>

#include "GameEffect.h"


bool VegetableValleyPlayLevel::NextLevelTriggerOn = false;
bool VegetableValleyPlayLevel::IsStageEnd = false;
float VegetableValleyPlayLevel::UpdateTime = 0.0f;
int VegetableValleyPlayLevel::VegetableValleyEntertheDoorNumber = -1;

VegetableValleyPlayLevel::VegetableValleyPlayLevel() 
{
}

VegetableValleyPlayLevel::~VegetableValleyPlayLevel() 
{
}



void VegetableValleyPlayLevel::CheckRespawnEnemy()
{
	std::map<std::string, Enemy*>::iterator StartIter = LevelEnemy.begin();
	std::map<std::string, Enemy*>::iterator EndtIter = LevelEnemy.end();

	for (; StartIter != EndtIter; ++StartIter)
	{
		Enemy* Enemy = StartIter->second;
		Enemy->RespawnTrigger();
	}
}



void VegetableValleyPlayLevel::CreateAndSetupBackgroundEffectRenderer(
	const std::string& _AnimationName,
	const std::string& _FileName,
	int _StartFrame, int _EndFrame,
	float4 _Pos, float _Ratio,
	float _Inter/* = 0.1f*/, bool _Loop/* = true*/)
{
	GameEngineRenderer* Render = LevelEffect->CreateRenderer(RenderOrder::BackGroundEffect);
	Render->CreateAnimation(_AnimationName, _FileName, _StartFrame, _EndFrame, _Inter, _Loop);
	Render->SetRenderPos(_Pos);
	Render->SetScaleRatio(_Ratio);
	Render->ChangeAnimation(_AnimationName);
}