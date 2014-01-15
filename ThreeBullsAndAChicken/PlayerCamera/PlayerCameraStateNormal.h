#pragma once
#include "PlayerCameraState.h"
#include "OgreCamera.h"
class PlayerCameraStateNormal:public PlayerCameraState
{
public:
	PlayerCameraStateNormal();
	~PlayerCameraStateNormal();
	void update() override;
	void init(Ogre::SceneNode*) override;
	void exit() override;
private:
	Ogre::Camera* m_camera;
	Ogre::SceneNode* m_playerNode;
	Ogre::Real m_distance;
};

