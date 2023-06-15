#pragma once


enum class UpdateOrder
{
	BackGround,
	BackGroundEffect,
	UI,
	Player,
	Monster,
	PlayerAbility,
	MonsterAbility,
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
	KirbyInhaleAbility,
	MonsterBody,
	MonsterAbility,
	Object,
	Max,
};