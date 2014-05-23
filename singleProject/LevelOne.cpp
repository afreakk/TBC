#include "stdafx.h"
#include "LevelOne.h"
#include "GameStarter.h"
LevelOne::LevelOne() 
: BaseGameLevel("Tutorial_level01.scene", "SceneOne",LevelID::LEVEL_ONE, "Tutorial")
, m_pillarHider(m_environmentNode)
{
	setAutoSpawnEnemies(false);
	Ogre::LogManager::getSingleton().logMessage("hnz: lvl1 Const");
	loadTutorialPosition();
}


void LevelOne::loadTutorialPosition()
{
	if (GameStarter::resume)
	{
		m_tutorial.setTooltipIdx(GameStarter::savedTutPoint);
		spawnEnemies();
	}

}
LevelOne::~LevelOne()
{
}
bool LevelOne::update()
{
	m_pillarHider.update();
	m_environment.update();
	if (tutorialUpdate())
		goLevel(MainLevelEnums::LVL2);
	return BaseGameLevel::update();
}
bool LevelOne::tutorialUpdate()
{
	m_tutorial.update();
	if (m_tutorial.canSpawn())
		spawnEnemies();
	return m_tutorial.plzChangeLevel();
}
