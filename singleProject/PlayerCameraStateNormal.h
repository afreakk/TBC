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
	Player* m_player;
	Ogre::Real m_height;
	Ogre::Real m_lerp;

};

