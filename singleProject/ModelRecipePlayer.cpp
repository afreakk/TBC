#include "stdafx.h"
#include "ModelRecipePlayer.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"
#include "AnimationTumble.h"
#include "OgreCore.h"
#include "AnimationPrepare.h"

ModelRecipePlayer::ModelRecipePlayer()
: m_materialName("Examples/Ninja")
{
	m_name = "Player";
}
ModelRecipePlayer::~ModelRecipePlayer()
{

}
BaseAnimation* ModelRecipePlayer::getPrepare(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Stealth"));
	return new AnimationPrepare(anims);
}
Ogre::Entity* ModelRecipePlayer::initMesh(Ogre::SceneManager* sMgr)
{
	auto resourcePtr =  MeshManager::getSingleton().createOrRetrieve("ninja.mesh", "Models") ;
	auto mesh = resourcePtr.first.dynamicCast<Ogre::Mesh>();
	unsigned short src, dest;
	if (!mesh->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		mesh->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
    Ogre::Entity* ent = sMgr->createEntity("PlayerEntity", mesh);
	ent->setCastShadows(true);
	ent->setUpdateBoundingBoxFromSkeleton(true);
	ent->setQueryFlags(QueryMasks::PlayerMask);
	return ent;
}

const std::string& ModelRecipePlayer::getMaterialName()
{
	return m_materialName;
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
	/*auto p = OgreCore::getSingleton().getSceneMgr()->createEntity("lowpoly_mainchar_final.mesh");
	unsigned short src, dest;
	if (!p->getMesh()->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		p->getMesh()->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
	auto cNode = node->createChildSceneNode(Vector3(0.0,70.0,0.0));
	cNode->scale(Vector3(1.0));
	cNode->attachObject(p);*/
	node->attachObject(ent);
}
BaseAnimation* ModelRecipePlayer::getTumble(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back( entity->getAnimationState("Backflip") ) ;
	return new AnimationTumble(anims);
}
Ogre::SceneNode* ModelRecipePlayer::createNode()
{
	return OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode("Player");
}