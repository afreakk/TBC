#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateDead : public BehaviourState
{
public:
	BehaviourStateDead();
	~BehaviourStateDead();
	void update(UniversalModelHandler&)override;
};

