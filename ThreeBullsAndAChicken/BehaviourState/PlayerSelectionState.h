#pragma once
#include "stdafx.h"
#include "../ModelBehaviour/ModelHandler.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourState/BehaviourState.h"

class PlayerSelectionState:public BehaviourState
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void update(ModelHandler& playerModel) override;
private:
};

