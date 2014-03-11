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
	Ogre::Real m_lerp;
	static Ogre::Vector3 m_lerpedPlayerPos;

	void lerpPlayerPos(const Ogre::Real& dt);
};

