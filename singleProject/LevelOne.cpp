#include "stdafx.h"
#include "LevelOne.h"
#include "OgreCore.h"
#include "MainLevelSetter.h"
#include "MainUpdate.h"
#include "ParticleReferenceContainer.h"
#include "PlayerContainer.h"
#include "PlayerGlobalStats.h"
#include "PlayerHandler.h"
#include "CoreCompositor.h"
#include "../procedural/ProceduralPlaneGenerator.h"
LevelOne::LevelOne() 
: ILevel(LevelID::LEVEL_ONE)
, m_particleRefContainer(new ParticleReferenceContainer())
, m_playerContainer(new PlayerContainer())
, m_mutantContainer(new MutantContainer())
, m_environmentNode(OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode())
, m_time(0.0)
{
	m_console = unique_ptr<GameConsole>(new GameConsole());
	m_enemySpawner.init(m_mutantContainer.get(), m_playerContainer->getPlayer());
	m_playerCamera.init(m_playerContainer->getPlayer());
	m_dotSceneLoader.parseDotScene("environment03.scene", "SceneOne", OgreCore::getSingletonPtr()->getSceneMgr(), m_environmentNode );

	linkSubscribers();
}


LevelOne::~LevelOne()
{
	m_mutantContainer->destroyHandlers();
	m_playerContainer->destroyHandlers();
	destroyWorld();
	unLinkSubscribers();
}
void LevelOne::linkSubscribers()
{
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(&m_playerGUI, "PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(m_playerContainer.get(), "PlayerContainer");
	m_playerContainer->getHandler()->registerSubscriber(&m_playerCamera, "playerCamera");
}
void LevelOne::unLinkSubscribers()
{
	m_playerContainer->getPlayer()->removeSubscriber("playerCamera");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerContainer");
}

void LevelOne::destroyWorld()
{
	for (unsigned i = 0; i < m_dotSceneLoader.staticObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.staticObjects[i]);
	for (unsigned i = 0; i < m_dotSceneLoader.dynamicObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.dynamicObjects[i]);
	m_environmentNode->removeAndDestroyAllChildren();
}
Real avgFps = 0.0;
bool LevelOne::update()
{
	if (avgFps != OgreCore::getSingleton().getWindow()->getAverageFPS())
	{
		avgFps = OgreCore::getSingleton().getWindow()->getAverageFPS();
		cout << OgreCore::getSingleton().getWindow()->getAverageFPS() << endl;
	}
	m_time += MainUpdate::getSingleton().getDeltaTime();
	m_particleRefContainer->update();
	m_playerContainer->update();
	m_mutantContainer->update();
	m_enemySpawner.update();
	m_playerCamera.update();
	m_environment.update();
	TooltipUpdates::update();
	//if (m_time > 3.1)
//		MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::MENU);
	return false;
}