#pragma once
#include "stdafx.h"
class CreationRecipes
{
public:
	virtual Ogre::Entity* initMesh(Ogre::SceneManager* )=0;
	virtual Ogre::SceneNode* initNode(Ogre::SceneManager* )=0;
	virtual Ogre::AnimationState* getWalk(Ogre::Entity*) = 0;
	virtual Ogre::AnimationState* getAttack(Ogre::Entity*) = 0;
	virtual Ogre::AnimationState* getDie(Ogre::Entity*) = 0;
	string getNodeName() const
	{
		return m_nodeName;
	}
	string getEntityName() const
	{
		return m_entityName;
	}
	string getFileName() const
	{
		return m_fileName;
	}

protected:
	string m_nodeName;
	string m_entityName;
	string m_fileName;
	string m_walkAnimationName;
};

