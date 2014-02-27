#pragma once
#include "BaseAnimation.h"
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
	virtual BaseAnimation* getWalk(Ogre::Entity*) = 0;
	virtual BaseAnimation* getAttack(Ogre::Entity*) = 0;
	virtual BaseAnimation* getDie(Ogre::Entity*) = 0;
	virtual BaseAnimation* getPrepare(Ogre::Entity*) = 0;
	virtual BaseAnimation* getTumble(Ogre::Entity*) = 0;
	virtual void attachNode(Ogre::SceneNode* node, Ogre::Entity* ent) = 0;
	virtual Ogre::SceneNode* createNode()=0;
	virtual const std::string& getMaterialName() = 0;
	const std::string& getName()
	{
		return m_name;
	}
protected:
	std::string m_name;
};

