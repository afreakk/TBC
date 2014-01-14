#include "stdafx.h"
#include "PlayerModelHandler.h"

#include "../OgreCore/OgreCore.h"
#include "../Other/UnitCircleMovement.h"
using namespace Ogre;
PlayerModelHandler::PlayerModelHandler()
{
}
PlayerModelHandler::~PlayerModelHandler()
{
}

void PlayerModelHandler::normalTranslate(const Ogre::Real& rInc)
{
	m_rad += rInc;
	normalSetPosition();
}

Ogre::SceneNode* PlayerModelHandler::getNode()
{
	return m_playerNode;
}
// initialise entity, node & start position
void PlayerModelHandler::init(const Real& r, const Real& d, const Real& h) 
{
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	m_rad = r, m_dist = d, m_height = h;
	m_playerEntity = initMesh(sMgr);
	m_playerNode = initPlayerNode(sMgr, m_playerEntity);
	normalSetPosition();
}
Ogre::Entity* PlayerModelHandler::initMesh(SceneManager* sMgr)
{
	Entity* playerEntity =  sMgr->createEntity("Player", "ninja.mesh");
	return playerEntity;
}

Ogre::SceneNode* PlayerModelHandler::initPlayerNode(Ogre::SceneManager* sMgr, Ogre::Entity* playerEntity)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
	node->attachObject(playerEntity);
	node->setScale(Ogre::Vector3(0.01,0.01,0.01));
	return node;
}

void PlayerModelHandler::normalSetPosition()
{
	m_playerNode->setPosition(UnitCircleMovement::posFromR(m_rad, m_dist, m_height));
}
