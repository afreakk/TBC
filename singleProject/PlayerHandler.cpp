#include "stdafx.h"
#include "PlayerHandler.h"
#include "PlayerHandlerStateNormal.h"
#include "PlayerHandlerStateSelection.h"
#include "PlayerHandlerStateMultiAttack.h"
#include "PlayerHandlerStateSingleAttack.h"
#include "PlayerHandlerStateDead.h"
#include "PlayerHandlerStateTumble.h"
#include "OISCore.h"
#include "Player.h"


PlayerHandler::PlayerHandler(Player* player) 
: m_player(player)
, StateHandler(new PlayerHandlerStateNormal(player))
{
	OISCore::getSingletonPtr()->addKeyListener(this, "PlayerHandler");
}

PlayerHandler::~PlayerHandler()
{
	OISCore::getSingletonPtr()->removeKeyListener("PlayerHandler");
}


void PlayerHandler::switchState(PLAYER_HANDLER_STATE newState)
{
	std::vector<unsigned> mutantList;
	TUMBLE_DIRECTION tumbleValue = TUMBLE_DIRECTION::DIRECTION_NONE;
	switch (newState)
	{
	case PLAYER_HANDLER_STATE::NORMAL:
		m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<PLAYER_HANDLER_STATE>>( new PlayerHandlerStateNormal(m_player) ) ;
		break;
	case PLAYER_HANDLER_STATE::SELECTION:
		m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<PLAYER_HANDLER_STATE>>( new PlayerHandlerStateSelection(m_player));
		break;
	case PLAYER_HANDLER_STATE::MULTI_ATTACK:
		mutantList = static_cast<PlayerHandlerStateSelection*>(m_currentState.get())->getAttackList();
		m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<PLAYER_HANDLER_STATE>>( new PlayerHandlerStateMultiAttack(mutantList, m_player));
		break;
	case PLAYER_HANDLER_STATE::SINGLE_ATTACK:
		m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<PLAYER_HANDLER_STATE>>( new PlayerHandlerStateSingleAttack(m_player));
		break;
	case PLAYER_HANDLER_STATE::DEAD:
		m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<PLAYER_HANDLER_STATE>>(new PlayerHandlerStateDead(m_player));
		break;
	case PLAYER_HANDLER_STATE::TUMBLE:
		tumbleValue = static_cast<PlayerHandlerStateNormal*>(m_currentState.get())->getTumbleValue();
		m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<PLAYER_HANDLER_STATE>>(new PlayerHandlerStateTumble(tumbleValue, m_player));
		break;
	default:
		assert(0);
		break;
	}
	notifySubscribers();

}
bool PlayerHandler::keyPressed(const OIS::KeyEvent& e)
{
	m_currentState->keyPressed(e);
	return true;
}
bool PlayerHandler::keyReleased(const OIS::KeyEvent& e)
{
	m_currentState->keyReleased(e);
	return true;
}