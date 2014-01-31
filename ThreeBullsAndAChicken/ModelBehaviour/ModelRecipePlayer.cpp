#include "stdafx.h"
#include "ModelRecipePlayer.h"
#include "../ModelAnimations/AnimationAttack.h"
#include "../ModelAnimations/AnimationWalk.h"
#include "../ModelAnimations/AnimationDie.h"

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

BaseAnimation* ModelRecipePlayer::getDie(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Death1"));
	anims.push_back(entity->getAnimationState("Death2"));
	return new AnimationDie(anims);
}
BaseAnimation* ModelRecipePlayer::getWalk(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Walk"));
	return new AnimationWalk(anims);
}
BaseAnimation* ModelRecipePlayer::getAttack(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Attack1"));
	anims.push_back(entity->getAnimationState("Attack2"));
	anims.push_back(entity->getAnimationState("Attack3"));
	return new AnimationAttack(anims);
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