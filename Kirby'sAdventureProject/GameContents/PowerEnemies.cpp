#include "PowerEnemies.h"

PowerEnemies::PowerEnemies() 
{
}

PowerEnemies::~PowerEnemies() 
{
}



float4 PowerEnemies::GetAbilityDir()
{
	float4 AbilityDir = float4::ZERO;

	if (ActorDir::Left == Dir)
	{
		AbilityDir = float4{ -1.0f, 0.0f };
	}
	else if (ActorDir::Right == Dir)
	{
		AbilityDir = float4{ 1.0f, 0.0f };
	}
	
	return AbilityDir;
}

