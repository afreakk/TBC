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
, m_enemySpawner("Tutorial")
, m_time(0.0)
, m_pillarHider(m_environmentNode)
{
	Ogre::LogManager::getSingleton().logMessage("hnz: lvl1 Const");
	m_enemySpawner.init(m_mutantContainer.get(), m_playerContainer->getPlayer());
	m_playerCamera.init(m_playerContainer->getPlayer());
	m_dotSceneLoader.parseDotScene("Tutorial_level01.scene", "SceneOne", OgreCore::getSingletonPtr()->getSceneMgr(), m_environmentNode );
	m_environmentNode->rotate(Vector3::UNIT_Y, Radian(Degree(180)));
//	m_environmentNode->setPosition(Vector3(0, -10.0, 0));
	linkSubscribers();
}


LevelOne::~LevelOne()
{
	Ogre::LogManager::getSingleton().logMessage("hnz: lvl1 Dest");
	m_mutantContainer->destroyHandlers();
	m_playerContainer->destroyHandlers();
	destroyWorld();
	unLinkSubscribers();
	/* Destroy envNode + childEntity and nodes ? Seems to be destroyed somehow*/
	/*for (auto it : m_dotSceneLoader.dynamicObjects)
	{
	}
	auto nodes = m_environmentNode->getChildIterator();
	while (nodes.hasMoreElements())
	{
		auto it = nodes.getNext()
	}
	auto env = m_environmentNode->getAttachedObjectIterator();
	while (env.hasMoreElements())
	{
		auto it = env.getNext();
		OgreCore::getSingleton().getSceneMgr()->destroyMovableObject(it);
	}*/
	Ogre::LogManager::getSingleton().logMessage("hnz: lvl1 Dest / end");
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
	/*if (avgFps != OgreCore::getSingleton().getWindow()->getAverageFPS())
	{
		avgFps = OgreCore::getSingleton().getWindow()->getAverageFPS();
		cout << OgreCore::getSingleton().getWindow()->getAverageFPS() << endl;
	}*/
	m_menu.updateMenu();
	m_time += MainUpdate::getSingleton().getDeltaTime();
	m_pillarHider.update();
	m_particleRefContainer->update();
	m_playerContainer->update();
	m_mutantContainer->update();
	m_playerCamera.update();
	m_environment.update();
	m_tutorial.update();
	TooltipUpdates::update();
	if (m_tutorial.canSpawn())
	    m_enemySpawner.update();
	if (m_tutorial.plzChangeLevel())
		MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::LVL2);
	return false;
}