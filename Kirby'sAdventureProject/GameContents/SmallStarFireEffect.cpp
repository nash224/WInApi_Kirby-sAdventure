#include "SmallStarFireEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"
#include "ObejctDisapearingEffect.h"

SmallStarFireEffect::SmallStarFireEffect()
{
}

SmallStarFireEffect::~SmallStarFireEffect()
{
}


void SmallStarFireEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);

	GlobalContents::SpriteFileLoad("SpitStar_1x4_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 4, 1);

	MainRenderer->CreateAnimation("SmallStarFire", "SpitStar_1x4_16x16.bmp", 0, 3, FramesInter);
	MainRenderer->ChangeAnimation("SmallStarFire");

	MainRenderer->SetRenderScaleToTexture();

	Scale = ResourcesManager::GetInst().FindSprite("SpitStar_1x4_16x16.bmp")->GetSprite(0).RenderScale;
	SetCheckPoint(Scale);
}

void SmallStarFireEffect::init(const std::string& _FileName, const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });
	SetGroundTexture(_FileName);
}


void SmallStarFireEffect::Update(float _Delta)
{
	if (true == CheckCenterPoint())
	{
		ObejctDisapearingEffect* ObejctDisapearing = GetLevel()->CreateActor<ObejctDisapearingEffect>(UpdateOrder::PlayerAbility);
		ObejctDisapearing->init(GetPos());
		Death();
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	if (CameraPos().X > GetPos().X && GetPos().X > CameraPos().X + WinScale.X)
	{
		Death();
	}

	std::vector<GameEngineCollision*> Col;
	Col.reserve(2);
	if (true == EffectCollision->Collision(CollisionOrder::MonsterBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ObejctDisapearingEffect* ObejctDisapearing = GetLevel()->CreateActor<ObejctDisapearingEffect>(UpdateOrder::PlayerAbility);
		ObejctDisapearing->init(GetPos());
		Death();
	}



	AddPos(EffectDir * SMALLSTARFIREEFFECTSPEED * _Delta);
}

