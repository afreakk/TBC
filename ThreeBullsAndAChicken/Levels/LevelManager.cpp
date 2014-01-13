#include "stdafx.h"
#include "LevelManager.h"
#include "ILevel.h"
LevelManager::LevelManager(ILevel* initialLevel) : m_currentLevel(initialLevel)
{
}


LevelManager::~LevelManager()
{
	delete m_currentLevel;
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
	delete m_currentLevel;
	m_currentLevel = nullptr;
	m_currentLevel = nextLevel;
}