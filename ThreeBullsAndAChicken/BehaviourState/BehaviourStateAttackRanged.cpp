#include "stdafx.h"
#include "BehaviourStateAttackRanged.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"
#include "../Containers/PlayerContainer.h"
#include "../GameLevels/MainUpdate.h"

BehaviourStateAttackRanged::BehaviourStateAttackRanged()
: BehaviourState(BEHAVOUR_STATE::RANGED_ATTACK)
, m_delayedPlayerPos(Vector3::ZERO)
, m_shootDelay(2.0)
, m_localTime(0.0)
, m_hasAimed(false)
{
}


BehaviourStateAttackRanged::~BehaviourStateAttackRanged()
{
}

void BehaviourStateAttackRanged::update(ModelHandler& modelHandler)
{
	m_localTime += MainUpdate::getSingleton().getDeltaTime();
	if (m_localTime > m_shootDelay)
	{
		m_localTime = 0.0;
		m_hasAimed = false;
		static_cast<ModelHandlerMutant&>(modelHandler).fire();
	}
	else if (m_localTime > m_shootDelay / 2.0&& !m_hasAimed)
	{
		if (hasHit())
			PlayerContainer::getSingleton().killPlayer();
		aim(modelHandler);
		m_hasAimed = true;
	}
}

void BehaviourStateAttackRanged::aim(ModelHandler& modelHandler)
{
	m_delayedPlayerPos = PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition();
	modelHandler.getNode()->lookAt(m_delayedPlayerPos,Ogre::Node::TransformSpace::TS_WORLD);
}
bool BehaviourStateAttackRanged::hasHit()
{
	if (m_delayedPlayerPos.distance(PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition()) < 0.3)
		return true;
	return false;
}