#pragma once
#include "BaseAnimation.h"
enum QueryMasks
{
    PlayerMask = 1<<0,
    World = 2<<0,
    None = 3<<0
};
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

