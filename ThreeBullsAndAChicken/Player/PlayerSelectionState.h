#pragma once
#include "stdafx.h"
#include "PlayerModelHandler.h"
#include "../Enemy/Mutant.h"
#include "../UniversalBehaviourState/BehaviourState.h"

class PlayerSelectionState:public BehaviourState
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void update(UniversalModelHandler& playerModel) override;
private:
};

