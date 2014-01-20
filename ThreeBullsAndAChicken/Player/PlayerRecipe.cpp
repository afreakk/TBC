#include "stdafx.h"
#include "PlayerRecipe.h"

PlayerRecipe::PlayerRecipe()
{
	m_entityName = "PlayerEntity";
	m_fileName = "ninja.mesh";
	m_nodeName = "PlayerNode";
	m_walkAnimationName = "Walk";
}
PlayerRecipe::~PlayerRecipe()
{

}
Ogre::Entity* PlayerRecipe::initMesh(Ogre::SceneManager* sMgr)
{
	return sMgr->createEntity(m_entityName, m_fileName);
}

Ogre::AnimationState* PlayerRecipe::getDie(Ogre::Entity* entity)
{
	return entity->getAnimationState("Death1");
}
Ogre::AnimationState* PlayerRecipe::getWalk(Ogre::Entity* entity)
{
	return entity->getAnimationState(m_walkAnimationName);
}
Ogre::AnimationState* PlayerRecipe::getAttack(Ogre::Entity* entity)
{
	auto attack =  entity->getAnimationState("Attack1");
	return attack;
}
Ogre::SceneNode* PlayerRecipe::initNode(Ogre::SceneManager* sMgr)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode(m_nodeName);
	node->setScale(Ogre::Vector3(0.001, 0.001, 0.001));
	return node;
}
Ogre::AnimationState* PlayerRecipe::getBlock(Ogre::Entity* entity)
{
	return entity->getAnimationState("Block");
}