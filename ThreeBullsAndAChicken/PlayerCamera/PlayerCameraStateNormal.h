#pragma once
#include "stdafx.h"
#include "PlayerCameraState.h"
class PlayerCameraStateNormal:public PlayerCameraState
{
public:
	PlayerCameraStateNormal(SceneNode*);
	~PlayerCameraStateNormal();
	void update() override;
private:
	Ogre::Camera* m_camera;
	Ogre::SceneNode* m_playerNode;
	Ogre::Real m_distance;
	Ogre::Real m_height;
	Real m_lerp;
};

