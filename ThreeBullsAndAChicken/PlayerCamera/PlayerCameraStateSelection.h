#pragma once
#include "PlayerCameraState.h"
#include "../BehaviourObject/Mutant.h"
class PlayerCameraStateSelection:public PlayerCameraState
{
public:
	PlayerCameraStateSelection();
	~PlayerCameraStateSelection();
	void update() override ;
private:
	const std::vector<unique_ptr<Mutant> >& m_mutants; 
	Ogre::Camera* m_camera;
};

