#include "stdafx.h"
#include "PlayerLERPState.h"
#include "PlayerStats.h"

#include "../GameLevels/MainUpdate.h"
PlayerLERPState::PlayerLERPState() :PlayerState(PLAYER_STATES::PlayerLERPState), m_currentTargetIndex(0), m_moreEnemies(true), m_lerpState(LERP_STATE::LERP_WALK)
{
}


PlayerLERPState::~PlayerLERPState()
{
}

void PlayerLERPState::update(PlayerModelHandler& modelHandler)
{
	if (m_moreEnemies)
		m_moreEnemies = attackEnemies(modelHandler);
	else
	{
		if (returnToNormal(modelHandler))
		{
			auto newPos = m_attackList[m_currentTargetIndex]->getNormalPos();
			modelHandler.setNormalPos(newPos);
			m_nextState = PLAYER_STATES::PlayerNormalState;
		}
	}
}
bool PlayerLERPState::attackEnemies(PlayerModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	if (m_lerpState == LERP_STATE::LERP_WALK)
		m_lerpState = modelHandler.lerpWalk(m_lastPosition, m_attackList[m_currentTargetIndex]->getNode()->getPosition(), dt);
	else if (m_lerpState == LERP_STATE::LERP_ATTACK)
	{
		m_lerpState = modelHandler.lerpAttack(m_lastPosition, m_attackList[m_currentTargetIndex]->getNode()->getPosition(), dt);
		if (m_lerpState == LERP_STATE::LERP_WALK)
		{
			modelHandler.resetLerp();
			m_lastPosition = modelHandler.getNode()->getPosition();
			if (m_currentTargetIndex + 1 < m_attackList.size())
				m_currentTargetIndex++;
			else
				return false;
		}
	}
	return true;
}
bool PlayerLERPState::returnToNormal(PlayerModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	return true; // lol
}
void PlayerLERPState::init(PlayerModelHandler& modelHandler)
{
	cout << "init LerpState" << endl;
	modelHandler.resetLerp();
	m_currentTargetIndex = 0;
	m_nextState = PLAYER_STATES::PlayerLERPState;
	m_moreEnemies = true;
	m_lerpState = LERP_STATE::LERP_WALK;
	m_lastPosition = modelHandler.getNode()->getPosition();
	m_attackList = PlayerStats::getSingletonPtr()->getAttackList();
}
void PlayerLERPState::exit()
{
}