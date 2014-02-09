#pragma once
#include "BehaviourState.h"
class BehaviourStateDead : public BehaviourState
{
public:
	BehaviourStateDead();
	~BehaviourStateDead();
	virtual void update(ModelHandler&)override;
};

