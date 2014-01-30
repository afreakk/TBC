#pragma once
#include "stdafx.h"
class ModelRecipe
{
public:
	virtual ~ModelRecipe()
	{
	}
	virtual Ogre::Entity* initMesh(Ogre::SceneManager* )=0;
	virtual Ogre::SceneNode* initNode(Ogre::SceneManager* )=0;
	virtual Ogre::AnimationState* getWalk(Ogre::Entity*) = 0;
	virtual Ogre::AnimationState* getAttack(Ogre::Entity*) = 0;
	virtual Ogre::AnimationState* getDie(Ogre::Entity*) = 0;
};

