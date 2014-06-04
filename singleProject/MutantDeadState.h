#pragma once
#include "BehaviourStateDead.h"
#include "ModelHandlerMutant.h"
class MutantDeadState : public BehaviourStateDead
{
public:
	MutantDeadState(Vector3 killedDirection, ModelHandlerMutant& mutantModelHandler);
	~MutantDeadState();
	void update(ModelHandler& m) override;
};

