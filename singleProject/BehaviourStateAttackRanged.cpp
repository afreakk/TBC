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
, m_delayedPlayerPos(Vector3::ZERO)
, m_delayedDirectionToPlayer(Quaternion::ZERO)
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
	auto dt = MainUpdate::getSingleton().getDeltaTime()*GlobalVariables::getSingleton().getSpeed();
	aim(modelHandler);
    Quaternion interpolatedLookAt = Math::lerp<Quaternion,Real>(m_originalDirection, m_delayedDirectionToPlayer, Real(dt*1.0));
	modelHandler.getNode()->setOrientation(m_delayedDirectionToPlayer);
	if (m_localTime >= m_shootDelay)
	{
        static_cast<ModelHandlerMutant&>(modelHandler).fire();
		m_localTime = 0.0;
	}
	m_localTime += dt;
}

void BehaviourStateAttackRanged::aim(ModelHandler& modelHandler)
{
	m_originalDirection = modelHandler.getNode()->getOrientation();
	m_delayedPlayerPos = PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition();
	m_delayedDirectionToPlayer =  (m_originalDirection * Vector3(0.0, 0.0, -1.0)).getRotationTo(m_delayedPlayerPos-modelHandler.getNode()->getPosition());
	m_delayedDirectionToPlayer = m_originalDirection * m_delayedDirectionToPlayer;
}
