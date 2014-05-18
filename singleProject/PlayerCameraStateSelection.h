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
	Vector3 m_lookAt;
};

