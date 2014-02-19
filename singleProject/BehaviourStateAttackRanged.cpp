#include "stdafx.h"
#include "BehaviourStateAttackRanged.h"
#include "ModelHandlerMutant.h"
#include "PlayerContainer.h"
#include "MainUpdate.h"
#include "Player.h"
#include "GlobalVariables.h"
#include "MutantGlobalStats.h"

BehaviourStateAttackRanged::BehaviourStateAttackRanged()
: BehaviourState(BEHAVOUR_STATE::RANGED_ATTACK)
, m_phase(AttackRangedPhase::reloading)
, m_delayedPlayerPos(Vector3::ZERO)
, m_directionToPlayer(Quaternion::ZERO)
, m_lerp(Real(0.0))
, m_shootDelay(MutantGlobalStats::getSingleton().getRangedCooldown())
, m_localTime(0.0)
, m_hasAimed(false)
{
}


BehaviourStateAttackRanged::~BehaviourStateAttackRanged()
{
}

void BehaviourStateAttackRanged::update(ModelHandler& modelHandler)
{
	const auto& dt = MainUpdate::getSingleton().getScaledDeltaTime();
	m_localTime += dt;
	switch (m_phase)
	{
	case AttackRangedPhase::shooting:
		m_phase = shootingPhase(modelHandler, dt);
		break;
	case AttackRangedPhase::reloading:
		m_phase = reloadPhase(modelHandler, dt);
		break;
	default:
		m_phase = waiting(modelHandler, dt);
		break;
	}
}

AttackRangedPhase BehaviourStateAttackRanged::waiting(ModelHandler& modelHandler, const Ogre::Real& dt)
{
	if (m_localTime >= m_shootDelay)
	{
		m_localTime = 0.0;
		return AttackRangedPhase::reloading;
	}
	return AttackRangedPhase::waiting;

}
AttackRangedPhase BehaviourStateAttackRanged::shootingPhase(ModelHandler& modelHandler, const Ogre::Real& dt)
{
    static_cast<ModelHandlerMutant&>(modelHandler).fire();
    return AttackRangedPhase::waiting;
}
AttackRangedPhase BehaviourStateAttackRanged::reloadPhase(ModelHandler& modelHandler, const Ogre::Real& dt)
{
	if (m_localTime >= m_shootDelay)
	{
		m_localTime = 0.0;
		return AttackRangedPhase::shooting;
	}
	aim(modelHandler);
    Quaternion interpolatedLookAt = Math::lerp<Quaternion,Real>(m_originalDirection, m_directionToPlayer, Real(dt*2.0));
	modelHandler.getNode()->setOrientation(interpolatedLookAt);
	return AttackRangedPhase::reloading;
}
void BehaviourStateAttackRanged::aim(ModelHandler& modelHandler)
{
	m_originalDirection = modelHandler.getNode()->getOrientation();
	m_delayedPlayerPos = PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition();
	m_directionToPlayer =  (m_originalDirection * Vector3(0.0, 0.0, -1.0)).getRotationTo(m_delayedPlayerPos-modelHandler.getNode()->getPosition());
	m_directionToPlayer = m_originalDirection * m_directionToPlayer;
}
