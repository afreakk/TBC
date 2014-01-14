#pragma once
#include "OgreSceneNode.h"
class PlayerCameraState
{
public:
	virtual void update()=0;
	virtual void init(Ogre::SceneNode*) = 0;
	virtual void exit() = 0;
};

