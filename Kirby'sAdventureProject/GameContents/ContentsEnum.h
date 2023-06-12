#pragma once


enum class UpdateOrder
{
	Player,
	Monster,
};


enum class RenderOrder
{
	BackGround,
	BackGroundEffect,
	Play,
	AbillityEffect,
	HitEffect,
	PlayUI,
	DebugRender,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	PlayerAbility,
	MonsterBody,
	MonsterAbility,
	Object,
};