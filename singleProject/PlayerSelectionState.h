#pragma once
#include "ModelHandler.h"
#include "Mutant.h"
#include "BehaviourState.h"

class PlayerSelectionState:public BehaviourState
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void update(ModelHandler& playerModel) override;
private:
};

