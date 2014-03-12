
#include "stdafx.h"
#include "MutantHandlerStateTumble.h"
#include "PlayerGlobalStats.h"
#include "BehaviourStateTumble.h"
#include "UnitCircleMovement.h"
#include "Mutant.h"
#include "Occupado.h"
#include "LaneSettings.h"


MutantHandlerStateTumble::MutantHandlerStateTumble( Mutant* mutant, TUMBLE_DIRECTION direction)
: HandlerState(MUTANT_HANDLER_STATE::TUMBLE)
, m_direction(direction==TUMBLE_DIRECTION::DIRECTION_NONE ? getTumbleDirection(mutant) : direction)
, m_mutant(mutant)
, m_currentTumbleState(new BehaviourStateTumble(vectorFromTumbleDirection(m_mutant->getNode()->getPosition(), m_direction),
PlayerGlobalStats::getSingleton().getTumbleSpeed()))
{
	m_mutant->setState(m_currentTumbleState.get());
}


MutantHandlerStateTumble::~MutantHandlerStateTumble()
{
}

void MutantHandlerStateTumble::update()
{
	if (m_currentTumbleState->hasReachedEnd())
		m_state = MUTANT_HANDLER_STATE::NORMAL;

}
TUMBLE_DIRECTION MutantHandlerStateTumble::getTumbleDirection(Mutant* mutant)
{
	unsigned lane = LaneSettings::getSingleton().getClosestLane(mutant->getNode()->getPosition());
	if (lane == 0)
		return TUMBLE_DIRECTION::DIRECTION_OUT;
	else if (lane + 1 == LaneSettings::getSingleton().getLaneCount())
		return TUMBLE_DIRECTION::DIRECTION_IN;
	else
		return Ogre::Math::RangeRandom(-1.0f, 1.0f) > 0.0 ? TUMBLE_DIRECTION::DIRECTION_IN : TUMBLE_DIRECTION::DIRECTION_OUT;
}