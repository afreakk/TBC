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

	int enemyCount = 8;
	std::vector<PolarCoordinates> mutantStartingPositions;
	for (int i = 0; i < enemyCount; i++)
	{
		mutantStartingPositions.push_back(PolarCoordinates());
		mutantStartingPositions[i].r = floor(static_cast<float>(i)) * ((Math::PI/2.0) / floor(static_cast<float>(enemyCount)))+Math::PI/8.0;
		mutantStartingPositions[i].h = 0.2;
		mutantStartingPositions[i].d = 5.5;
	}
	m_enemySpawner.injectStartingPositions(mutantStartingPositions);

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