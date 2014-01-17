#include "stdafx.h"
#include "PlayerLERPState.h"
#include "PlayerStats.h"

#include "../GameLevels/MainUpdate.h"
PlayerLERPState::PlayerLERPState() :PlayerState(PLAYER_STATES::PlayerLERPState), m_currentTargetIndex(0) , m_lerpT(0.0)
{
}


PlayerLERPState::~PlayerLERPState()
{
}

void PlayerLERPState::update(PlayerModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	modelHandler.getNode()->setPosition(Ogre::Math::lerp(m_lastPosition, m_attackList[m_currentTargetIndex]->getNode()->getPosition(),m_lerpT));
	m_lerpT += dt;
	if (m_lerpT > 1.0)
	{
		m_lerpT = 0.0;
		m_lastPosition = modelHandler.getNode()->getPosition();
		if (m_currentTargetIndex == m_attackList.size()-1)
			goAttack();
		else
			m_currentTargetIndex++;
	}

}
void PlayerLERPState::goAttack()
{

}
void PlayerLERPState::init(PlayerModelHandler& modelHandler)
{
	m_currentTargetIndex = 0;
	m_lastPosition = modelHandler.getNode()->getPosition();
	m_attackList = PlayerStats::getSingletonPtr()->getAttackList();
	cout << m_attackList.size() << endl;
	cout << PlayerStats::getSingletonPtr()->getAttackList().size() << endl;
}
void PlayerLERPState::exit()
{

}