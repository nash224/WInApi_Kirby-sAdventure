#include "Projectile.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>

Projectile::Projectile() 
{
}

Projectile::~Projectile() 
{
}


void Projectile::Start() 
{
	Renderer = CreateRenderer(RenderOrder::AbillityEffect);
	Renderer->SetRenderScale({ 16, 16 });
}

void Projectile::Update(float _Delta) 
{
	AddPos(Dir * _Delta * Speed);

	if (1.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}
}

