#include "stdafx.h"
#include "ModelRecipeMutant.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"

int ModelRecipeMutant::s_count = 0;
ModelRecipeMutant::ModelRecipeMutant()
: m_id(++s_count)
, m_entityName("MutantNode"+boost::lexical_cast<string>(m_id))
, m_nodeName("MutantEntity"+boost::lexical_cast<string>(m_id))
{
	cout << "MutantEntity: " << m_entityName << endl;
}

ModelRecipeMutant::~ModelRecipeMutant()
{
	cout << "mutant recipe destrucotr" << endl;
}

Ogre::Entity* ModelRecipeMutant::initMesh(Ogre::SceneManager* sMgr)
{
	auto ent = sMgr->createEntity(m_entityName, "ninja.mesh");
	return ent;
}

BaseAnimation* ModelRecipeMutant::getDie(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Death1"));
	anims.push_back(entity->getAnimationState("Death2"));
	return new AnimationDie(anims);
}

BaseAnimation* ModelRecipeMutant::getWalk(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Walk"));
	return new AnimationWalk(anims);
}
BaseAnimation* ModelRecipeMutant::getAttack(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Attack1"));
	anims.push_back(entity->getAnimationState("Attack2"));
	anims.push_back(entity->getAnimationState("Attack3"));
	return new AnimationAttack(anims);
}
Ogre::SceneNode* ModelRecipeMutant::initNode(Ogre::SceneManager* sMgr)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode(m_nodeName);
	return node;
}