#pragma once


enum class UpdateOrder
{
	BackGround,
	BackGroundEffect,
	Player,
	Monster,
	Item,
	UI,
	Ability,
	Other,
};


enum class RenderOrder
{
	BackGround,
	BackGroundEffect,
	Play,
	AbillityEffect,
	HitEffect,
	DebugRender,
	PlayUI,
	Fade,
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	PlayerAbility,
	KirbyInhaleAbility,
	MonsterBody,
	BossBody,
	MonsterAbility,
	Object,
	Max,
};