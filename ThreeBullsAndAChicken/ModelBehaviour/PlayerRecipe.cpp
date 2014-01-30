#include "stdafx.h"
#include "PlayerRecipe.h"

PlayerRecipe::PlayerRecipe()
{
}
PlayerRecipe::~PlayerRecipe()
{

}
Ogre::Entity* PlayerRecipe::initMesh(Ogre::SceneManager* sMgr)
{
	return sMgr->createEntity("PlayerEntity", "ninja.mesh");
}

Ogre::AnimationState* PlayerRecipe::getDie(Ogre::Entity* entity)
{
	return entity->getAnimationState("Death1");
}
Ogre::AnimationState* PlayerRecipe::getWalk(Ogre::Entity* entity)
{
	return entity->getAnimationState("Walk");
}
Ogre::AnimationState* PlayerRecipe::getAttack(Ogre::Entity* entity)
{
	auto attack =  entity->getAnimationState("Attack1");
	return attack;
}
Ogre::SceneNode* PlayerRecipe::initNode(Ogre::SceneManager* sMgr)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
	node->setScale(Ogre::Vector3(0.001, 0.001, 0.001));
	return node;
}
Ogre::AnimationState* PlayerRecipe::getBlock(Ogre::Entity* entity)
{
	return entity->getAnimationState("Block");
}