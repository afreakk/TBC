#include "stdafx.h"
#include "ModelRecipePlayer.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"
#include "AnimationTumble.h"
#include "OgreCore.h"
#include "AnimationPrepare.h"

ModelRecipePlayer::ModelRecipePlayer()
{
}
ModelRecipePlayer::~ModelRecipePlayer()
{

}
BaseAnimation* ModelRecipePlayer::getPrepare(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("all"));
	return new AnimationPrepare(anims);
}
Ogre::Entity* ModelRecipePlayer::initMesh(Ogre::SceneManager* sMgr)
{
	auto resourcePtr =  MeshManager::getSingleton().createOrRetrieve("All.mesh", "Models") ;
	auto mesh = resourcePtr.first.dynamicCast<Ogre::Mesh>();
	unsigned short src, dest;
	if (!mesh->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		mesh->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
    Ogre::Entity* ent = sMgr->createEntity("PlayerEntity", mesh);
	ent->getMesh()->buildEdgeList();
//	ent->setCastShadows(true);
	ent->setUpdateBoundingBoxFromSkeleton(true);
	ent->setQueryFlags(QueryMasks::PlayerMask);
	return ent;
}

const std::string& ModelRecipePlayer::getMaterialName(const std::string& typ)
{
	return "IDUNNOLOL";
}
BaseAnimation* ModelRecipePlayer::getDie(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("all"));
	return new AnimationDieHero(anims);
}
BaseAnimation* ModelRecipePlayer::getWalk(Ogre::Entity* entity, Skritt* skritt)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("all"));
	return new AnimationWalkHero(anims, skritt);
}
BaseAnimation* ModelRecipePlayer::getAttack(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("all"));
//	anims.push_back(entity->getAnimationState("Attack2"));
//	anims.push_back(entity->getAnimationState("Attack3"));
	return new AnimationAttackHero(anims);
}
void ModelRecipePlayer::attachNode(Ogre::SceneNode* node, Ogre::Entity* ent)
{
	/*auto p = OgreCore::getSingleton().getSceneMgr()->createEntity("lowpoly_mainchar_final.mesh");
	unsigned short src, dest;
	if (!p->getMesh()->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		p->getMesh()->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
	auto cNode = node->createChildSceneNode(Vector3(0.0,70.0,0.0));
	cNode->scale(Vector3(1.0));
	cNode->attachObject(p);*/
	auto childNode = node->createChildSceneNode();
	childNode->attachObject(ent);
	childNode->setScale(Vector3(2.5f));
	childNode->rotate(Vector3::UNIT_Y, Ogre::Radian(Math::PI));
}
#include "AnimationIdle.h"
BaseAnimation* ModelRecipePlayer::getIdle(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back( entity->getAnimationState("all") ) ;
	return new AnimationIdleHero(anims);
}
BaseAnimation* ModelRecipePlayer::getTumble(Ogre::Entity* entity, Skritt* skritt)
{
	std::vector<AnimationState*> anims;
	anims.push_back( entity->getAnimationState("all") ) ;
	return new AnimationWalkHero(anims, skritt);
}
Ogre::SceneNode* ModelRecipePlayer::createNode()
{
	return OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode("Player");
}