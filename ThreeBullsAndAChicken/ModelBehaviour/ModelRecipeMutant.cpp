#include "stdafx.h"
#include "ModelRecipeMutant.h"
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
	return sMgr->createEntity(m_entityName, "ninja.mesh");
}

Ogre::AnimationState* ModelRecipeMutant::getDie(Ogre::Entity* entity)
{
	return entity->getAnimationState("Death1");
}

Ogre::AnimationState* ModelRecipeMutant::getWalk(Ogre::Entity* entity)
{
	return entity->getAnimationState("Walk");
}
Ogre::AnimationState* ModelRecipeMutant::getAttack(Ogre::Entity* entity)
{
	return entity->getAnimationState("Attack1");
}
Ogre::SceneNode* ModelRecipeMutant::initNode(Ogre::SceneManager* sMgr)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode(m_nodeName);
	node->setScale(Ogre::Vector3(0.001, 0.001, 0.001));
	return node;
}