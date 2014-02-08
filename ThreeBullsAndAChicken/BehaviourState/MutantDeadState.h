#pragma once
#include "BehaviourStateDead.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"
class MutantDeadState : public BehaviourStateDead
{
public:
	MutantDeadState(Vector3 killedDirection, ModelHandlerMutant& mutantModelHandler);
	~MutantDeadState();
};

