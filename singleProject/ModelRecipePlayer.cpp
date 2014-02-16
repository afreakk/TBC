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
	unsigned short src, dest;
	if (!ent->getMesh()->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		ent->getMesh()->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
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
void ModelRecipePlayer::attachNode(Ogre::SceneNode* node, Ogre::Entity* ent)
{
	node->attachObject(ent);
}
BaseAnimation* ModelRecipePlayer::getTumble(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back( entity->getAnimationState("Backflip") ) ;
	return new AnimationTumble(anims);
}