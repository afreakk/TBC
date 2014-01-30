#include "stdafx.h"
#include "ModelRecipePlayer.h"

ModelRecipePlayer::ModelRecipePlayer()
{
}
ModelRecipePlayer::~ModelRecipePlayer()
{

}
Ogre::Entity* ModelRecipePlayer::initMesh(Ogre::SceneManager* sMgr)
{
	return sMgr->createEntity("PlayerEntity", "ninja.mesh");
}

Ogre::AnimationState* ModelRecipePlayer::getDie(Ogre::Entity* entity)
{
	return entity->getAnimationState("Death1");
}
Ogre::AnimationState* ModelRecipePlayer::getWalk(Ogre::Entity* entity)
{
	return entity->getAnimationState("Walk");
}
Ogre::AnimationState* ModelRecipePlayer::getAttack(Ogre::Entity* entity)
{
	auto attack =  entity->getAnimationState("Attack1");
	return attack;
}
Ogre::SceneNode* ModelRecipePlayer::initNode(Ogre::SceneManager* sMgr)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
	node->setScale(Ogre::Vector3(0.001, 0.001, 0.001));
	return node;
}
Ogre::AnimationState* ModelRecipePlayer::getBlock(Ogre::Entity* entity)
{
	return entity->getAnimationState("Block");
}