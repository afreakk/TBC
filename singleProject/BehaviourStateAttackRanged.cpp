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
	if (m_localTime >= m_shootDelay)
	{
		aim(modelHandler);
		m_localTime = 0.0;
		m_lerp = 0.0;
        static_cast<ModelHandlerMutant&>(modelHandler).fire();
	}

	auto dt = MainUpdate::getSingleton().getDeltaTime()*GlobalVariables::getSingleton().getSpeed();
	m_localTime += dt;
	Quaternion interpolatedLookAt = m_delayedDirectionToPlayer;
	if (m_lerp < 1.0)
	{
	    m_lerp += dt;
        Quaternion interpolatedLookAt = Math::lerp(m_originalDirection, m_delayedDirectionToPlayer, m_lerp);
	}
	modelHandler.getNode()->setOrientation(interpolatedLookAt);
}

void BehaviourStateAttackRanged::aim(ModelHandler& modelHandler)
{
	m_originalDirection = modelHandler.getNode()->getOrientation();
	m_delayedPlayerPos = PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition();
	m_delayedDirectionToPlayer =  (m_originalDirection * Vector3(0.0, 0.0, -1.0)).getRotationTo(m_delayedPlayerPos-modelHandler.getNode()->getPosition());
	m_delayedDirectionToPlayer = m_originalDirection * m_delayedDirectionToPlayer;
}
