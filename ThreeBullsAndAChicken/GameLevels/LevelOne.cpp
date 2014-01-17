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
	m_currentCamera = new PlayerCamera(&m_player);

	//temporary for reference of space
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	auto dotSceneLoader = new DotSceneLoader();
	dotSceneLoader->parseDotScene("citytest.scene", "CityDir", sMgr);

	m_gameRules.init(&m_enemyHandler, &m_player);
	std::vector<NormalPosition> mutantStartingPositions;
	int enemyCount = 8;
	for (int i = 0; i < enemyCount; i++)
	{
		mutantStartingPositions.push_back(NormalPosition());
		mutantStartingPositions[i].r = floor(static_cast<float>(i)) * ((Math::PI/2.0) / floor(static_cast<float>(enemyCount)));
		mutantStartingPositions[i].h = 0.0;
		mutantStartingPositions[i].d = -5.0;
	}
	m_enemyHandler.init(&m_player, mutantStartingPositions);
	m_playerGUI.init();
}


LevelOne::~LevelOne()
{
	delete PlayerStats::getSingletonPtr();
}

bool LevelOne::update()
{
	m_player.update();
	m_enemyHandler.update();
	m_currentCamera->update();
	return false;
}