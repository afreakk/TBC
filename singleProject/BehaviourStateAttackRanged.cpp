#include "stdafx.h"
#include "BehaviourStateAttackRanged.h"
#include "ModelHandlerMutant.h"
#include "PlayerContainer.h"
#include "MainUpdate.h"
#include "Player.h"

BehaviourStateAttackRanged::BehaviourStateAttackRanged()
: BehaviourState(BEHAVOUR_STATE::RANGED_ATTACK)
, m_delayedPlayerPos(Vector3::ZERO)
, m_delayedDirectionToPlayer(Quaternion::ZERO)
, m_lerp(Real(0.0))
, m_shootDelay(2.0)
, m_localTime(m_shootDelay)
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
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	m_localTime += dt;
	if (m_lerp < 1.0)
	    m_lerp += dt/1.5;
	Quaternion interpolatedLookAt = Math::lerp(m_originalDirection, m_delayedDirectionToPlayer, m_lerp);
	modelHandler.getNode()->setOrientation(interpolatedLookAt);
	/*
	Real shootDelay = m_shootDelay*(1.0/GlobalVariables::getSingleton().getSpeed());
	m_localTime += MainUpdate::getSingleton().getDeltaTime();
	if (m_localTime > shootDelay)
	{
		m_localTime = 0.0;
		m_hasAimed = false;
		static_cast<ModelHandlerMutant&>(modelHandler).fire();
	}
	else if (m_localTime > shootDelay / 2.0&& !m_hasAimed)
	{
		if (hasHit())
			PlayerContainer::getSingleton().killPlayer();
		aim(modelHandler);
		m_hasAimed = true;
	}*/
}

void BehaviourStateAttackRanged::aim(ModelHandler& modelHandler)
{
	m_originalDirection = modelHandler.getNode()->getOrientation();
	m_delayedPlayerPos = PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition();
	m_delayedDirectionToPlayer =  (m_originalDirection * Vector3(0.0, 0.0, -1.0)).getRotationTo(m_delayedPlayerPos-modelHandler.getNode()->getPosition());
	m_delayedDirectionToPlayer = m_originalDirection * m_delayedDirectionToPlayer;
	cout << "aim at: " << m_delayedPlayerPos << endl;
	cout << "direction: " << m_delayedDirectionToPlayer << endl;
}
bool BehaviourStateAttackRanged::hasHit()
{
	if (m_delayedPlayerPos.distance(PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition()) < 0.3)
		return true;
	return false;
}