#include "stdafx.h"
#include "MutantHandlerStateNormal.h"
#include "../Enemy/MutantGlobalStats.h"

MutantHandlerStateNormal::MutantHandlerStateNormal(Mutant* mutant)
: HandlerState(MUTANT_HANDLER_STATE::NORMAL)
, m_mutant(mutant)
, m_walkingDirection{ NormalDirection::Right }
, m_normalState{ new BehaviourStateNormal{ &m_walkingDirection , &MutantGlobalStats::getSingleton().getWalkSpeed()}}
{
	m_mutant->setState(m_normalState.get());
}


MutantHandlerStateNormal::~MutantHandlerStateNormal()
{
}

void MutantHandlerStateNormal::update()
{
}