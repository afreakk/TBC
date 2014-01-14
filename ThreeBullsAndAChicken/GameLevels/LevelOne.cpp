#include "stdafx.h"
#include "LevelOne.h"
LevelOne::LevelOne() : ILevel(LevelID::LEVEL_ONE)
{
}


LevelOne::~LevelOne()
{
}

bool LevelOne::update()
{
	m_player.update();
	return false;
}