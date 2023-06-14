#pragma once


enum class UpdateOrder
{
	UI,
	BackGround,
	BackGroundEffect,
	Player,
	PlayerAbility,
	Monster,
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