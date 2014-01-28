#pragma once
#include "../UniversalBehaviourState/BehaviourState.h"
class BehaviourStateSubscriber
{
public:
	virtual void notify(BEHAVOUR_STATE)=0;
};

