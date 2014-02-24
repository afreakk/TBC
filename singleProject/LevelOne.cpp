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
	m_enemySpawner.init(m_mutantContainer.get(), m_playerContainer->getPlayer());
	m_playerCamera.init(m_playerContainer->getPlayer());

	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	/*Procedural::PlaneGenerator().setNumSegX(24).setNumSegY(24).setSizeX(24000*2).setSizeY(24000*2).setUTile(5.0).setVTile(5.0).realizeMesh("groundBox");
	auto cNode = sMgr->getRootSceneNode()->createChildSceneNode();
	auto ent = sMgr->createEntity("groundBox");
	cNode->attachObject(ent);*/
	m_dotSceneLoader.parseDotScene("environment03.scene", "SceneOne", sMgr, m_environmentNode );
	/*auto e = sMgr->createEntity("Environment02Waterfront", "Environment02Waterfront.mesh");
	e->setMaterialName("Examples/Ninja");
	auto n = sMgr->getRootSceneNode()->createChildSceneNode();
	n->attachObject(e);
	n->scale(Vector3(20500));*/

	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(&m_playerGUI, "PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->registerSubscriber(m_playerContainer.get(), "PlayerContainer");
	m_playerContainer->getHandler()->registerSubscriber(&m_playerCamera, "playerCamera");

}


LevelOne::~LevelOne()
{
	for (unsigned i = 0; i < m_dotSceneLoader.staticObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.staticObjects[i]);
	for (unsigned i = 0; i < m_dotSceneLoader.dynamicObjects.size(); i++)
		OgreCore::getSingleton().getSceneMgr()->destroyEntity(m_dotSceneLoader.dynamicObjects[i]);
	m_environmentNode->removeAndDestroyAllChildren();
	OgreCore::getSingleton().getSceneMgr()->destroySceneNode(m_environmentNode->getName());
	m_playerContainer->getPlayer()->removeSubscriber("playerCamera");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerGUI");
	PlayerGlobalStats::getSingletonPtr()->removeSubscriber("PlayerContainer");
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
/*	if (m_time > 0.1)
		MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::MENU);*/
	return false;
}