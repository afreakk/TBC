#include "stdafx.h"
#include "UniversalModelHandler.h"
#include "boost\lexical_cast.hpp"

using namespace Ogre;

int UniversalModelHandler::s_count = 0;

UniversalModelHandler::UniversalModelHandler(string entityName, string fileName, string walkAnimName, string nodeName)
: m_entity(nullptr), m_node(nullptr), m_animationState(nullptr)
, m_entityName(entityName), m_fileName(fileName), m_walkAnimationName(walkAnimName), m_nodeName(nodeName)
, m_id(++s_count)
{
	m_entityName.append(boost::lexical_cast<string> (m_id));
	m_nodeName.append(boost::lexical_cast<string> (m_id));

}
UniversalModelHandler::~UniversalModelHandler()
{
}

Entity* UniversalModelHandler::getEntity() const
{
	return m_entity;
}
void UniversalModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	m_animationState->addTime(Ogre::Math::Abs(rInc)*20.0);
	m_normalPosition.r += rInc;
	UnitCircleMovement::normalSetDirection(m_node, getNormalPos(), activeDirection);
	UnitCircleMovement::normalSetPosition(m_node, getNormalPos());
}

Ogre::SceneNode* UniversalModelHandler::getNode() const 
{
	return m_node;
}
const NormalPosition& UniversalModelHandler::getNormalPos() const 
{
	return m_normalPosition;
}

// initialise entity, node & start position
void UniversalModelHandler::init(NormalPosition pos) 
{
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();

	m_normalPosition = pos;
	m_entity = initMesh(sMgr);
	m_node = initPlayerNode(sMgr, m_entity);
	UnitCircleMovement::normalSetPosition(m_node, m_normalPosition);
}
Ogre::Entity* UniversalModelHandler::initMesh(SceneManager* sMgr)
{
	Entity* playerEntity =  sMgr->createEntity(m_entityName, m_fileName);
	m_animationState = playerEntity->getAnimationState(m_walkAnimationName);
	m_animationState->setLoop(true);
	m_animationState->setEnabled(true);

	return playerEntity;
}

Ogre::SceneNode* UniversalModelHandler::initPlayerNode(Ogre::SceneManager* sMgr, Ogre::Entity* playerEntity)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode(m_nodeName);
	node->attachObject(playerEntity);
	node->setScale(Ogre::Vector3(0.001, 0.001, 0.001));
	return node;
}
