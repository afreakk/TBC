#pragma once
#include "stdafx.h"
#include "PlayerCameraState.h"
class PlayerCameraStateLERP:public PlayerCameraState
{
public:
	PlayerCameraStateLERP(SceneNode* playerNode);
	~PlayerCameraStateLERP();
	void update() override;
private:
	Ogre::Camera* m_camera;
	Ogre::SceneNode* m_playerNode;
	Real m_lerp;
	Real m_r;
};

