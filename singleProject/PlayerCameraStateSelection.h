#pragma once
#include "PlayerCameraState.h"
#include "Mutant.h"
class PlayerCameraStateSelection:public PlayerCameraState
{
public:
	PlayerCameraStateSelection();
	~PlayerCameraStateSelection();
	void update() override ;
private:
	Ogre::Camera* m_camera;
	Vector3 m_lookAt;
};

