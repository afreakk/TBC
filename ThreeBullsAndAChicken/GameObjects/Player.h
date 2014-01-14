#pragma once
#include "PlayerState.h"
#include "PlayerModelHandler.h"
#include "../Camera/PlayerCameraStateNormal.h"
class Player
{
public:
	Player();
	~Player();
	void update();
private:
	PlayerState* m_currentState;
	PlayerCameraState* m_currentCameraState;
	PlayerModelHandler m_model;


};

