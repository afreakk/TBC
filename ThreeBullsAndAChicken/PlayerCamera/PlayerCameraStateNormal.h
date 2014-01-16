#pragma once
#include "stdafx.h"
#include "PlayerCameraState.h"
class PlayerCameraStateNormal:public PlayerCameraState
{
public:
	PlayerCameraStateNormal();
	~PlayerCameraStateNormal();
	void update() override;
	void init(SceneNode*) override;
	void exit() override;
private:
	Ogre::Camera* m_camera;
	Ogre::SceneNode* m_playerNode;
	Ogre::Real m_distance;
};

