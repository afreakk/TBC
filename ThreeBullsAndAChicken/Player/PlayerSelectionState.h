#pragma once
#include "stdafx.h"
#include "PlayerModelHandler.h"
#include "../BehaviourObject/Mutant.h"
#include "../BehaviourState/BehaviourState.h"

class PlayerSelectionState:public BehaviourState
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void update(UniversalModelHandler& playerModel) override;
private:
};

