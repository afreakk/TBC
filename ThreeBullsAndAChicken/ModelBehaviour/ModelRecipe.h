#pragma once
#include "stdafx.h"
#include "../ModelAnimations/BaseAnimation.h"
class ModelRecipe
{
public:
	virtual ~ModelRecipe()
	{
	}
	virtual Ogre::Entity* initMesh(Ogre::SceneManager* )=0;
	virtual Ogre::SceneNode* initNode(Ogre::SceneManager* )=0;
	virtual BaseAnimation* getWalk(Ogre::Entity*) = 0;
	virtual BaseAnimation* getAttack(Ogre::Entity*) = 0;
	virtual BaseAnimation* getDie(Ogre::Entity*) = 0;
};

