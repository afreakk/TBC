#pragma once
#include "PlayerCameraState.h"
class PlayerCameraStateLERP:public PlayerCameraState
{
public:
	PlayerCameraStateLERP(SceneNode* playerNode);
	~PlayerCameraStateLERP();
	void update() override;
private:
	Ogre::SceneNode* m_playerNode;
	Real m_lerp;
	Real m_r;
	Real m_distance;
	Real m_height;
	Real m_spinSpeed;
};

