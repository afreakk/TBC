#include "stdafx.h"
#include "MutantDeadState.h"
#include "../GameLevels/MainUpdate.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"

MutantDeadState::MutantDeadState(Vector3 killedDirection)
: BehaviourStateDead()
, m_killerDirection(killedDirection)
{
}


void MutantDeadState::update(ModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	static_cast<ModelHandlerMutant&>(modelHandler).damage(m_killerDirection.normalisedCopy());
	BehaviourStateDead::update(modelHandler);
}
MutantDeadState::~MutantDeadState()
{
}
