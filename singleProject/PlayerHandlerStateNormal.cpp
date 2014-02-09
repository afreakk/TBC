#include "stdafx.h"
#include "PlayerHandlerStateNormal.h"
#include "OISCore.h"
#include "PlayerGlobalStats.h"
#include "Player.h"
#include "BehaviourStateNormal.h"

PlayerHandlerStateNormal::PlayerHandlerStateNormal(Player* player) 
: HandlerState(PLAYER_HANDLER_STATE::NORMAL)
, m_player(player)
, m_spaceDown(false)
, m_walkingDirection{ NormalDirection::None }
, m_normalState{ new BehaviourStateNormal{ &m_walkingDirection , &PlayerGlobalStats::getSingleton().getWalkingSpeed()}}
, m_tumble(TUMBLE_DIRECTION::DIRECTION_NONE)
{
	m_player->setState(m_normalState.get());
}


PlayerHandlerStateNormal::~PlayerHandlerStateNormal()
{
}
void PlayerHandlerStateNormal::update()
{
	m_walkingDirection = getWalkingDirection();
	if (m_spaceDown)
		m_state = PLAYER_HANDLER_STATE::SELECTION;
	else if (m_tumble != TUMBLE_DIRECTION::DIRECTION_NONE)
		m_state = PLAYER_HANDLER_STATE::TUMBLE;
}

void PlayerHandlerStateNormal::keyPressed(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KeyCode::KC_SPACE)
		m_spaceDown = true;

	if (e.key == OIS::KeyCode::KC_W)
		m_tumble = TUMBLE_DIRECTION::DIRECTION_IN;
	else if (e.key == OIS::KeyCode::KC_S)
		m_tumble = TUMBLE_DIRECTION::DIRECTION_OUT;
}
void PlayerHandlerStateNormal::keyReleased(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KeyCode::KC_SPACE)
		m_spaceDown = false;

}
NormalDirection PlayerHandlerStateNormal::getWalkingDirection()
{
	auto keyboard = OISCore::getSingletonPtr()->getKeyboard();
	char direction = 0;
	if (keyboard->isKeyDown(OIS::KeyCode::KC_A))
		direction--;
	if (keyboard->isKeyDown(OIS::KeyCode::KC_D))
		direction++;
	if (direction > 0)
		return NormalDirection::Left;
	if (direction < 0)
		return NormalDirection::Right;
	return NormalDirection::None;
}