#include "stdafx.h"
#include "ModelRecipeMutantSuicide.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"

int ModelRecipeMutantSuicide::s_count = 0;
ModelRecipeMutantSuicide::ModelRecipeMutantSuicide()
: m_id(++s_count)
, m_entityName("MutantNodeSuicide"+boost::lexical_cast<string>(m_id))
, m_nodeName("MutantEntitySuicide"+boost::lexical_cast<string>(m_id))
{
}

ModelRecipeMutantSuicide::~ModelRecipeMutantSuicide()
{
}

Ogre::Entity* ModelRecipeMutantSuicide::initMesh(Ogre::SceneManager* sMgr)
{
	auto ent = sMgr->createEntity(m_entityName, "robot.mesh");
	ent->setUpdateBoundingBoxFromSkeleton(true);
	unsigned short src, dest;
	if (!ent->getMesh()->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		ent->getMesh()->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
	return ent;
}

BaseAnimation* ModelRecipeMutantSuicide::getDie(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Die"));
	return new AnimationDie(anims);
}

BaseAnimation* ModelRecipeMutantSuicide::getWalk(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Walk"));
	return new AnimationWalk(anims);
}
BaseAnimation* ModelRecipeMutantSuicide::getAttack(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Slump"));
	return new AnimationAttack(anims);
}
void ModelRecipeMutantSuicide::attachNode(Ogre::SceneNode* node, Ogre::Entity* ent)
{
	auto childNode = node->createChildSceneNode();
    childNode->rotate(Vector3(0.0, 1.0, 0.0), Angle(90.0));
	childNode->scale(Vector3(3.0));
	childNode->attachObject(ent);
}
