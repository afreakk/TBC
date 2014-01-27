#pragma once
#include "PlayerCameraState.h"
#include "../Enemy/EnemyHandler.h"
class PlayerCameraStateSelection:public PlayerCameraState
{
public:
	PlayerCameraStateSelection();
	~PlayerCameraStateSelection();
	void update() override ;
private:
	const std::vector<unique_ptr<MutantHandler> >& m_mutants; 
	Ogre::Camera* m_camera;
};

