#pragma once
#include "../BehaviourState/BehaviourState.h"
class BehaviourStateSubscriber
{
public:
	virtual void notify(BEHAVOUR_STATE)=0;
};

