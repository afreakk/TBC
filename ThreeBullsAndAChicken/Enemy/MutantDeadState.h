#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class MutantDeadState : public BehaviourState
{
public:
	MutantDeadState();
	~MutantDeadState();
	void update(UniversalModelHandler&)override;
};

