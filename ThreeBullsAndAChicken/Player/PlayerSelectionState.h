#pragma once
#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerModelHandler.h"
#include "../Enemy/Mutant.h"

class PlayerSelectionState:public PlayerState
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void update(PlayerModelHandler& playerModel) override;
private:
};

