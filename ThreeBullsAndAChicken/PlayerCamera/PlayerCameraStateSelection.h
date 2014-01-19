#pragma once
#include "PlayerCameraState.h"
class PlayerCameraStateSelection:public PlayerCameraState
{
public:
	PlayerCameraStateSelection();
	~PlayerCameraStateSelection();
	void update() override ;
	void init(SceneNode*)  override;
	void exit()  override;
private:
	Ogre::Camera* m_camera;
};

