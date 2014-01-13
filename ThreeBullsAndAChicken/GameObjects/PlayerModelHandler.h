#pragma once
#include "OgreSceneNode.h"
#include "OgreVector3.h"
class PlayerModelHandler
{
public:
	PlayerModelHandler();
	~PlayerModelHandler();
	void init(Ogre::Vector3 pos);
private:
	Ogre::SceneNode* m_playerNode;
};

