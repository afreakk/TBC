#include "stdafx.h"
#include "MutantHandlerStateNormal.h"
#include "MutantGlobalStats.h"
#include "Mutant.h"
#include "BehaviourStateNormal.h"
#include "ModelHandlerMutant.h"
#include "PlayerContainer.h"
#include "Player.h"
MutantHandlerStateNormal::MutantHandlerStateNormal(Mutant* mutant,const PolarCoordinates& plarerCoords)
: HandlerState(MUTANT_HANDLER_STATE::NORMAL)
, m_mutant(mutant)
, m_playerCoords(plarerCoords)
, m_walkingDirection{ m_mutant->getPolarCoordinates().theta < m_playerCoords.theta ? NormalDirection::dirRight : NormalDirection::dirLeft }
, m_normalState{ new BehaviourStateNormal{ &m_walkingDirection , &MutantGlobalStats::getSingleton().getWalkSpeed()}}
{
	m_mutant->setState(m_normalState.get());
}


MutantHandlerStateNormal::~MutantHandlerStateNormal()
{
}
void MutantHandlerStateNormal::update()
{
	steerTowardsPlayer();
	if (Math::Abs(m_mutant->getPolarCoordinates().theta - m_playerCoords.theta) < MutantGlobalStats::getSingleton().getAttackDistance()
		|| static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).getWeaponType() == WeaponType::SUICIDE_BOMB )
		goAttack();
	if (!m_normalState->getSuccess())
		m_state = MUTANT_HANDLER_STATE::TUMBLE;
}

void MutantHandlerStateNormal::goAttack()
{
	switch (static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).getWeaponType())
	{
	case WeaponType::SUICIDE_BOMB:
		m_state = MUTANT_HANDLER_STATE::SUICIDE_ATTACK;
		break;
	default:
		m_state = MUTANT_HANDLER_STATE::RANGED_ATTACK;
	}
}
void MutantHandlerStateNormal::steerTowardsPlayer()
{
	if (m_mutant->getPolarCoordinates().theta > PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta)
		m_walkingDirection = NormalDirection::dirLeft;
	else
		m_walkingDirection = NormalDirection::dirRight;
}