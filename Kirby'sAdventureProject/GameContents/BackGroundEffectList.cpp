#include "VegetableValley11.h"
#include "GameEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>



//CreateAnimation("HillProjectionEffect", "CloudAndWater12x3_8x8.bmp", 0, 2, 0.15f, true);
//CreateAnimation("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, 0.15f, true);
//CreateAnimation("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, 0.15f, true);


// VegetableValley11 배경애니메이션 리스트
void VegetableValley11::VegetableValley11BackGroundEffect(float _Ratio, float _Inter, bool _Loop)
{
	CreateAndSetupBackgroundEffectRenderer("HillProjectionEffect", "CloudAndWater12x3_8x8.bmp",
	0, 2, { 40,40 }, _Ratio, _Inter, _Loop);


	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 228,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 252,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 276,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 300,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 372,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 396,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 660,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 684,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 708,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 732,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 756,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 780,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 804,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 828,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1332,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1356,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1380,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1404,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1428,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1452,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1476,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1500,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1524,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1548,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1860,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1884,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1908,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1932,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1956,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 1980,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2004,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2028,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2052,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2076,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2100,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2124,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2148,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2173,228 }, _Ratio, _Inter, _Loop);

	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2485,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2508,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2532,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2556,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2580,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2604,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2628,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2652,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2676,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2700,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2724,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2748,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2772,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2796,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2820,228 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("ForestProjectionEffect", "CloudAndWater12x3_8x8.bmp", 12, 14, { 2845,228 }, _Ratio, _Inter, _Loop);


	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 276,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 300,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 372,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 396,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 660,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 684,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 708,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 732,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 756,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 780,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 804,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 828,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1332,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1356,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1380,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1404,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1428,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1452,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1476,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1500,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1524,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1548,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1860,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1884,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1908,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1932,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1956,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 1980,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2004,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2028,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2052,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2076,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2100,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2124,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2148,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2173,252 }, _Ratio, _Inter, _Loop);

	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2533,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2556,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2580,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2604,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2628,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2652,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2676,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2700,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2724,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2748,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2772,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2796,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2820,252 }, _Ratio, _Inter, _Loop);
	CreateAndSetupBackgroundEffectRenderer("WaterProjectionEffect", "CloudAndWater12x3_8x8.bmp", 24, 26, { 2845,252 }, _Ratio, _Inter, _Loop);



}

void VegetableValley11::CreateAndSetupBackgroundEffectRenderer(
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