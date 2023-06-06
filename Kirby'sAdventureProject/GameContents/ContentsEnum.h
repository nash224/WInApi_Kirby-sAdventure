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
};

enum class CollisionOrder
{
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
	Object,
};