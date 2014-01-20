#include "stdafx.h"
#include "LevelOne.h"
#include "../OgreCore/OgreCore.h"
#include "../Other/DotSceneLoader.h"
#include "../Player/PlayerStats.h"
#include "Overlay/OgreOverlay.h"
#include "Overlay/OgreOverlaySystem.h"
using namespace Ogre;
LevelOne::LevelOne() : ILevel(LevelID::LEVEL_ONE)
{
	new PlayerStats();
	m_playerCamera = new PlayerCamera(&m_player);

	//temporary for reference of space
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	auto dotSceneLoader = new DotSceneLoader();
	dotSceneLoader->parseDotScene("Cityblock.scene", "CityDir", sMgr);

	m_gameRules.init(&m_enemyHandler, &m_player);
	std::vector<NormalPosition> mutantStartingPositions;
	int enemyCount = 8;
	for (int i = 0; i < enemyCount; i++)
	{
		mutantStartingPositions.push_back(NormalPosition());
		mutantStartingPositions[i].r = floor(static_cast<float>(i)) * ((Math::PI/2.0) / floor(static_cast<float>(enemyCount)))+Math::PI/4.0;
		mutantStartingPositions[i].h = 0.0;
		mutantStartingPositions[i].d = -4.5;
	}
	m_enemyHandler.init(&m_player, mutantStartingPositions);
	m_playerGUI.init();
	m_player.addSubsriber(m_playerCamera, "playerCamera");
}


LevelOne::~LevelOne()
{
	m_player.removeSubscriber("playerCamera");
	delete PlayerStats::getSingletonPtr();
}

bool LevelOne::update()
{
	m_player.update();
	m_enemyHandler.update();
	m_playerCamera->update();
	return false;
}