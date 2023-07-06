#include "LargeStarFireEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "ObejctDisapearingEffect.h"



LargeStarFireEffect::LargeStarFireEffect()
{
}

LargeStarFireEffect::~LargeStarFireEffect()
{
}


void LargeStarFireEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("AbillityStartEffect_1x8_32x31.bmp", "Resources\\Effect\\KirbyBaseEffect", 8, 1);

	MainRenderer->CreateAnimation("LargeStarFire", "AbillityStartEffect_1x8_32x31.bmp", 0, 7, FramesInter);
	MainRenderer->ChangeAnimation("LargeStarFire");

	MainRenderer->SetRenderScaleToTexture();

	Scale = Sprite->GetSprite(0).RenderScale;
}

void LargeStarFireEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void LargeStarFireEffect::Update(float _Delta)
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetCameraPos();
	if (CameraPos.X > GetPos().X || GetPos().X > CameraPos.X + WinScale.X)
	{
		Death();
		EffectPointerRelease();
		return;
	}


	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody);

	int Damage = GameEngineRandom::MainRandom.RandomInt(7, 9);
	AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage);



	AddPos(EffectDir * EffectSpeed * _Delta);
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */



void LargeStarFireEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}