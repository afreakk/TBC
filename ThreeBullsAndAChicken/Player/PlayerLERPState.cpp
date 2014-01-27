#include "stdafx.h"
#include "PlayerLERPState.h"
#include "PlayerStats.h"

#include "../GameLevels/MainUpdate.h"
PlayerLERPState::PlayerLERPState(SceneNode* target) :PlayerState(PLAYER_STATES::PlayerLERPState), m_lerpState(LERP_STATE::LERP_WALK), m_target(target)
, m_goNextTarget(false)
{
}


PlayerLERPState::~PlayerLERPState()
{
}

bool PlayerLERPState::nextTarget() const
{
	return m_goNextTarget;
}
void PlayerLERPState::update(PlayerModelHandler& modelHandler)
{
	if (attackEnemy(modelHandler))
		m_goNextTarget = true;

}
bool PlayerLERPState::attackEnemy(PlayerModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	const Ogre::Vector3& tPos = m_target->getPosition();
	if (m_lerpState == LERP_STATE::LERP_WALK)
		m_lerpState = modelHandler.lerpWalk(tPos, dt);
	else if (m_lerpState == LERP_STATE::LERP_ATTACK)
	{
		m_lerpState = modelHandler.lerpAttack(tPos, dt);
		if (m_lerpState == LERP_STATE::LERP_WALK)
		{
			return true;
		}
	}
	return false;
}
/*
bool PlayerLERPState::returnToNormal(PlayerModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	auto newPos = m_target->getNormalPos();
	modelHandler.setNormalPos(newPos);
	m_nextState = PLAYER_STATES::PlayerNormalState;
	return true; // lol
}
*/