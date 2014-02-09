#include "stdafx.h"
#include "MutantHandlerStateAttackRanged.h"
#include "Mutant.h"
#include "BehaviourStateAttackRanged.h"

MutantHandlerStateAttackRanged::MutantHandlerStateAttackRanged(Mutant* mutant, SceneNode* playerNode)
: HandlerState(MUTANT_HANDLER_STATE::RANGED_ATTACK)
, m_mutant(mutant)
, m_attackState{ new BehaviourStateAttackRanged() }
{
	m_mutant->setState(m_attackState.get());
}


MutantHandlerStateAttackRanged::~MutantHandlerStateAttackRanged()
{
}

void MutantHandlerStateAttackRanged::update()
{
}