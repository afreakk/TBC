#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateDead : public BehaviourState
{
public:
	BehaviourStateDead();
	~BehaviourStateDead();
	virtual void update(ModelHandler&)override;
};

