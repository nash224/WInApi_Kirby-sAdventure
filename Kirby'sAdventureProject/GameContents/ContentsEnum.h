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
	AbillityEffect,
	HitEffect,
	Play,
	PlayUI,
	DebugRender,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
	MonsterAbility,
	Object,
};