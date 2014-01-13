#include "stdafx.h"
#include "PlayerModelHandler.h"

#include "OgreCore.h"
using namespace Ogre;
PlayerModelHandler::PlayerModelHandler()
{
}
void PlayerModelHandler::init(Ogre::Vector3 pos)
{
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	Entity* playerEntity =  sMgr->createEntity("Player", "ninja.mesh");
	m_playerNode = sMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", pos);
	m_playerNode->attachObject(playerEntity);
	m_playerNode->setScale(Ogre::Vector3(0.1f,0.1f,0.1f));
}


PlayerModelHandler::~PlayerModelHandler()
{
}
