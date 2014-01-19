#pragma once
#include "PlayerCameraState.h"
class PlayerCameraStateLERP:public PlayerCameraState
{
public:
	PlayerCameraStateLERP();
	~PlayerCameraStateLERP();
	void update() override;
	void init(SceneNode*) override;
	void exit() override;
private:
	Ogre::Camera* m_camera;
	Ogre::SceneNode* m_playerNode;
};

