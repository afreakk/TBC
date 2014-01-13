#pragma once
#include "PlayerState.h"
#include "PlayerModelHandler.h"
class Player
{
public:
	Player();
	~Player();
	void update();
private:
	PlayerState* m_currentState;
	PlayerModelHandler m_model;

};

