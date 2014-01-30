#include "stdafx.h"
#include "MutantHandlerStateDead.h"


MutantHandlerStateDead::MutantHandlerStateDead(Mutant* mutant)
: HandlerState(MUTANT_HANDLER_STATE::DEAD)
, m_mutant(mutant)
, m_deadState(new BehaviourStateDead())
{
	m_mutant->setState(m_deadState.get());
}


MutantHandlerStateDead::~MutantHandlerStateDead()
{
}

void MutantHandlerStateDead::update()
{

}