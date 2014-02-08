#include "stdafx.h"
#include "MutantHandlerStateDead.h"
#include "../Containers/PlayerContainer.h"

MutantHandlerStateDead::MutantHandlerStateDead(Mutant* mutant)
: HandlerState(MUTANT_HANDLER_STATE::DEAD)
, m_mutant(mutant)
, m_deadState(new MutantDeadState( PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition() - m_mutant->getNode()->getPosition(), static_cast<ModelHandlerMutant&>(mutant->getModelHandler()) ))
{
	m_mutant->setState(m_deadState.get());
}


MutantHandlerStateDead::~MutantHandlerStateDead()
{
}

void MutantHandlerStateDead::update()
{

}