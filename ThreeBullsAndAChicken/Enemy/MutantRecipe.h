#pragma once
#include "stdafx.h"
#include "../Other/CreationRecipes.h"
class MutantRecipe:public CreationRecipes
{
public:
	MutantRecipe();
	~MutantRecipe();
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr) override;
	Ogre::SceneNode* initNode(Ogre::SceneManager* sMgr) override;
	Ogre::AnimationState* getWalk(Ogre::Entity*) override;
	Ogre::AnimationState* getAttack(Ogre::Entity*) override;
	Ogre::AnimationState* getDie(Ogre::Entity*) override;
private:
	const int m_id;
	static int s_count;
};

