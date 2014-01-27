#include "stdafx.h"
#include "LevelManager.h"
#include "ILevel.h"
LevelManager::LevelManager(ILevel* initialLevel) : m_currentLevel(initialLevel)
{
}


LevelManager::~LevelManager()
{
}
void LevelManager::update()
{
	m_currentLevel->update();
}
const LevelID LevelManager::getCurrentLevelID()
{
	return m_currentLevel->getID();
}
void LevelManager::changeLevel(ILevel* nextLevel)
{
	m_currentLevel.reset();
	m_currentLevel = unique_ptr<ILevel>{ nextLevel };
}