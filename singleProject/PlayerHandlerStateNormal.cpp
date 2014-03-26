#include "stdafx.h"
#include "PlayerHandlerStateNormal.h"
#include "OISCore.h"
#include "MainUpdate.h"
#include "PlayerGlobalStats.h"
#include "Player.h"
#include "BehaviourStateNormal.h"
#include "MutantContainer.h"
#include "ModelHandlerPlayer.h"
PlayerHandlerStateNormal::PlayerHandlerStateNormal(Player* player) 
: HandlerState(PLAYER_HANDLER_STATE::NORMAL)
, m_player(player)
, m_walkingDirection{ NormalDirection::None }
, m_normalState{ new BehaviourStateNormal{ &m_walkingDirection , &PlayerGlobalStats::getSingleton().getWalkingSpeed()}}
, m_tumble(TUMBLE_DIRECTION::DIRECTION_NONE)
, m_tumbleAttack(false)
, m_teleporter(player)
{
	m_player->setState(m_normalState.get());
}

bool PlayerHandlerStateNormal::tumbleAttack() const
{
	return m_tumbleAttack;
}

PlayerHandlerStateNormal::~PlayerHandlerStateNormal()
{
}
void PlayerHandlerStateNormal::update()
{
	if(!m_teleporter.handleTeleport())
	{
        m_walkingDirection = getWalkingDirection();
        if (m_tumble != TUMBLE_DIRECTION::DIRECTION_NONE)
            m_state = PLAYER_HANDLER_STATE::TUMBLE;
    //    if (PlayerGlobalStats::getSingleton().getEnergy() == 100 )
      //      m_state = PLAYER_HANDLER_STATE::SELECTION;
	}
	else
		m_walkingDirection = NormalDirection::None;


}

void PlayerHandlerStateNormal::keyPressed(const OIS::KeyEvent& e)
{
	if (OISCore::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Modifier::Shift) && (e.key == OIS::KeyCode::KC_SPACE || e.key == OIS::KeyCode::KC_C))
		m_state = PLAYER_HANDLER_STATE::SELECTION;
	else if (e.key == OIS::KeyCode::KC_E)
		m_teleporter.teleport();
	else if (e.key == OIS::KeyCode::KC_SPACE || e.key == OIS::KeyCode::KC_C)
		m_state = PLAYER_HANDLER_STATE::SINGLE_ATTACK;
	if (e.key == OIS::KeyCode::KC_W)
		m_tumble = TUMBLE_DIRECTION::DIRECTION_IN;
	else if (e.key == OIS::KeyCode::KC_S)
		m_tumble = TUMBLE_DIRECTION::DIRECTION_OUT;
}
void PlayerHandlerStateNormal::keyReleased(const OIS::KeyEvent& e)
{

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
		return NormalDirection::dirRight;
	if (direction < 0)
		return NormalDirection::dirLeft;
	return NormalDirection::None;
}