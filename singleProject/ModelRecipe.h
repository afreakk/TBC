#pragma once
#include "BaseAnimation.h"
class Skritt;
enum QueryMasks
{
    PlayerMask = 1<<1,
    World = 1<<2,
    None = 1<<3
};
class ModelRecipe
{
public:
	virtual ~ModelRecipe()
	{
	}
	virtual Ogre::Entity* initMesh(Ogre::SceneManager* )=0;
	virtual BaseAnimation* getWalk(Ogre::Entity*, Skritt* skritt) = 0;
	virtual BaseAnimation* getAttack(Ogre::Entity*) = 0;
	virtual BaseAnimation* getDie(Ogre::Entity*) = 0;
	virtual BaseAnimation* getPrepare(Ogre::Entity*) = 0;
	virtual BaseAnimation* getTumble(Ogre::Entity*, Skritt*) = 0;
	virtual void attachNode(Ogre::SceneNode* node, Ogre::Entity* ent) = 0;
	virtual Ogre::SceneNode* createNode()=0;
	virtual const std::string& getMaterialName(const std::string& type) = 0;
};

