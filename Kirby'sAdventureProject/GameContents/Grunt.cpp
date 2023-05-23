#include "Grunt.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Kirby.h"


std::list<Grunt*> Grunt::AllGrunt;

Grunt::Grunt() 
{
	AllGrunt.push_back(this);
}

Grunt::~Grunt() 
{
}


void Grunt::AllMonsterDeath()
{
	for (Grunt* Grunt : AllGrunt)
	{
		Grunt->Death();
	}

	AllGrunt.clear();
}


void Grunt::Start()
{
	ResourcesManager::GetInst().SpriteFileLoad("MetaKnightsSoldiersStand.bmp", "Resources\\Unit\\Grunt", 3, 2);
	GameEngineRenderer* TestGrunt = CreateRenderer(RenderOrder::HitEffect);
	TestGrunt->CreateAnimation("MetalKnight", "MetaKnightsSoldiersStand.bmp", 0, 5, 0.15f, true);
	TestGrunt->ChangeAnimation("MetalKnight");

	GameEngineCollision* BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollision->SetCollisionScale({ 64 , 64 });
	BodyCollision->SetCollisionType(CollisionType::CirCle);

}

void Grunt::Update(float _Delta)
{
	float4 Dir = Kirby::GetMainKirby()->GetPos() - GetPos();

	Dir.Normalize();

	AddPos(Dir * _Delta * 100.0f);
}