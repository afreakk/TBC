#include "stdafx.h"
#include "LevelOne.h"
#include "OgreCore.h"

LevelOne::LevelOne() 
: ILevel(LevelID::LEVEL_ONE)
, m_globalVars(new GlobalVariables())
, m_playerStats(new PlayerGlobalStats())
, m_mutantGlobalStats(new MutantGlobalStats())
, m_particleRefContainer(new ParticleReferenceContainer())
, m_playerContainer(new PlayerContainer())
, m_mutantContainer(new MutantContainer())
{
	m_enemySpawner.init(m_mutantContainer.get(), m_playerContainer->getPlayer());
	m_playerCamera.init(m_playerContainer->getPlayer());

	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	m_dotSceneLoader.parseDotScene("citycylinder.scene", "SceneOne", sMgr);

	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(&m_playerGUI, "PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(m_playerContainer.get(), "PlayerContainer");
	m_playerContainer->getHandler()->registerSubscriber(&m_playerCamera, "playerCamera");
}


LevelOne::~LevelOne()
{
	m_playerContainer->getPlayer()->removeSubscriber("playerCamera");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerContainer");
}

Real avgFps = 0.0;
bool LevelOne::update()
{
	/*if (avgFps != OgreCore::getSingleton().getWindow()->getAverageFPS())
	{
		avgFps = OgreCore::getSingleton().getWindow()->getAverageFPS();
		cout << OgreCore::getSingleton().getWindow()->getAverageFPS() << endl;
	}*/
	m_particleRefContainer->update();
	m_playerContainer->update();
	m_mutantContainer->update();
	m_enemySpawner.update();
	m_playerCamera.update();
	return false;
}