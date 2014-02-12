#include "stdafx.h"
#include "MutantDeadState.h"
#include "MainUpdate.h"

MutantDeadState::MutantDeadState(Vector3 killedDirection, ModelHandlerMutant& mutantModelHandler)
: BehaviourStateDead()
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	mutantModelHandler.damage(killedDirection.normalisedCopy());
}

MutantDeadState::~MutantDeadState()
{
}