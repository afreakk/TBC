#include "stdafx.h"
#include "MutantHandlerStateNormal.h"
#include "MutantGlobalStats.h"
#include "Mutant.h"
#include "BehaviourStateNormal.h"
MutantHandlerStateNormal::MutantHandlerStateNormal(Mutant* mutant, SceneNode* playerNode)
: HandlerState(MUTANT_HANDLER_STATE::NORMAL)
, m_mutant(mutant)
, m_playerNode(playerNode)
, m_walkingDirection{ NormalDirection::Left }
, m_normalState{ new BehaviourStateNormal{ &m_walkingDirection , &MutantGlobalStats::getSingleton().getWalkSpeed()}}
{
	m_mutant->setState(m_normalState.get());
}


MutantHandlerStateNormal::~MutantHandlerStateNormal()
{
}

void MutantHandlerStateNormal::update()
{
	if (m_mutant->getModelHandler().getNode()->getPosition().distance(m_playerNode->getPosition()) < MutantGlobalStats::getSingleton().getAttackDistance())
		m_state = MUTANT_HANDLER_STATE::RANGED_ATTACK;
}