#include "stdafx.h"
#include "LevelTwo.h"

LevelTwo::LevelTwo() 
: BaseGameLevel("Mountainpath.scene", "SceneTwo", LevelID::LEVEL_TWO,"LvlOne")
{
}

LevelTwo::~LevelTwo()
{
}

bool LevelTwo::update()
{
	m_environment.update();
	return BaseGameLevel::update();
}