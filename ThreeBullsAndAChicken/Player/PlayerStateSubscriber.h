#pragma once
#include "PlayerState.h"
class PlayerStateSubscriber
{
public:
	virtual void notify(PLAYER_STATES)=0;
};

