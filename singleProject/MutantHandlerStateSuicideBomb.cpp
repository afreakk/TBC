#include "stdafx.h"
#include "LaneSettings.h"
#include "MutantHandlerStateSuicideBomb.h"
#include "ModelHandlerMutant.h"
#include "BehaviourStateLERP.h"
#include "BehaviourStateNormal.h"
#include "MutantGlobalStats.h"
#include "MainUpdate.h"
#include "MutantContainer.h"
#include "LERPWalkAttack.h"
#include "BehaviourStateTumble.h"
// playerObject, &MutantGlobalStats::getSingleton().getLERPSpeed(),new LERPWalkAttack()
MutantHandlerStateSuicideBomb::MutantHandlerStateSuicideBomb(BehaviourObject* mutant, BehaviourObject* playerObject)
: HandlerState(MUTANT_HANDLER_STATE::RANGED_ATTACK)
, m_direction(NormalDirection::dirLeft)
, m_speed(MutantGlobalStats::getSingleton().getWalkSpeed())
, m_mutant(mutant)
, m_mutState{ new BehaviourStateNormal(&m_direction,&m_speed) }
, m_detonationTimer(5.0)
, m_activated(false)
, m_player(playerObject)
, m_tumbleDirection(TUMBLE_DIRECTION::DIRECTION_NONE)
, m_mutantState(SUICIDE_STATE::NORMAL)
{
	m_mutant->setState(m_mutState.get());
}


MutantHandlerStateSuicideBomb::~MutantHandlerStateSuicideBomb()
{
}

void MutantHandlerStateSuicideBomb::update()
{
	handleTumble();
	steerTowardsPlayer();
	handleDetonationTimer();
	if (m_player->getNode()->getPosition().distance(m_mutant->getNode()->getPosition()) < 200.0)
		clickClicker();
}

void MutantHandlerStateSuicideBomb::clickClicker()
{
	if (m_activated)
		return;
    static_cast<ModelHandlerMutant&>(m_mutant->getModelHandler()).fire();
    MutantContainer::getSingleton().killMutant(m_mutant->getNode()->getName());
    m_activated = true;
}
void MutantHandlerStateSuicideBomb::handleDetonationTimer()
{
	m_detonationTimer -= MainUpdate::getSingleton().getScaledDeltaTime();
	if (m_detonationTimer <= 0.0)
		clickClicker();
}
void MutantHandlerStateSuicideBomb::steerTowardsPlayer()
{
	horizontalSteer();
	verticalSteer();
}

void MutantHandlerStateSuicideBomb::handleTumble()
{
	if (m_mutState->getState() != BEHAVOUR_STATE::TUMBLE)
		return;
	if (static_cast<BehaviourStateTumble*>(m_mutState.get())->hasReachedEnd())
		setState(SUICIDE_STATE::NORMAL);
}
void MutantHandlerStateSuicideBomb::verticalSteer()
{
	int playerLane = LaneSettings::getSingleton().getClosestLane(m_player->getPolarCoordinates());
	int mutantLane = LaneSettings::getSingleton().getClosestLane(m_mutant->getPolarCoordinates());
	int result = mutantLane - playerLane;
	if (result > 0)
		m_tumbleDirection = TUMBLE_DIRECTION::DIRECTION_IN;
	else if (result < 0)
		m_tumbleDirection = TUMBLE_DIRECTION::DIRECTION_OUT;
	else
		m_tumbleDirection = TUMBLE_DIRECTION::DIRECTION_NONE;
	if (m_tumbleDirection != TUMBLE_DIRECTION::DIRECTION_NONE)
		setState(SUICIDE_STATE::TUMBLE);
}
void MutantHandlerStateSuicideBomb::horizontalSteer()
{
	if (m_mutant->getPolarCoordinates().theta > m_player->getPolarCoordinates().theta)
		m_direction = NormalDirection::dirLeft;
	else
		m_direction = NormalDirection::dirRight;
}
void MutantHandlerStateSuicideBomb::setState(SUICIDE_STATE state)
{
	m_mutantState = state;
	m_mutState.reset();
	switch (state)
	{
	case SUICIDE_STATE::NORMAL:
		m_mutState = unique_ptr<BehaviourState>(new BehaviourStateNormal(&m_direction, &m_speed));
		break;
	case SUICIDE_STATE::TUMBLE:
        m_mutState = unique_ptr<BehaviourState>(new BehaviourStateTumble(vectorFromTumbleDirection(m_mutant->getNode()->getPosition(), m_tumbleDirection),1000.0));
		break;
	default:
		assert(0);
		break;
	}
	m_mutant->setState(m_mutState.get());

}