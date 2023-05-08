#include "PlayLevel.h"


#include "Player.h"
#include "BackGround.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{

}



void PlayLevel::Start() 
{
	BackGround* VegetableValley1 = GameEngineLevel::CreateActor<BackGround>();
	VegetableValley1->init("VegetableValley1.bmp");

	GameEngineLevel::CreateActor<Player>();
}

void PlayLevel::Update(float _Delta)
{

}

void PlayLevel::Render() 
{

}

void PlayLevel::Release() 
{

}