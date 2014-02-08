#include "stdafx.h"
#include "LevelOne.h"
#include "../OgreCore/OgreCore.h"

LevelOne::LevelOne() 
: ILevel(LevelID::LEVEL_ONE)
, m_globalVars(new GlobalVariables())
, m_playerStats(new PlayerGlobalStats())
, m_mutantGlobalStats(new MutantGlobalStats())
, m_particleRefContainer(new ParticleReferenceContainer())
, m_playerContainer(new PlayerContainer())
, m_mutantContainer(new MutantContainer())
, m_enemySpawner(m_mutantContainer.get(),m_playerContainer->getPlayer())
, m_playerCamera(m_playerContainer->getPlayer())
{
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	m_dotSceneLoader.parseDotScene("cityblock.scene", "SceneOne", sMgr);
//	auto ent = sMgr->createEntity("cityblockBox009.mesh");
//	sMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

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

Real avgFps = 0.0;
bool LevelOne::update()
{
	if (avgFps != OgreCore::getSingleton().getWindow()->getAverageFPS())
	{
		avgFps = OgreCore::getSingleton().getWindow()->getAverageFPS();
		cout << OgreCore::getSingleton().getWindow()->getAverageFPS() << endl;
	}
	m_particleRefContainer->update();
	m_playerContainer->update();
	m_mutantContainer->update();
	m_enemySpawner.update();
	m_playerCamera.update();
	return false;
}