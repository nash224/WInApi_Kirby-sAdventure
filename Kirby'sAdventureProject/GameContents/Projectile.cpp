#include "Projectile.h"
#include <GameEngineCore/GameEngineRenderer.h>

Projectile::Projectile() 
{
}

Projectile::~Projectile() 
{
}


void Projectile::Start() 
{
	Renderer = CreateRenderer();
}

void Projectile::Update(float _Delta) 
{
	AddPos(Dir * _Delta * Speed);

	if (1.0f < GetLiveTime())
	{
		Renderer->Death();
	}
}

void Projectile::Render() 
{

}
