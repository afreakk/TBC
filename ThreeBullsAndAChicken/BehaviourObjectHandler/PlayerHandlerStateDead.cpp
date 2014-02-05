#include "stdafx.h"
#include "PlayerHandlerStateDead.h"


PlayerHandlerStateDead::PlayerHandlerStateDead(Player* player)
: HandlerState(PLAYER_HANDLER_STATE::DEAD)
, m_player(player)
, m_deadState(new BehaviourStateDead())
{
	m_player->setState(m_deadState.get());
}


PlayerHandlerStateDead::~PlayerHandlerStateDead()
{
}

void PlayerHandlerStateDead::update()
{

}