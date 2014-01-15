#pragma once
#include "PlayerState.h"
#include "PlayerModelHandler.h"
class PlayerSelectionState:public PlayerState
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void init() override;
	void exit() override;
	void update(PlayerModelHandler& playerModel) override;
};

