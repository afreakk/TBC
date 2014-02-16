#include "stdafx.h"
#include "MutantHandlerStateNormal.h"
#include "MutantGlobalStats.h"
#include "Mutant.h"
#include "BehaviourStateNormal.h"
#include "ModelHandlerMutant.h"
MutantHandlerStateNormal::MutantHandlerStateNormal(Mutant* mutant,const PolarCoordinates& plarerCoords)
: HandlerState(MUTANT_HANDLER_STATE::NORMAL)
, m_mutant(mutant)
, m_playerCoords(plarerCoords)
, m_walkingDirection{ m_mutant->getPolarCoordinates().r < m_playerCoords.r ? NormalDirection::dirRight : NormalDirection::dirLeft }
, m_normalState{ new BehaviourStateNormal{ &m_walkingDirection , &MutantGlobalStats::getSingleton().getWalkSpeed()}}
{
	m_mutant->setState(m_normalState.get());
}


MutantHandlerStateNormal::~MutantHandlerStateNormal()
{
}

void MutantHandlerStateNormal::update()
{
	if (Math::Abs(m_mutant->getPolarCoordinates().r - m_playerCoords.r) < MutantGlobalStats::getSingleton().getAttackDistance())
		m_state = getAttackState();
}

MUTANT_HANDLER_STATE MutantHandlerStateNormal::getAttackState()
{
	switch (static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).getWeaponType())
	{
	case WeaponType::SUICIDE_BOMB:
		return MUTANT_HANDLER_STATE::SUICIDE_ATTACK;
	default:
		return MUTANT_HANDLER_STATE::RANGED_ATTACK;
	}
}