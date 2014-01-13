#pragma once
#include "PlayerState.h"
class PlayerNormalState:public PlayerState
{
public:
	PlayerNormalState();
	void update() override;
	~PlayerNormalState();
};

