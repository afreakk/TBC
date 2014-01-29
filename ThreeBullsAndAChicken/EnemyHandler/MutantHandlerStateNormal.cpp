#include "stdafx.h"
#include "MutantHandlerStateNormal.h"
#include "../Enemy/MutantGlobalStats.h"

MutantHandlerStateNormal::MutantHandlerStateNormal(Mutant* mutant, SceneNode* playerNode)
: HandlerState(MUTANT_HANDLER_STATE::NORMAL)
, m_mutant(mutant)
, m_playerNode(playerNode)
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
	if (m_mutant->getModelHandler().getNode()->getPosition().distance(m_playerNode->getPosition()) < MutantGlobalStats::getSingleton().getAttackDistance())
		m_state = MUTANT_HANDLER_STATE::LERP;
}