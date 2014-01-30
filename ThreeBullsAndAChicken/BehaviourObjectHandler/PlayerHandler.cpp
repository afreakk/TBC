#include "stdafx.h"
#include "PlayerHandler.h"
#include "PlayerHandlerStateNormal.h"
#include "PlayerHandlerStateSelection.h"
#include "PlayerHandlerStateLERP.h"
#include "../OgreCore/OISCore.h"


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
	case PLAYER_HANDLER_STATE::LERP:
		mutantList = static_cast<PlayerHandlerStateSelection*>(m_currentState.get())->getAttackList();
		m_currentState.reset();
		m_currentState = unique_ptr<HandlerState<PLAYER_HANDLER_STATE>>( new PlayerHandlerStateLERP(mutantList, m_player));
		break;
	default:
		assert(0);
		break;
	}

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