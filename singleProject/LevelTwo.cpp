
#include "stdafx.h"
#include "LevelTwo.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "ParticleReferenceContainer.h"
#include "PlayerContainer.h"
#include "PlayerGlobalStats.h"
#include "PlayerHandler.h"

LevelTwo::LevelTwo() 
: ILevel(LevelID::LEVEL_TWO)
, m_particleRefContainer(new ParticleReferenceContainer())
, m_playerContainer(new PlayerContainer())
, m_mutantContainer(new MutantContainer())
, m_environmentNode(OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode())
, m_enemySpawner("LvlOne")
, m_time(0.0)
{
	Ogre::LogManager::getSingleton().logMessage("hnz: lvl2 Const");
	m_enemySpawner.init(m_mutantContainer.get(), m_playerContainer->getPlayer());
	m_playerCamera.init(m_playerContainer->getPlayer());
	m_dotSceneLoader.parseDotScene("Mountainpath.scene", "SceneTwo", OgreCore::getSingletonPtr()->getSceneMgr(), m_environmentNode );
//	m_environmentNode->rotate(Vector3::UNIT_Y, Radian(Degree(180)));
//	m_environmentNode->setPosition(Vector3(0, -10.0, 0));
//	m_environmentNode->scale(Vector3(0.325));
	m_playerGUI.init();
    //bec00z0ff loadingbar need exclusive 0000000000000Layer
	linkSubscribers();
}


LevelTwo::~LevelTwo()
{
	Ogre::LogManager::getSingleton().logMessage("hnz: lvl2 Dest");
	m_mutantContainer->destroyHandlers();
	m_playerContainer->destroyHandlers();
	destroyWorld();
	unLinkSubscribers();
}
void LevelTwo::linkSubscribers()
{
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(&m_playerGUI, "PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(m_playerContainer.get(), "PlayerContainer");
	m_playerContainer->getHandler()->registerSubscriber(&m_playerCamera, "playerCamera");
}
void LevelTwo::unLinkSubscribers()
{
	m_playerContainer->getPlayer()->removeSubscriber("playerCamera");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerContainer");
}

void LevelTwo::destroyWorld()
{
	for (unsigned i = 0; i < m_dotSceneLoader.staticObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.staticObjects[i]);
	for (unsigned i = 0; i < m_dotSceneLoader.dynamicObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.dynamicObjects[i]);
	m_environmentNode->removeAndDestroyAllChildren();
}
bool LevelTwo::update()
{
	m_time += MainUpdate::getSingleton().getDeltaTime();
	m_particleRefContainer->update();
	m_playerContainer->update();
	m_mutantContainer->update();
	m_playerCamera.update();
	m_environment.update();
    m_enemySpawner.update();
	m_menu.updateMenu();
	return false;
}