#pragma once
#include "PlayerCameraState.h"
class Player;
class PlayerCameraStateNormal:public PlayerCameraState
{
public:
	PlayerCameraStateNormal(Player*);
	~PlayerCameraStateNormal();
	void update() override;
private:
	Ogre::Camera* m_camera;
	Player* m_player;
	Ogre::Real m_distance;
	Ogre::Real m_height;
	Real m_lerp;
};

