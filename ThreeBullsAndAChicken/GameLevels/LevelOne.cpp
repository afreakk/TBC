#include "stdafx.h"
#include "LevelOne.h"
#include "../OgreCore/OgreCore.h"

LevelOne::LevelOne() : ILevel(LevelID::LEVEL_ONE), m_playerCamera(&m_player), m_playerStats(new PlayerStats())
{

	//temporary for reference of space
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	m_dotSceneLoader.parseDotScene("Cityblock.scene", "CityDir", sMgr);

	m_gameRules.init(&m_enemyHandler, &m_player);
	std::vector<PolarCoordinates> mutantStartingPositions;
	int enemyCount = 8;
	for (int i = 0; i < enemyCount; i++)
	{
		mutantStartingPositions.push_back(PolarCoordinates());
		mutantStartingPositions[i].r = floor(static_cast<float>(i)) * ((Math::PI/2.0) / floor(static_cast<float>(enemyCount)))+Math::PI/4.0;
		mutantStartingPositions[i].h = 0.2;
		mutantStartingPositions[i].d = 5.5;
	}
	m_enemyHandler.init(&m_player, mutantStartingPositions);
	PlayerStats::getSingletonPtr()->registerEnergySubscriber(&m_playerGUI, "PlayerGUI");
	m_player.addSubsriber(&m_playerCamera, "playerCamera");
}


LevelOne::~LevelOne()
{
	m_player.removeSubscriber("playerCamera");
	PlayerStats::getSingletonPtr()->removeEnergySubscriber("PlayerGUI");
}

bool LevelOne::update()
{
	m_player.update();
	m_enemyHandler.update();
	m_playerCamera.update();
	m_gameRules.update();
	return false;
}