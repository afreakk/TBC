#include "stdafx.h"
#include "LevelOne.h"
#include "../OgreCore/OgreCore.h"

LevelOne::LevelOne() 
: ILevel(LevelID::LEVEL_ONE)
, m_globalVars(new GlobalVariables())
, m_playerStats(new PlayerGlobalStats())
, m_mutantGlobalStats(new MutantGlobalStats())
, m_playerContainer(new PlayerContainer())
, m_mutantContainer(new MutantContainer())
, m_enemySpawner(m_mutantContainer.get(),m_playerContainer->getPlayer())
, m_playerCamera(m_playerContainer->getPlayer())
{
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	m_dotSceneLoader.parseDotScene("Cityblock.scene", "CityDir", sMgr);

	///

	m_enemySpawner.injectStartingPositions();

	///

	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(&m_playerGUI, "PlayerGUI");
	m_playerContainer->getHandler()->registerSubscriber(&m_playerCamera, "playerCamera");
}


LevelOne::~LevelOne()
{
	m_playerContainer->getPlayer()->removeSubscriber("playerCamera");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerGUI");
}

bool LevelOne::update()
{
	m_playerContainer->update();
	m_mutantContainer->update();
	m_enemySpawner.update();
	m_playerCamera.update();
	return false;
}