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
	Renderer = CreateRenderer(RenderOrder::Projectile);
	Renderer->SetRenderScale({ 60, 20 });
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

void Projectile::Render() 
{

}
