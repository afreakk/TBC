#pragma once
#include "stdafx.h"
#include "../Other/CreationRecipes.h"
class PlayerRecipe : public CreationRecipes
{
public:
	PlayerRecipe();
	~PlayerRecipe();
	Ogre::Entity* initMesh(Ogre::SceneManager* sMgr) override;
	Ogre::SceneNode* initNode(Ogre::SceneManager* sMgr) override;
	Ogre::AnimationState* getWalk(Ogre::Entity*) override;
	Ogre::AnimationState* getAttack(Ogre::Entity*) override;
	Ogre::AnimationState* getDie(Ogre::Entity*) override;
	Ogre::AnimationState* getBlock(Ogre::Entity*);
private:
};

