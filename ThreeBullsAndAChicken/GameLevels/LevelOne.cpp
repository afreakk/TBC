#include "stdafx.h"
#include "LevelOne.h"
#include "../OgreCore/OgreCore.h"
using namespace Ogre;
LevelOne::LevelOne() : ILevel(LevelID::LEVEL_ONE)
{
	m_currentCamera = new PlayerCamera(&m_player);

	//temporary for reference of space
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	Entity* ogreHeadEntity =  sMgr->createEntity("ogrehead", "ogrehead.mesh");
	auto node = sMgr->getRootSceneNode()->createChildSceneNode("ogreHeadNode");
	node->attachObject(ogreHeadEntity);
	node->setScale(Ogre::Vector3(0.2,0.2,0.2));
	node->setPosition(Ogre::Vector3(0.0, 0.0, 0.0));

	m_gameRules.init(&m_enemyHandler, &m_player);
}


LevelOne::~LevelOne()
{
}

bool LevelOne::update()
{
	m_player.update();
	m_enemyHandler.update();
	m_currentCamera->update();
	return false;
}