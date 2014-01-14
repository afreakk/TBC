#pragma once
#include "PlayerModelHandler.h"
class PlayerState
{
public:
	virtual void update(PlayerModelHandler& )=0;
	virtual void init() = 0;
	virtual void exit() = 0;
};

