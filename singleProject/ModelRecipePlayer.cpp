#include "stdafx.h"
#include "ModelRecipePlayer.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"
#include "AnimationTumble.h"

ModelRecipePlayer::ModelRecipePlayer()
{
}
ModelRecipePlayer::~ModelRecipePlayer()
{

}
Ogre::Entity* ModelRecipePlayer::initMesh(Ogre::SceneManager* sMgr)
{
    Ogre::Entity* ent = sMgr->createEntity("PlayerEntity", "ninja.mesh");
	ent->setQueryFlags(QueryMasks::PlayerMask);
	ent->setUpdateBoundingBoxFromSkeleton(true);
	return ent;
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
	return node;
}
BaseAnimation* ModelRecipePlayer::getTumble(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back( entity->getAnimationState("Backflip") ) ;
	return new AnimationTumble(anims);
}