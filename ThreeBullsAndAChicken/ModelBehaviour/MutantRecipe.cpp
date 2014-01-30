#include "stdafx.h"
#include "MutantRecipe.h"
int MutantRecipe::s_count = 0;
MutantRecipe::MutantRecipe()
: m_id(++s_count)
, m_entityName("MutantNode"+boost::lexical_cast<string>(m_id))
, m_nodeName("MutantEntity"+boost::lexical_cast<string>(m_id))
{
	cout << "MutantEntity: " << m_entityName << endl;
}

MutantRecipe::~MutantRecipe()
{
	cout << "mutant recipe destrucotr" << endl;
}

Ogre::Entity* MutantRecipe::initMesh(Ogre::SceneManager* sMgr)
{
	return sMgr->createEntity(m_entityName, "ninja.mesh");
}

Ogre::AnimationState* MutantRecipe::getDie(Ogre::Entity* entity)
{
	return entity->getAnimationState("Death1");
}

Ogre::AnimationState* MutantRecipe::getWalk(Ogre::Entity* entity)
{
	return entity->getAnimationState("Walk");
}
Ogre::AnimationState* MutantRecipe::getAttack(Ogre::Entity* entity)
{
	return entity->getAnimationState("Attack1");
}
Ogre::SceneNode* MutantRecipe::initNode(Ogre::SceneManager* sMgr)
{
	auto node = sMgr->getRootSceneNode()->createChildSceneNode(m_nodeName);
	node->setScale(Ogre::Vector3(0.001, 0.001, 0.001));
	return node;
}