#pragma once
#include "stdafx.h"
#include "../UniversalBehaviourState/BehaviourState.h"
class MutantNormalState:public BehaviourState
{
public:
	MutantNormalState();
	~MutantNormalState();
	void update(UniversalModelHandler& )override;
private:
};

