#include "stdafx.h"
#include "PlayerHandlerStateTumble.h"
#include "../Stats/PlayerGlobalStats.h"


PlayerHandlerStateTumble::PlayerHandlerStateTumble(TUMBLE_DIRECTION direction, Player* player)
: HandlerState(PLAYER_HANDLER_STATE::TUMBLE)
, m_player(player)
, m_currentTumbleState(new BehaviourStateTumble(vectorFromTumbleDirection(player->getNode()->getPosition(), direction),PlayerGlobalStats::getSingleton().getTumbleSpeed()))
{
	m_player->setState(m_currentTumbleState.get());
}


PlayerHandlerStateTumble::~PlayerHandlerStateTumble()
{
}

void PlayerHandlerStateTumble::update()
{
	if (m_currentTumbleState->hasReachedEnd())
		m_state = PLAYER_HANDLER_STATE::NORMAL;

}