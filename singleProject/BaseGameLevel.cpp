#include "stdafx.h"
#include "BaseGameLevel.h"
#include "PlayerGlobalStats.h"
#include "PlayerHandler.h"
#include "MutantGlobalStats.h"
#include "ParticleReferenceContainer.h"
#include "PlayerContainer.h"
#include "MainUpdate.h"
#include "GameStarter.h"
#include "MainLevelSetter.h"
#include "AudioHelpers.h"
BaseGameLevel::BaseGameLevel(const std::string& sceneFileName, const std::string& groupName, LevelID level, const std::string& enemyspawnerConfig) 
: ILevel(level)
, m_environmentNode(OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode())
, m_particleRefContainer(new ParticleReferenceContainer())
, m_playerContainer(new PlayerContainer())
, m_mutantContainer(new MutantContainer())
, m_enemySpawner(enemyspawnerConfig)
, m_time(0.0)
, m_spawnEnemies(true)
{
	m_enemySpawner.init(m_mutantContainer.get(), m_playerContainer->getPlayer());
	m_playerCamera.init(m_playerContainer->getPlayer());
	m_dotSceneLoader.parseDotScene(sceneFileName, groupName, OgreCore::getSingletonPtr()->getSceneMgr(), m_environmentNode );
	m_playerGUI.init();
	linkSubscribers();
}
BaseGameLevel::~BaseGameLevel()
{
	destroyWorld();
	m_mutantContainer->destroyHandlers();
	m_playerContainer->destroyHandlers();
	destroyWorld();
	unLinkSubscribers();
}
void BaseGameLevel::destroyWorld()
{
	for (unsigned i = 0; i < m_dotSceneLoader.staticObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.staticObjects[i]);
	for (unsigned i = 0; i < m_dotSceneLoader.dynamicObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.dynamicObjects[i]);
	m_environmentNode->removeAndDestroyAllChildren();
}
void BaseGameLevel::linkSubscribers()
{
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(&m_playerGUI, "PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(m_playerContainer.get(), "PlayerContainer");
	m_playerContainer->getHandler()->registerSubscriber(&m_playerCamera, "playerCamera");
}
void BaseGameLevel::unLinkSubscribers()
{
	m_playerContainer->getPlayer()->removeSubscriber("playerCamera");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerContainer");
}
#include "GlobalVariables.h"
bool BaseGameLevel::update()
{
	GlobalVariables::getSingleton().updateLerp();
	m_time += MainUpdate::getSingleton().getDeltaTime();
	m_particleRefContainer->update();
	m_playerContainer->update();
	m_mutantContainer->update();
	m_playerCamera.update();
	m_menu.updateMenu();
	m_deathScreen.updateDeathMenu();
	SoundUpdater::updateSound();
	TooltipUpdates::update();
	if (m_spawnEnemies)
        m_enemySpawner.instantiateNewEnemies();
	return false;
}
void BaseGameLevel::setAutoSpawnEnemies(bool on)
{
	m_spawnEnemies = on;
}
void BaseGameLevel::spawnEnemies()
{
	m_enemySpawner.instantiateNewEnemies();
}
void BaseGameLevel::goLevel(MainLevelEnums newLevel)
{
    GameStarter::resume = false;
    MainLevelSetter::getSingleton().changeLevel(newLevel);
}
